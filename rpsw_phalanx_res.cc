#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>
#include "rpsw_phalanx_res.h"

int phalanx_hw_res::init(uint32_t base_addr)
{
    _base_addr=base_addr;

    return 0;
}

int phalanx_hw_res::init(const std::string& dummy_file_name)
{
    std::ifstream ifs(dummy_file_name.c_str(), std::ifstream::in);
    if (ifs.is_open()) {
        while (true) {
            std::string line;
            std::getline (ifs,line);
            if (line.size()==0) {
                break;
            }
            std::size_t pos=line.find(":");
            std::string readout=line.substr(pos);
            _dummy_data.push_back(atoi(readout.c_str()));
        }
    } else {
        std::cout<<"read file failed."<<std::endl;
    }

    std::cout<<_dummy_data.size()<<std::endl;
    ifs.close();
    return 0;
}

int phalanx_hw_res::get_card_status(uint32_t& card_status)
{
    card_status=1;

    return 0;
}

int phalanx_hw_res::get_volt_readout(uint8_t id, int32_t& readout)
{
    readout=id*3+58;

    return 0;
}

int phalanx_hw_res::get_thermal_readout(uint8_t id, int32_t& readout)
{
    readout=id%6+13;

    return 0;
}

phalanx_hw_res::~phalanx_hw_res()
{
    std::cout<<"~phalanx_hw_res"<<std::endl;
}
