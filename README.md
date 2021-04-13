# AtPath
## What is AtPath?
At path is an easy to use path finding library written in C++ for SFML based applications. 
## How to Install
Simply copy the atpath directory over to your project (or to /usr/include/ if you wish) and include the atpath/handler.hpp file

After including, all components of the library are stored under the **at** namespace

## Demo Controls
 - Left mouse button : Move the destination to the cursor location
 - Right mouse button : Create an obstacle where the cursor is
 - Space : Remove all obstacles
 - R : Reset the engine


## How to Use
### Creating an atpath object
*Note: Everything in this library is stored under the ap namespace*
The constructor takes two parameters: the starting position and destination position. These two locations must be given using the sf::Vector2f format.
```ap::AtPath atpath(start, destination);```

### Modifying obstacles
Obstacles are stored as ```sf:Rect<float>``` through the use of a vector. This is a publicly accessible vector and standard methods such as *push_back* and *remove* can be used to modify it.

### Generating Routes
Routes are stored under the public vector *routes* (routes themselves are a vector of points), and are automatically generated in the background through the *realtime* function. If the *realtime* function is not used, then the route() function can also be used, but performance based scheduling features will be lost (the function generates routes all at once possibly resulting in heavy delay).

### Resetting the engine
The reset() function can be used to reset the pathfinding object. It takes one boolean parameter which specifies if the routes vector should be cleared as well.

### Modifying the configuration
The config struct allows easy access to many important settings that dictate how the engine will function. The following is a list of settings with their respective purpose.
 - ```point_distance``` : The distance between points in routes (shorter distances result in more points, thus are more demanding to generate).
 - ```max_distance``` : The maximum distance from the origin the engine will generate to. (Prevents excessive load from long routes)
 - ```route_count``` : The target number of routes to generate. No more routes will be generated once this number is reached.
 - ```cycle_count_max``` : The number of cycles to generate for a load of 0 (essentially the maximum). This number scales as the load increases in order to maintain the desired framerate.
 - ```reroute_strength``` : The multiplier for how strongly discouraged old routes should be.
 
### Changing the destination or origin
The destination and origin are stored as ```sf::Vector2f``` with the public variables being called destination and origin, respectably.

## Mini Example
The following example purely shows interactions with library and does not show other tasks, such as rendering the obstacles or path. For a full, working, example see **demo.cpp**.
```
#include "atpath/handler.hpp" //Includes the library

ap::AtPath object(origin, destination); //Create the atpath object

object.obstacles = list_of_obstacles; //Setting obstacles to another list of obstacles
object.obstacles.push_back(block) //Adding a single object to the vector of obstacles

object.origin = new_origin_position; //Updating the origin

object.realtime(); //Calling the realtime function. This should be called every process loop

```

## Project Layout
├── atpath - *The main library folder* <br>
│   ├── engine.cpp - *The pathfinding engine (what actually generates the routes)*<br>
│   ├── handler.cpp - *Contains the atpath class which holds and prepares all the needed data for the engine*<br>
│   ├── handler.hpp - *Header file for handler.cpp and engine.cpp*<br>
│   ├── perfmon.cpp - *Performance monitor and tracker (allows the engine to adjust loads to improve performance)*<br>
│   └── perfmon.hpp - *Header file for perfmon.hpp*<br>
└── demo.cpp - *An interactive demo designed to show off the project's capabilities and functionality*<br>
