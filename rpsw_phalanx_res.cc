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

inline int phalanx_hw_res::read_dummy_data(const std::string& file, std::vector<uint32_t>& data)
{
    std::ifstream ifs(file.c_str(), std::ifstream::in);
    if (ifs.is_open()) {
        while (true) {
            std::string line;
            std::getline (ifs,line);
            if (line.size()==0) {
                break;
            }
            std::size_t pos=line.find(":");
            std::string readout=line.substr(pos+1);
            data.push_back(atoi(readout.c_str()));
        }
    } else {
        std::cout<<"read file failed: "<<file<<std::endl;
        return -1;
    }

    ifs.close();
    return 0;
}

int phalanx_hw_res::init(const std::string& dummy_file_name)
{
    std::string temperature(dummy_file_name);

    read_dummy_data(dummy_file_name+("_temp"), _dummy_temp);
    read_dummy_data(dummy_file_name+("_vol"), _dummy_vol);

    std::cout<<_dummy_temp.size()<<std::endl;
    std::cout<<_dummy_vol.size()<<std::endl;
    return 0;
}

int phalanx_hw_res::get_card_status(uint32_t& card_status)
{
    card_status=1;

    return 0;
}

int phalanx_hw_res::get_volt_readout(uint8_t id, int32_t& readout)
{
    Poco::Timestamp::TimeDiff elapsed=_start_timer.elapsed();
    readout=_dummy_vol[elapsed/1000000];

    std::cout<<"time is "<<(elapsed/1000000)<<", readout is "<<readout<<std::endl;

    return 0;
}

int phalanx_hw_res::get_thermal_readout(uint8_t id, int32_t& readout)
{
    Poco::Timestamp::TimeDiff elapsed=_start_timer.elapsed();
    readout=_dummy_temp[elapsed/1000000];

    std::cout<<"time is "<<(elapsed/1000000)<<", readout is "<<readout<<std::endl;

    return 0;
}

phalanx_hw_res::~phalanx_hw_res()
{
    std::cout<<"~phalanx_hw_res"<<std::endl;
}
