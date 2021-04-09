#include "handler.hpp"



ap::AtPath::AtPath(sf::Vector2f start, sf::Vector2f stop){
    origin = start; destination = stop;
}

void ap::AtPath::reset(bool hard){
    eS.cycle_count = 0;
    eS.nodes.clear();
    eS.done = false; eS.fault = false;
    positive_points.clear();
    negative_points.clear();
    if(hard) routes.clear();
}

std::vector<sf::Vector2f> ap::AtPath::getBestRoute(){
    std::vector<sf::Vector2f> best_route;
    for(std::vector<sf::Vector2f> r : routes){
        if(getCost(r) < getCost(best_route) || getCost(best_route) == 0) best_route = r;
    }
    return best_route;
}

void ap::AtPath::writeRoute(std::vector<sf::Vector2f> write_route){
    for(std::vector<sf::Vector2f> r : routes){if(getCost(r) == getCost(write_route)) return;}
    routes.push_back(write_route);
}

void ap::AtPath::reroute(){
    std::vector<sf::Vector2f> old_path;
    if(routes.size() > 0) old_path = routes.back();
    reset();
    for(int i{0}; i < 4; i++) {for(sf::Vector2f n : old_path) negative_points.push_back(n);}
    eS.done = false;
    return;
}



float ap::AtPath::getPointWeight(sf::Vector2f point){
    float weight{0.f};
    float force{0.25f};
    for(sf::Vector2f p : positive_points) weight += force * (1/getDistance(p,point)); 
    for(sf::Vector2f n : negative_points) weight -= force * (1/getDistance(n,point));
    return weight; 
}

float ap::AtPath::getCost(std::vector<sf::Vector2f> path){
    float cost{0.f};
    for(int i{0}; i < path.size(); i++){
        if(i < path.size() - 1) cost += getDistance(path[i],path[i+1]);
    }
    return cost;
}

bool ap::AtPath::checkPath(std::vector<sf::Vector2f> path){
    bool valid = true;
    if(path.size() == 0) return false; 
    for(sf::Vector2f p : path) if(!isValid(p)) valid = false;
    if(getDistance(path[0], origin) > 10.f) valid = false;
    if(getDistance(path[path.size() - 1], destination) > 10.f) valid = false;
    return valid;
}

std::vector<sf::Vector2f> ap::AtPath::SimplifyNodes(std::vector<sf::Vector2f> nodes){

    std::vector<sf::Vector2f> marked_for_deletion;
    for(int i{0}; i < nodes.size(); i++){
        if(i != 0 && i < nodes.size() - 1){
            if(getSlope(nodes[i - 1],nodes[i]) == getSlope(nodes[i],nodes[i + 1])) marked_for_deletion.push_back(nodes[i]);
        }
    }

    std::vector<sf::Vector2f> new_list;
    for(sf::Vector2f n : nodes){
        bool skip{false};
         for(sf::Vector2f m : marked_for_deletion)
             if(n == m) skip = true;
        if(!skip) new_list.push_back(n);
    }

    return new_list;
}

float ap::AtPath::getDistance(sf::Vector2f a, sf::Vector2f b){
    return sqrt(pow(a.x - b.x,2) + pow(a.y - b.y, 2));
}

float ap::AtPath::getSlope(sf::Vector2f a, sf::Vector2f b){
    return (b.y - a.y) / (b.x - a.x);
}

bool ap::AtPath::isValid(sf::Vector2f point){
    for(sf::Rect<float> o : obstacles){
        if(o.contains(point) || getDistance(sf::Vector2f{(float)(o.left + (o.width * 0.5)), (float)(o.top + (o.height * 0.5))},point) < o.height * 1.1) return false;
    }
    return true;
}

void ap::AtPath::realtime(){
    pf.update();
    if(routes.size() < 4){
        int cc = 100 * (pf.getFPS() / pf.target_fps);
        engine(cc);
        if(eS.done){reroute(); std::cout << "Rerouting..." << std::endl;}
    }
}