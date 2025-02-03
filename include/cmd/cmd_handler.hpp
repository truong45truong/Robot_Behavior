#ifndef __CMD_INTERFACE_HPP__
#define __CMD_INTERFACE_HPP__

#include "../objects.hpp"
#include <vector>

class CMDHandler {
public:
    virtual void Init(const Point& start){
        point_start_ = start;
    }
    virtual bool Execute(const Point&, GridMap&) = 0;
    virtual std::vector<Point> GetPointMark(){
        return {};
    };
protected:
    Point point_start_;
    Point point_destination_;
};

#endif
