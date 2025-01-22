#ifndef __MAIN_CPP__
#define __MAIN_CPP__
#include <iostream>
#include "../include/logger.hpp"
#include "../include/robot.hpp"
#include "../include/image_bmp.hpp"
#include "../include/objects.hpp"
int main(){

    // check logger
    LOG_DEBUG("Maybe i can touch this button...");
    
    LOG_INFO("Pressure is dropping...");

    Robot::Instance()->move_to(Point{1,2});

    Image img(200, 200);

    // Draw a red rectangle
    for (int y = 50; y < 150; ++y) {
        for (int x = 50; x < 150; ++x) {
            img.setPixel(x, y, 255, 0, 0); // Red color
        }
    }

    // Save the image
    img.saveBMP("output.bmp");
    return 0;
}

#endif