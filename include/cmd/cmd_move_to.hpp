#ifndef __CMD_MOVE_TO_HPP__
#define __CMD_MOVE_TO_HPP__
#include "cmd_handler.hpp"
#include "../logger.hpp"

class CMDMoveTo : public CMDHandler {
public:
    bool Execute(const Point& destination, GridMap& grid_map) override {
        point_destination_ = destination;
        if( point_destination_.x < 0 || point_destination_.x >  grid_map.width - 1 || point_destination_.y < 0 || point_destination_.y >  grid_map.height - 1 ){
            LOG_WARN("Destination out of bounds");
            return false;
        }
        return true;
    }
};

#endif
