#pragma once
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>


namespace ap{

    class AtPath{
        private:
            std::vector<sf::Vector2f> positive_points;
            std::vector<sf::Vector2f> negative_points;
            float getPointWeight(sf::Vector2f point); //Get the current weight of a location
            bool checkPath(std::vector<sf::Vector2f> path);//Check to ensure that a path is valid
            float getCost(std::vector<sf::Vector2f> path);//Calculate the cost of a path
            float getDistance(sf::Vector2f a, sf::Vector2f b);//Calculate the distance between two points
            float getSlope(sf::Vector2f a, sf::Vector2f b);//Calculate the slope between two points
            bool isValid(sf::Vector2f point);//Check to see if the point intersects with an obstacle
            std::vector<sf::Vector2f> SimplifyNodes(std::vector<sf::Vector2f> nodes);//Simplify a vector of nodes (get rid of unrequired points)
        public:
            std::vector<std::vector<sf::Vector2f>> routes;
            std::vector<sf::Rect<float>> obstacles;
            sf::Vector2f origin;
            sf::Vector2f destination;
            AtPath(sf::Vector2f start, sf::Vector2f stop);
            std::vector<sf::Vector2f> route(int cycles=200); //Generates a route or improves an existing one
            void reset(); //Reset path learning (use if the destination, obstacles, or origin has changed)
            std::vector<sf::Vector2f> reroute(int cycles=200);
            std::vector<sf::Vector2f> improve_route(int cycles=1); //Light weight task meant to improve upon and/or find better routes in the background
    };
}