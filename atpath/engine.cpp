#include "handler.hpp"

void ap::AtPath::engine(int cycles){
    for(int tries{0}; tries < cycles; tries++){
        if(eS.done) return;
        if(eS.nodes.size() == 0) eS.head = origin;

        float increment{10.f};    
        sf::Vector2f best{eS.head};

        for(int ang{0}; ang < 360; ang += 10){
            sf::Vector2f test{eS.head};
            test.x += cos(ang) * increment; test.y += sin(ang) * increment;
            if(isValid(test) && getPointWeight(test) + 50.f * (1/getDistance(test,destination)) > getPointWeight(best) + 50.f * (1/getDistance(best,destination)))
                best = test;
        }

        if(best != eS.head){eS.nodes.push_back(best); eS.head = best;}
        else if(getDistance(eS.head,destination) > 10.f) eS.fault = true; //Check to ensure that we are not at the destination, then declare this path a fail

        if(eS.nodes.size() > getBestRoute().size() * 2 && routes.size() > 0) eS.fault = true;

        if(checkPath(eS.nodes)){
            eS.nodes = SimplifyNodes(eS.nodes);
            if(routes.size() == 0){routes.push_back(eS.nodes);}
            else writeRoute(eS.nodes);
            eS.done = true;
            positive_points.insert(positive_points.end(), eS.nodes.begin(), eS.nodes.end());
        }
            
        if(eS.fault){
            negative_points.insert(negative_points.end(), eS.nodes.begin(), eS.nodes.end());
            eS.nodes.clear();
            eS.fault = false;
        }
    }
}