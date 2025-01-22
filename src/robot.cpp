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

bool Robot::MoveTo(const Point& point){
    LOG_INFO(("Robot move to x=" + std::to_string(point.x) + " y=" + std::to_string(point.y)).c_str());
    if( point.x < 0 || point.x >  grid_map_.width || point.y < 0 || point.y >  grid_map_.height ){
        LOG_WARN("Point out of bounds");
        return false;
    }
    point_current_ = point;
    LOG_DEBUG(("The current position of the robot is x=" + std::to_string(point_current_.x) + " y=" + std::to_string(point_current_.y)).c_str());
    return true;
}

bool Robot::LineTo(const Point& point){
    LOG_INFO(("Robot line to x=" + std::to_string(point.x) + " y=" + std::to_string(point.y)).c_str());
    if( point.x < 0 || point.x >  grid_map_.width || point.y < 0 || point.y >  grid_map_.height ){
        LOG_WARN("Point out of bounds");
        return false;
    }
    int start_x = std::min(point_current_.x, point.x);
    int end_x = std::max(point_current_.x, point.x);
    int start_y = std::min(point_current_.y, point.y);
    int end_y = std::max(point_current_.y, point.y);

    for(int i = start_x ; i <= end_x ; i ++ ){
        for(int j = start_y ; j <= end_y; j ++){
            if(Utils::IsPointOnLineSegment(Point(i,j), point_current_, point)){
                LOG_DEBUG(("Point x=" + std::to_string(i) + " y= " + std::to_string(j) + " is marked" ).c_str());
                grid_map_.point_marks.push_back(Point(i,j));
            }
        }
    }
    point_current_ = point;

    LOG_DEBUG(("The current position of the robot is x=" + std::to_string(point_current_.x) + " y=" + std::to_string(point_current_.y)).c_str());
    return true;
}

void Robot::CreateGridSize(const int& size) noexcept{
    LOG_INFO("Creating grid map size");
    grid_map_.width = size;
    grid_map_.height = size;
}

void Robot::ExportGridMap(ImageBMP& image) noexcept{
    LOG_INFO("Exporting grid map");
    bitmap_data::RGB_24 rgb_black(0,0,0);
    int height_image = image.GetHeigth();
    int width_image = image.GetWidth();
    int padding = width_image / (grid_map_.width + 1)*0.2;
    for(int line_x = 0 ; line_x <=  grid_map_.width; line_x ++){
        int x1 = 0 + padding;
        int y1 = line_x * (height_image / (grid_map_.width +1)) + padding;
        int x2 = width_image - padding;
        int y2 = line_x * (height_image / (grid_map_.width +1)) + padding;
        image.drawLine(x1, y1, x2, y2,rgb_black);
    }

    for(int line_y = 0 ; line_y <=  grid_map_.height; line_y ++){
        int x1 = line_y * (width_image / (grid_map_.height +1)) + padding;
        int y1 =0 + padding;
        int x2 = line_y * (height_image / (grid_map_.height +1)) + padding;
        int y2 = height_image - padding;
        image.drawLine(x1, y1, x2, y2,rgb_black);
    }

    for(int mark_index = 0 ; mark_index < grid_map_.point_marks.size() ; mark_index ++ ){
        Point point_mark {
            grid_map_.point_marks[mark_index].x*(width_image / (grid_map_.width +1)) + 2*padding,
            grid_map_.point_marks[mark_index].y*(height_image / (grid_map_.height +1)) + 2*padding
        };
        image.Mark(point_mark, int(padding/2),  rgb_black);
    }
}
#endif