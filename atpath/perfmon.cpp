#include "perfmon.hpp"

Tmr::Tmr(int t_fps){target_fps = t_fps;}

void Tmr::clean_history(){
    while(fps_history.size() > 300) fps_history.erase(fps_history.begin());
}

int Tmr::getE(){
    return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void Tmr::update(){
    current_count += 1;
   
    if(last_time != getE()){
        last_time = getE();
        fps_history.push_back(current_count);
        current_count = 0;
        clean_history(); 
        //Recalculate the load value
        load = 0.f;
        for(int f : fps_history) load += (f / target_fps);
        load /= fps_history.size();
    }
}