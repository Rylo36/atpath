#include "handler.hpp"
#define QUICK_MODE 1

void ap::AtPath::engine(int cycles){
    //std::vector<sf::Vector2f> best_route;
    for(int tries{0}; tries < cycles; tries++){
        if(eS.done) return;
        //std::vector<sf::Vector2f> nodes;
        //sf::Vector2f head{origin};
        //bool stop = false;
        //while(getDistance(head, destination) > 10.f && !stop){

        if(eS.nodes.size() == 0) eS.head = origin;

        float increment{5.f};    
        sf::Vector2f best{eS.head};

        for(int ang{0}; ang < 360; ang += 5){
            sf::Vector2f test{eS.head};
            test.x += cos(ang) * increment; test.y += sin(ang) * increment;
            if(isValid(test) && getPointWeight(test) + 50.f * (1/getDistance(test,destination)) > getPointWeight(best) + 50.f * (1/getDistance(best,destination)))
                best = test;
        }

        if(best != eS.head){eS.nodes.push_back(best); eS.head = best;}
        else{
            if(getDistance(eS.head,destination) > 10.f) eS.fault = true; //Check to ensure that we are not at the destination, then declare this path a fail
        }

        if(eS.nodes.size() > getBestRoute().size() * 2 && routes.size() > 0) eS.fault;

        if(checkPath(eS.nodes)){
            eS.nodes = SimplifyNodes(eS.nodes);
            //Path is complete
            if(routes.size() == 0){routes.push_back(eS.nodes);}
            else{
                //if(getCost(eS.nodes) < getCost(getBestRoute())) routes.push_back(eS.nodes);
                writeRoute(eS.nodes);
            }
             eS.done = true;
            positive_points.insert(positive_points.end(), eS.nodes.begin(), eS.nodes.end());
            std::cout << "Good path found" << std::endl;
        }
            
        if(eS.fault){
            negative_points.insert(negative_points.end(), eS.nodes.begin(), eS.nodes.end());
            eS.nodes.clear();
            eS.fault = false;
            std::cout << "Bad path found" << std::endl;
        }
            
           // if(getCost(eS.nodes) < getCost(eS.best_route)) eS.best_route = eS.nodes;}

        //if(!checkPath(eS.best_route)) eS.best_route = eS.nodes;

        //Apply new weights
        //std::cout << getCost(best_route) << "(" << checkPath(nodes) << ")" << std::endl;
        //std::cout << "+" << positive_points.size() << " | -" << negative_points.size() << std::endl; 
    }
}