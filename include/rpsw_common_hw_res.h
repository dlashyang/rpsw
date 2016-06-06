#ifndef RPSW_COMMON_HW_RES_H
#define RPSW_COMMON_HW_RES_H

#include <stdint.h>
#include <memory>
#include "readout.h"

class cmm_hw_res
{
    public:
        virtual ~cmm_hw_res(){};
        virtual int init()=0;

        virtual int get_card_status(uint32_t& card_status)=0;
        virtual int get_volt_readout(uint8_t id, readout& readout)=0;
        virtual int get_thermal_readout(uint8_t id, readout& readout)=0;
};

typedef std::auto_ptr<cmm_hw_res> cmm_hw_res_t;
class hw_res_factory
{
    virtual cmm_hw_res_t create_hw_res()=0;
};

#endif //#ifndef RPSW_COMMON_HW_RES_H
