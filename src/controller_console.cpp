#ifndef __CONTROLLER_CONSOLE_CPP__
#define __CONTROLLER_CONSOLE_CPP__
#include "../include/controller_console.hpp"
#include "../include/logger.hpp"
#include "../include/robot.hpp"
#include "../include/image_bmp.hpp"
#include "../include/cmd_registry_factory.hpp"
#include <iostream>

void ControllerConsole::Init(const std::string& file_path = ""){
    
}

void ControllerConsole::Start(){
    bitmap_data::RGB_24 rgb_red(0,0,0);
    ImageBMP img(500,500);
    std::string line;
    int size;
    int width_image = img.GetWidth();
    int height_image = img.GetHeigth();
    int padding = 0.05*img.GetWidth();
    Point point;
    bool create_grid = false;
    std::cout << "===================MENU CMD====================" << std::endl;
    std::cout << "| 1. Move to: >> MOVE_TO x,y <<, Ex: MOVE_TO 1,1. " << std::endl;
    std::cout << "| 2. Line to: >> LINE_TO x,y << , Ex: LINE_TO 1,1. " << std::endl;
    std::cout << "| 3. Show Grid Map: SHOW" << std::endl;
    std::cout << "| 3. Exit : END" << std::endl;
    bool ign_buff_cin = false;
    while (true) {
        std::cout << "Enter CMD: " ;
        if(!ign_buff_cin){
            std::cin.ignore();
            ign_buff_cin = true;
        }
        std::getline(std::cin, line);
        if(Utils::ToUpperCase(line).find("END") != std::string::npos){
            break;
        }
        if(Utils::ToUpperCase(line).find("SHOW") != std::string::npos){
            this->Export();
            continue;
        }
        if (line.find("DIMENSION") != std::string::npos) {
            Utils::ExtractDimension(line,size);
            if(size < 2 || size > 50){
                LOG_WARN("The Dimension is out of bounds and it will be set to 5 . Dimension on range[2 : 50]");
                size = 5;
            }
            Robot::Instance()->CreateGridSize(size);
            create_grid = true;
            size_grid_ = size;
        } else if ( 
            line.find("MOVE_TO") != std::string::npos 
            || line.find("LINE_TO") != std::string::npos) {
            
            if(!create_grid) {
                LOG_WARN("The Dimension must be created first. Dimension on range[2 : 50] --> Please Enter:  DIMENSION [size] ");
            }
            if(Utils::ExtractCoordinates(line,point)){
                CMDHandler* cmd_handler;
                if(line.find("MOVE_TO") ==  std::string::npos){
                    cmd_handler = CMDRegistryFactory::CreateInstance(CMDType::LineTo);
                }else{
                    cmd_handler = CMDRegistryFactory::CreateInstance(CMDType::MoveTo);
                }

                if(Robot::Instance()->ExecuteCMD(cmd_handler,point)){
                    LOG_INFO("Robot line to point success");
                }else{
                    LOG_INFO("Robot line to point fail");
                }
            }else{
                LOG_WARN("Extract coordinates failed, please check the command");
            }
        }else{
            LOG_WARN(("Command : " + line + " wrong, please check the command").c_str());
        }
    }
}

void ControllerConsole::Export(){
    int col_size = 0;
    double ratio_scale = size_grid_ / 8; // max
    if(ratio_scale >= 1.5){
        col_size = size_grid_ / (ratio_scale*3);
        if(col_size < 2)col_size = 2;
    }else{
        col_size = size_grid_;
        ratio_scale = 1;
    }
    std::vector<Point> list_point_mark =  Robot::Instance()->GetGridMap().point_marks;
    std::vector<Point> list_marked = {};
    auto check_mark = [&list_point_mark, &list_marked](int x, int y) -> bool {
        bool status_marked = std::any_of(list_marked.begin(), list_marked.end(), 
                           [x, y](const Point& p) { return p.x == x && p.y == y; });
        if(status_marked) return false;
        return std::any_of(list_point_mark.begin(), list_point_mark.end(), 
                           [x, y](const Point& p) { return p.x == x && p.y == y; });
    };
    // for(int i = 0 ; i < list_point_mark.size() ; i ++){
    //     std::cout << "X: " << list_point_mark[i].x << " Y: " << list_point_mark[i].y << std::endl;
    // }
    std::cout << std::string(col_size * size_grid_, '-') << std::endl;
    for (int i = 0; i < size_grid_; i++) {
        if(col_size / 3 < 1){
            for (int j = 0; j < size_grid_ ; j++) {
                if(check_mark(j,i)){
                    std::cout << "+" << std::string(col_size - 2, ' ') << "|";
                    list_marked.push_back(Point(j,i));
                }else{
                    std::cout << std::string(col_size - 1, ' ') << "|";
                }
            }
            std::cout << std::endl;
        }
        for (int row = 0; row < col_size / 3; row++){
            std::cout << "|";
            for (int j = 0; j < size_grid_ ; j++) {
                if(check_mark(j,i)){
                    std::cout << "+" << std::string(col_size - 2, ' ') << "|";
                    list_marked.push_back(Point(j,i));
                }else{
                    std::cout << std::string(col_size - 1, ' ') << "|";
                }
            }
            std::cout << std::endl;
        }
        std::cout << std::string(col_size * size_grid_, '-') << std::endl;
    }
}
#endif;