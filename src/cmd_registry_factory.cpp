#ifndef __CMD_REGISTRY_FACTORY_CPP__
#define __CMD_REGISTRY_FACTORY_CPP__

#include "../include/cmd_registry_factory.hpp"
CMDHandler* CMDRegistryFactory::CreateInstance(const CMDType& cmd_type){
    switch(cmd_type){
        case CMDType::MoveTo:
            return new CMDMoveTo();
        case CMDType::LineTo:
            return new CMDLineTo();
        case CMDType::Undefine:
            return nullptr;
        default:
            return nullptr;
    }
}
#endif
