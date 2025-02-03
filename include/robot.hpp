#ifndef __ROBOT_HPP__
#define __ROBOT_HPP__

#include<iostream>
#include "objects.hpp"
#include "logger.hpp"
#include "utils.hpp"
#include "image_bmp.hpp"
#include "./cmd/cmd_line_to.hpp"
#include "./cmd/cmd_move_to.hpp"
class Robot {
public:
    static Robot* Instance();
    bool ExecuteCMD(CMDHandler* cmd_handler,const Point& point);
    void CreateGridSize(const int& size) noexcept;
    void ExportGridMap(ImageBMP& img) noexcept;
    void operator=(const Robot& ) = delete;
    Robot(const Robot&) = delete;
    GridMap GetGridMap() const {
        return grid_map_;
    }
private:
    static Robot* instance_;
    GridMap grid_map_;
    Point point_current_;
    Robot() = default;
};

#endif
