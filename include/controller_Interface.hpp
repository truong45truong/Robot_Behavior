#ifndef __CONTROLLER_INTERFACE_HPP__
#define __CONTROLLER_INTERFACE_HPP__
#include <iostream>

class IController{
public:
    virtual void Init(const std::string&) = 0;
    virtual void Export() = 0;
    virtual void Start() = 0;
};

#endif