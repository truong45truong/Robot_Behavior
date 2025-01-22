#ifndef __UTILS_HPP__
#define __UTILS_HPP__

#include <iostream>
#include <vector>
#include <algorithm>
#include <cctype>
#include "objects.hpp"
#include "logger.hpp"
#include <regex>

class Utils {
public:
    static inline std::string ToUpperCase(std::string &str) noexcept{
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        return str;
    }

    static inline bool ExtractCoordinates(const std::string& str, Point& point) {
        std::regex pattern(R"((LINE_TO|MOVE_TO)\s*(-?\d+),\s*(-?\d+))");
        std::smatch match;

        if (std::regex_search(str, match, pattern)) {
            int x = std::stoi(match[2].str());
            int y = std::stoi(match[3].str());
            point.x = x;
            point.y = y;
            LOG_DEBUG(("Extract Coordinates from cmd : " + std::to_string(x) + "," + std::to_string(y)).c_str());
            return true;
        }
        return false;
    } 

    static inline bool ExtractDimension(const std::string& str, int& size) {
        std::regex pattern(R"((DIMENSION)\s*(-?\d+))");
        std::smatch match;
        if (std::regex_search(str, match, pattern)) {
            size = std::stoi(match[2].str());
            return true;
        }
        return false;
    }

    static inline bool IsPointOnLineSegment(const Point& point_0, const Point& point_1, const Point& point_2){
        if ((point_0.x - point_1.x) * ( point_2.y - point_1.y) != ( point_0.y - point_1.y) * ( point_2.x - point_1.x)) {
            return false;
        }
        
        if (point_0.x < std::min(point_1.x, point_2.x) || point_0.x > std::max(point_1.x, point_2.x)) {
            return false;
        }
        if (point_0.y < std::min(point_1.y, point_2.y) || point_0.y > std::max(point_1.y, point_2.y)) {
            return false;
        }
    
        return true;
    }
private:
    Utils() = default;
    Utils(const Utils&) = delete;
    void operator=(const Utils&) = delete;
};

#endif