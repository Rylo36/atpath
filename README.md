# AtPath
## What is AtPath?
At path is an easy to use path finding library written in C++ for SFML based applications. 
## How to Install
Simply copy the atpath directory over to your project (or to /usr/include/ if you wish) and include the atpath/handler.hpp file

After including, all components of the library are stored under the **at** namespace



## Project Layout
├── atpath - *The main library folder* <br>
│   ├── engine.cpp - *The pathfinding engine (what actually generates the routes)*<br>
│   ├── handler.cpp - *Contains the atpath class which holds and prepares all the needed data for the engine*<br>
│   ├── handler.hpp - *Header file for handler.cpp and engine.cpp*<br>
│   ├── perfmon.cpp - *Performance monitor and tracker (allows the engine to adjust loads to improve performance)*<br>
│   └── perfmon.hpp - *Header file for perfmon.hpp*<br>
└── demo.cpp - *An interactive demo designed to show off the project's capabilities and functionality*<br>
