#include <iostream>
#include <SFML/Graphics.hpp>
#include "atpath/atpath.hpp"

sf::Vector2f res{1000.f,1000.f};

sf::RectangleShape destination(sf::Vector2f{25.f,25.f});
sf::RectangleShape pawn(sf::Vector2f{25.f,25.f});
std::vector<sf::RectangleShape> blocks;
std::vector<sf::Vector2f> nodes;

ap::AtPath atpath(pawn.getPosition(),destination.getPosition());



std::vector<sf::Rect<float>> BlocksToBounds(std::vector<sf::RectangleShape> blks){
    std::vector<sf::Rect<float>> vec;
    for(sf::RectangleShape b : blks)
        vec.push_back(b.getGlobalBounds());
    return vec;
}

void Input(sf::Window &w){

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        sf::Vector2f pos{(float)sf::Mouse::getPosition(w).x, (float)sf::Mouse::getPosition(w).y};
        bool valid = true;
        atpath.reset();
        for(sf::RectangleShape b : blocks) if(b.getGlobalBounds().contains(pos)) valid = false;
        if(valid) destination.setPosition(pos);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) blocks.clear();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) nodes = atpath.reroute();
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
        atpath.obstacles = BlocksToBounds(blocks);
        atpath.origin = pawn.getPosition();
        atpath.destination = destination.getPosition();
        nodes = atpath.route();
    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
        sf::Vector2f pos{(float)sf::Mouse::getPosition(w).x, (float)sf::Mouse::getPosition(w).y};
        bool valid = true;
        for(sf::RectangleShape b : blocks) if(b.getGlobalBounds().contains(pos)) valid = false;
        if(valid){
        sf::RectangleShape b{sf::Vector2f(20.f,20.f)};
        b.setPosition(pos);
        b.setFillColor(sf::Color(232, 136, 9));
        blocks.push_back(b);
        }
    }

}



std::vector<sf::CircleShape> NodesToCircles(std::vector<sf::Vector2f> nds){
    std::vector<sf::CircleShape> vec;
    for(sf::Vector2f n : nds){
        sf::CircleShape c{2.f};
        c.setFillColor(sf::Color::Green);
        c.setPosition(n);
        vec.push_back(c);
    }
    return vec;
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
        //atpath.improve_route();
        std::vector<sf::CircleShape> cn;
        cn = NodesToCircles(nodes);
        window.clear(sf::Color::Black);
        window.draw(destination);
        window.draw(pawn);
        for(sf::RectangleShape b : blocks) window.draw(b);
        for(sf::CircleShape c : cn) window.draw(c);
        window.display();
    }
    return 0;
}