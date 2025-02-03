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
#include "../include/controller_file.hpp"
#include "../include/controller_console.hpp"

int main(){
    LOG_INFO("====================START ROBOT======================");
    IController* controller;
    std::string command_file_path;
    while(true){
        std::cout << "=========================OPTION=========================" << std::endl;
        std::cout << "| 1. Control robot with command file. " << std::endl;
        std::cout << "| 2. Control robot with command console. " << std::endl;
        std::cout << "| 0. Exit . " << std::endl;
        std::cout << "========================================================" << std::endl;
        std::cout << "Enter yout choice: ";
        int choice;

        std::cin >> choice;
        switch (choice) {
            case 0:
                LOG_INFO("====================END ROBOT======================");
                break;
            case 1:
                // ... logic controller file
                controller = new ControllerFile();
                std::cout << "Enter path file command: ";
                std::cin.ignore();
                std::getline(std::cin,command_file_path);
                controller->Init(command_file_path);
                controller->Start();
                controller->Export();
                break;
            case 2:
                // ... logic controller console
                controller = new ControllerConsole();
                controller->Init("");
                controller->Start();
                controller->Export();
                break;
            default:
                std::cout << "Invalid choice! Please enter 0, 1, or 2." << std::endl;
                continue;
        }
        if(choice == 0) break;
    }

    std::ifstream file("commands.txt");
    if (!file.is_open()) {
        LOG_ERROR ("Error: Could not open the file commands.txt.");
        return 1;
    }

    // bitmap_data::RGB_24 rgb_red(0,0,0);

    // ImageBMP img(500, 500);
    // std::string line;
    // while (std::getline(file, line)) {
    //     int size;
    //     int width_image = img.GetWidth();
    //     int height_image = img.GetHeigth();
    //     int padding = 0.05*img.GetWidth();
    //     Point point;
    //     if (Utils::ToUpperCase(line).find("DIMENSION") != std::string::npos) {
    //         Utils::ExtractDimension(line,size);
    //         if(size < 1 || size > 100){
    //             LOG_WARN("The Dimension is out of bounds and it will be set to 5 . Dimension on range[1 : 100]");
    //             size = 5;
    //         }
    //         Robot::Instance()->CreateGridSize(size);
    //     } else if ( 
    //         line.find("MOVE_TO") != std::string::npos 
    //         || line.find("LINE_TO") != std::string::npos) {
            
    //         if(Utils::ExtractCoordinates(line,point)){
    //             if(line.find("MOVE_TO") ==  std::string::npos){
    //                 if(Robot::Instance()->LineTo(point)){
    //                     LOG_INFO("Robot line to point success");
    //                 }else{
    //                     LOG_INFO("Robot line to point fail");
    //                 }
    //             }else{
    //                 if(Robot::Instance()->MoveTo(point)){
    //                     LOG_INFO("Robot move to point success");
    //                 }else{
    //                     LOG_INFO("Robot move to point fail");
    //                 }
    //             }
    //         }else{
    //             LOG_WARN("Extract coordinates failed, please check the command in the file");
    //         }
    //     }else{
    //         LOG_WARN(("Command : " + line + " wrong, please check in file commands.txt").c_str());
    //     }
    // }
    // Robot::Instance()->ExportGridMap(img);
    // file.close();
    // // Save the image
    // img.saveBMP_RGB24("output.bmp");
    return 0;
}

#endif