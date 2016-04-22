#ifndef RPSW_PHALANX_RES_H
#define RPSW_PHALANX_RES_H

#include <vector>
#include <stdint.h>

#include <Poco/Timestamp.h>

#include "rpsw_common_hw_res.h"

class dummy_hw_res:public cmm_hw_res
{
    private:
        std::vector<int32_t> _temp;
        std::vector<int32_t> _vol;
        std::string _data_file;
        Poco::Timestamp _start;

        inline int read_data(const std::string& file, std::vector<int32_t>& data);

    public:
        dummy_hw_res(const std::string& file);
        virtual ~dummy_hw_res();
        int init();

        virtual int get_card_status(uint32_t& card_status);
        virtual int get_volt_readout(uint8_t id, int32_t& readout);
        virtual int get_thermal_readout(uint8_t id, int32_t& readout);
};

class dummy_factory: public hw_res_factory
{
    public:
        dummy_factory(std::string dummy_file): _file(dummy_file) {};

        virtual cmm_hw_res* create_hw_res()
        {
            return (new dummy_hw_res(_file));
        }

    private:
        std::string _file;
};
#endif //#ifndef RPSW_PHALANX_RES_H
