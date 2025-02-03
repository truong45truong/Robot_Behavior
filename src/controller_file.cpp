#ifndef __CONTROLLER_FILE__CPP__
#define __CONTROLLER_FILE__CPP__
#include "../include/controller_file.hpp";
#include "../include/logger.hpp"
#include "../include/robot.hpp"
#include "../include/image_bmp.hpp"
#include "../include/cmd_registry_factory.hpp"
#include <iostream>
#include <fstream>

void ControllerFile::Init(const std::string& file_path) {
    cmd_file_ = std::ifstream("commands.txt");
    if (!cmd_file_.is_open()) {
        LOG_ERROR ("Error: Could not open the file commands.txt.");
    }    
}

void ControllerFile::Start(){
    bitmap_data::RGB_24 rgb_red(0,0,0);
    ImageBMP img(2000,2000);
    std::string line;
    while (std::getline(cmd_file_, line)) {
        int size;
        int width_image = img.GetWidth();
        int height_image = img.GetHeigth();
        int padding = 0.05*img.GetWidth();
        Point point;
        if (Utils::ToUpperCase(line).find("DIMENSION") != std::string::npos) {
            Utils::ExtractDimension(line,size);
            if(size < 2 || size > 100){
                LOG_WARN("The Dimension is out of bounds and it will be set to 5 . Dimension on range[2 : 100]");
                size = 5;
            }
            Robot::Instance()->CreateGridSize(size);
        } else if ( 
            line.find("MOVE_TO") != std::string::npos 
            || line.find("LINE_TO") != std::string::npos) {
            
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
                LOG_WARN("Extract coordinates failed, please check the command in the file");
            }
        }else{
            LOG_WARN(("Command : " + line + " wrong, please check in file commands.txt").c_str());
        }
    }
    cmd_file_.close();
}

void ControllerFile::Export(){
    ImageBMP img(2000,2000);
    Robot::Instance()->ExportGridMap(img);
    img.saveBMP_RGB24("output_file.bmp");
}
#endif
