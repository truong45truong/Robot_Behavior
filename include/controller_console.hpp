#ifndef __CONTROLLER_CONSOLE_HPP
#define __CONTROLLER_CONSOLE_HPP

#include "controller_Interface.hpp"

class ControllerConsole : public IController {
public:
    void Init(const std::string& file_path) override;
    void Export() override;
    void Start() override;
private:
    int size_grid_ = 0;
};

#endif
