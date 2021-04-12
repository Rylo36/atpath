#include "handler.hpp"

void ap::AtPath::engine(int cycles){
    for(int tries{0}; tries < cycles; tries++){
        //std::cout << "isDone: " << eS.done << std::endl;
        if(eS.done) return;
        if(eS.nodes.size() == 0) eS.head = origin;

        float increment{config.point_distance};    
        sf::Vector2f best{eS.head};

        for(int ang{0}; ang < 360; ang += 10){
            sf::Vector2f test{eS.head};
            test.x += cos(ang) * increment; test.y += sin(ang) * increment;
            if(isValid(test) && getPointWeight(test) + 50.f * (1/getDistance(test,destination)) > getPointWeight(best) + 50.f * (1/getDistance(best,destination)))
                best = test;
        }
        //std::cout << best.x << " " <<  best.y << " != " << eS.head.x << " " << eS.head.y << std::endl; 
        if(best != eS.head){eS.nodes.push_back(best); eS.head = best;}
        else if(getDistance(eS.head,destination) > config.point_distance * 2) eS.fault = true; //Check to ensure that we are not at the destination, then declare this path a fail
        //std::cout << getDistance(eS.head,destination) << std::endl;
        if(eS.nodes.size() > getBestRoute().size() * 2 && routes.size() > 0) eS.fault = true;

        if(checkPath(eS.nodes)){
            eS.nodes = SimplifyNodes(eS.nodes);
            if(routes.size() == 0){routes.push_back(eS.nodes);}
            else writeRoute(eS.nodes);
            eS.done = true;
            positive_points.insert(positive_points.end(), eS.nodes.begin(), eS.nodes.end());
        }

        //std::cout << "Size: " << eS.nodes.size() << " RS: " << routes.size() << std::endl;
            
        if(eS.fault){
            negative_points.insert(negative_points.end(), eS.nodes.begin(), eS.nodes.end());
            eS.nodes.clear();
            eS.fault = false;
        }
    }
}