#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include "../include/logger.hpp"
#include "../include/robot.hpp"
#include "../include/objects.hpp"
int main(){

    // check logger
    LOG_DEBUG("Maybe i can touch this button...");
    
    LOG_INFO("Pressure is dropping...");

    Robot::Instance()->move_to(Point{1,2});
    return 0;
}

#endif