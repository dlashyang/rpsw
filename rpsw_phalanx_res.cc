#include <iostream>
#include "rpsw_phalanx_res.h"

int phalanx_hw_res::init(uint32_t base_addr)
{
    _base_addr=base_addr;

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
