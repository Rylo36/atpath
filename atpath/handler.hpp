#pragma once
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "perfmon.hpp"

namespace ap{

    class AtPath{
        private:
            struct engineState{ //Engine State Variables
                int cycle_count;
                //std::vector<sf::Vector2f> best_route;
                std::vector<sf::Vector2f> nodes;
                sf::Vector2f head;
                bool fault;
                bool done;
            } eS;
            std::vector<sf::Vector2f> positive_points;
            std::vector<sf::Vector2f> negative_points;
            void engine(int cycles=10);
            void writeRoute(std::vector<sf::Vector2f> write_route); 
            float getPointWeight(sf::Vector2f point); //Get the current weight of a location
            bool checkPath(std::vector<sf::Vector2f> path);//Check to ensure that a path is valid
            float getCost(std::vector<sf::Vector2f> path);//Calculate the cost of a path
            float getDistance(sf::Vector2f a, sf::Vector2f b);//Calculate the distance between two points
            float getSlope(sf::Vector2f a, sf::Vector2f b);//Calculate the slope between two points
            bool isValid(sf::Vector2f point);//Check to see if the point intersects with an obstacle
            std::vector<sf::Vector2f> SimplifyNodes(std::vector<sf::Vector2f> nodes);//Simplify a vector of nodes (get rid of unrequired points)
        public:
            struct Config{ //Configuration parameters
                float point_distance = 10.f;
                float max_distance = 2000.f;
            } config;
            Tmr pf{60};
            std::vector<std::vector<sf::Vector2f>> routes;
            std::vector<sf::Rect<float>> obstacles;
            sf::Vector2f origin;
            sf::Vector2f destination;
            AtPath(sf::Vector2f start, sf::Vector2f stop);
            void route(int cycles=200); //Generates a route or improves an existing one
            std::vector<sf::Vector2f> getBestRoute();
            void reset(bool hard = false); //Reset path learning (use if the destination, obstacles, or origin has changed)
            void reroute();
            void realtime(); //Light weight task meant to improve upon and/or find better routes in the background
    };
}