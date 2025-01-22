#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include<iostream>
#include "objects.hpp"
#include "logger.hpp"
#include "utils.hpp"
#include "image_bmp.hpp"
class Robot {
public:
    static Robot* Instance();
    bool MoveTo(const Point& point);
    bool LineTo(const Point& point);
    // bool CircleTo(Point point);
    void CreateGridSize(const int& size) noexcept;
    void ExportGridMap(ImageBMP& img) noexcept;
    void operator=(const Robot& ) = delete;
    Robot(const Robot&) = delete;
private:
    static Robot* instance_;
    GridMap grid_map_;
    Point point_current_;
    Robot() = default;
};

#endif
