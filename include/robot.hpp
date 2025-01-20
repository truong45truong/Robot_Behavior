#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include<iostream>
#include "objects.hpp"
#include "logger.hpp"

class Robot {
public:
    bool move_to(Point point);
    bool line_to(Point point);
    bool circle_to(Point point);

    void operator=(const Robot& ) = delete;
    Robot(const Robot&) = delete;

    static Robot* Instance();
private:
    static Robot* instance_;
    GridMap grid_map_;
    
    Robot() = default;
};

#endif
