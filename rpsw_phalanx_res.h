#ifndef RPSW_PHALANX_RES_H
#define RPSW_PHALANX_RES_H

#include <vector>
#include <stdint.h>

#include "rpsw_common_hw_res.h"

class phalanx_hw_res:public cmm_hw_res
{
    private:
        uint32_t _base_addr;
        std::vector<uint32_t> _dummy_data;

    public:
        phalanx_hw_res():_base_addr(0),_dummy_data(0){};
        virtual ~phalanx_hw_res();
        int init(uint32_t base_addr);
        int init(const std::string& dummy_file_name);

        virtual int get_card_status(uint32_t& card_status);
        virtual int get_volt_readout(uint8_t id, int32_t& readout);
        virtual int get_thermal_readout(uint8_t id, int32_t& readout);
};

#endif //#ifndef RPSW_PHALANX_RES_H
