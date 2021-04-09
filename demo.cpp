#include <iostream>
#include <SFML/Graphics.hpp>
#include "atpath/handler.hpp"

sf::Vector2f res{1000.f,1000.f};

sf::RectangleShape destination(sf::Vector2f{25.f,25.f});
sf::RectangleShape pawn(sf::Vector2f{25.f,25.f});
std::vector<sf::RectangleShape> blocks;
std::vector<std::vector<sf::CircleShape>> points;

ap::AtPath atpath(pawn.getPosition(),destination.getPosition());

bool realtime{false};

std::vector<sf::Rect<float>> BlocksToBounds(std::vector<sf::RectangleShape> blks){
    std::vector<sf::Rect<float>> vec;
    for(sf::RectangleShape b : blks)
        vec.push_back(b.getGlobalBounds());
    return vec;
}
/*
std::vector<sf::Vector2f> PointToRoute(std::vector<sf::CircleShape> circles){
    std::vector<sf::Vector2f> path;
    for(sf::CircleShape c : circles) path.push_back(c.getPosition());
    return path;
}*/

void ApplyColors(){
    std::vector<sf::Vector2f> best_route = atpath.getBestRoute();
    for(std::vector<sf::CircleShape> &path : points){
            //std::cout << "Best route: " << best_route.size() << " | Chk: " << path.size() << std::endl;
            if(path.size() == best_route.size()){
                for(sf::CircleShape &c : path) c.setFillColor(sf::Color::Green);
            }     
    }
}




void RoutesToPoints(){
    points.clear();
    for(std::vector<sf::Vector2f> r : atpath.routes){
        std::vector<sf::CircleShape> circles;
        for(sf::Vector2f n : r){
            sf::CircleShape c{2.f};
            c.setFillColor(sf::Color(232, 136, 9));
            c.setPosition(n);
            circles.push_back(c);
        }
        points.push_back(circles);
    }
    //std::cout << "Routes Stored: " << points.size() << std::endl;
    ApplyColors();
}

void Input(sf::Window &w){

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2f pos{(float)sf::Mouse::getPosition(w).x, (float)sf::Mouse::getPosition(w).y};
        bool valid = true;
        atpath.reset(true);
        for(sf::RectangleShape b : blocks) if(b.getGlobalBounds().contains(pos)) valid = false;
        if(valid) destination.setPosition(pos);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) blocks.clear();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
        std::cout << atpath.routes.size() << " FAULT:" << atpath.eS.fault << " DONE:" << atpath.eS.fault << " NODES:" << atpath.eS.nodes.size() << std::endl;
    }
    /*if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)){atpath.reroute(); RoutesToPoints();}
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
        atpath.obstacles = BlocksToBounds(blocks);
        atpath.origin = pawn.getPosition();
        atpath.destination = destination.getPosition();
        RoutesToPoints();
    }*/
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        sf::Vector2f pos{(float)sf::Mouse::getPosition(w).x, (float)sf::Mouse::getPosition(w).y};
        bool valid = true;
        for(sf::RectangleShape b : blocks) if(b.getGlobalBounds().contains(pos)) valid = false;
        atpath.reset(true);
        if(valid){
        sf::RectangleShape b{sf::Vector2f(20.f,20.f)};
        b.setPosition(pos);
        b.setFillColor(sf::Color(140, 136, 130));
        blocks.push_back(b);
        }
    }

}





int main(){
    srand(time(NULL)); //To make random act a little more random

    destination.setFillColor(sf::Color::Red);
    pawn.setFillColor(sf::Color::Blue);
    pawn.setPosition(sf::Vector2f{500.f,500.f});

    sf::RenderWindow window{sf::VideoMode(res.x,res.y),"AtPath Demo"};
    window.setFramerateLimit(30);
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){if(event.type == sf::Event::Closed) window.close();}
        Input(window);

        /*Realtime Pathfinding
        if(realtime){
            atpath.obstacles = BlocksToBounds(blocks);
            atpath.origin = pawn.getPosition();
            atpath.destination = destination.getPosition();
            atpath.realtime();
            RoutesToPoints();
        }
        */
        atpath.obstacles = BlocksToBounds(blocks);
        atpath.origin = pawn.getPosition();
        atpath.destination = destination.getPosition();
        RoutesToPoints();
        atpath.realtime();


        //atpath.improve_route();
        window.clear(sf::Color::Black);
        window.draw(destination);
        window.draw(pawn);
        for(sf::RectangleShape b : blocks) window.draw(b);
        for(std::vector<sf::CircleShape> path : points){for(sf::CircleShape c : path){window.draw(c);}}
        window.display();
    }
    return 0;
}