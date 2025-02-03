#ifndef __CONTROLLER_FILE_HPP__
#define __CONTROLLER_FILE_HPP__
#include "controller_Interface.hpp"
#include "image_bmp.hpp"
#include <fstream>

class ControllerFile : public IController {
public:
    void Init(const std::string& file_path) override;
    void Export() override;
    void Start() override; 
private:
    std::ifstream cmd_file_;
};

#endif