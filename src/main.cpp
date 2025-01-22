#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>

#include "../include/logger.hpp"
#include "../include/robot.hpp"
#include "../include/image_bmp.hpp"
#include "../include/objects.hpp"
#include "../include/utils.hpp"

int main(){
    LOG_INFO("====================START ROBOT======================");
    std::ifstream file("commands.txt");
    if (!file.is_open()) {
        LOG_ERROR ("Error: Could not open the file commands.txt.");
        return 1;
    }

    bitmap_data::RGB_24 rgb_red(0,0,0);

    ImageBMP img(1024, 1024);
    std::string line;
    while (std::getline(file, line)) {
        int size;
        int width_image = img.GetWidth();
        int height_image = img.GetHeigth();
        int padding = 0.05*img.GetWidth();
        Point point;
        if (Utils::ToUpperCase(line).find("DIMENSION") != std::string::npos) {
            Utils::ExtractDimension(line,size);
            if(size < 1 || size > 100){
                LOG_WARN("The Dimension is out of bounds and it will be set to 5 . Dimension on range[1 : 100]");
                size = 5;
            }
            Robot::Instance()->CreateGridSize(size);
        } else if ( 
            line.find("MOVE_TO") != std::string::npos 
            || line.find("LINE_TO") != std::string::npos) {
            
            if(Utils::ExtractCoordinates(line,point)){
                if(line.find("MOVE_TO") ==  std::string::npos){
                    if(Robot::Instance()->LineTo(point)){
                        LOG_INFO("Robot line to point success");
                    }else{
                        LOG_INFO("Robot line to point fail");
                    }
                }else{
                    if(Robot::Instance()->MoveTo(point)){
                        LOG_INFO("Robot move to point success");
                    }else{
                        LOG_INFO("Robot move to point fail");
                    }
                }
            }else{
                LOG_WARN("Extract coordinates failed, please check the command in the file");
            }
        }
    }
    Robot::Instance()->ExportGridMap(img);
    file.close();
    // Save the image
    img.saveBMP_RGB24("output.bmp");
    return 0;
}

#endif