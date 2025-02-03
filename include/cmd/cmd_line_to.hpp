#ifndef __CMD_LINE_TO_HPP__
#define __CMD_LINE_TO_HPP__
#include "cmd_handler.hpp"
#include "../logger.hpp"
#include "../utils.hpp"

class CMDLineTo : public CMDHandler {
public:
    bool Execute(const Point& destination, GridMap& grid_map) override {
        point_destination_ = destination;

        if( point_destination_.x < 0 || point_destination_.x >  grid_map.width - 1 || point_destination_.y < 0 || point_destination_.y >  grid_map.height - 1 ){
            LOG_WARN("Destination out of bounds");
            return false;
        }
        
        int start_x = std::min(point_start_.x, point_destination_.x);
        int end_x = std::max(point_start_.x, point_destination_.x);
        int start_y = std::min(point_start_.y, point_destination_.y);
        int end_y = std::max(point_start_.y, point_destination_.y);

        for(int i = start_x ; i <= end_x ; i ++ ){
            for(int j = start_y ; j <= end_y; j ++){
                if(Utils::IsPointOnLineSegment(Point(i,j), point_start_, point_destination_)){
                    grid_map.point_marks.push_back(Point(i,j));
                    m_list_point_mark.push_back(Point(i,j));
                    continue;
                }
                if(Utils::DistanceToLine(Point(i,j), point_start_, point_destination_) < 0.5 ){
                    grid_map.point_marks.push_back(Point(i,j));
                    m_list_point_mark.push_back(Point(i,j));
                    continue;
                }

            }
        }
    }

    std::vector<Point> GetPointMark() override {
        return m_list_point_mark;
    }
private:
    std::vector<Point> m_list_point_mark;
};

#endif
