#ifndef __CMD_REGISTRY_FACTORY_HPP__
#define __CMD_REGISTRY_FACTORY_HPP__

#include "./cmd/cmd_handler.hpp"
#include "./cmd/cmd_line_to.hpp"
#include "./cmd/cmd_move_to.hpp"

enum CMDType { MoveTo, LineTo, Undefine }; 

class CMDRegistryFactory {
public:
    static CMDHandler* CreateInstance(const CMDType& type);
};

#endif