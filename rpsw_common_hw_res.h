#ifndef RPSW_COMMON_HW_RES_H
#define RPSW_COMMON_HW_RES_H

#include <stdint.h>

class cmm_hw_res
{
    public:
        virtual ~cmm_hw_res(){};
        virtual int init()=0;

        virtual int get_card_status(uint32_t& card_status)=0;
        virtual int get_volt_readout(uint8_t id, int32_t& readout)=0;
        virtual int get_thermal_readout(uint8_t id, int32_t& readout)=0;
};

class hw_res_factory
{
    virtual cmm_hw_res* create_hw_res()=0;
};

#endif //#ifndef RPSW_COMMON_HW_RES_H
