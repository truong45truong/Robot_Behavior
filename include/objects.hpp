#ifndef __DATA_CONTAINER_HPP
#define __DATA_CONTAINER_HPP
#include <iostream>
#include <vector>

struct Point {
    int x = 0;
    int y = 0;
};

struct GridMap {
    int width = 0;
    int height = 0;
    std::vector<Point> point_marks;
}


#endif
