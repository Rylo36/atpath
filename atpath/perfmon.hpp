#include <chrono>
#include <iostream>
#include <math.h>
#include <vector>


class Tmr{ //Performance monitor and load management
    private:
        std::vector<int> fps_history; //History of fps values measured. Used to better estimate the load value
        int current_count; //Current frame count
        int last_time; //Last time (int from epoch) the current count was reset. 
        void clean_history();
        int getE(); //Get seconds since the epoch
    public:
    int target_fps; //Target framerate that the load value is based on
    int getFPS();
    float load; //Value of how loaded the system is (high value = significant load)
    void update(); //Should be ran every frame or else measurements will be off
    Tmr(int t_fps);
};