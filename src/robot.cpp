#ifndef __ROBOT_CPP__
#define __ROBOT_CPP__
#include "../include/robot.hpp"


Robot* Robot::instance_ = nullptr;

Robot* Robot::Instance(){
    if(instance_ == nullptr){
        instance_ = new Robot();
    }
    return instance_;
}

bool Robot::move_to(Point point){
    LOG_DEBUG("Robot is moving to point");
    grid_map_.point_marks.push_back(point);
}

#endif