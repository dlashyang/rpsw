#ifndef RPSW_PHALANX_RES_H
#define RPSW_PHALANX_RES_H

#include <vector>
#include <stdint.h>

#include <Poco/Timestamp.h>

#include "rpsw_common_hw_res.h"
#include "rpsw_log.h"

class dummy_hw_res:public cmm_hw_res
{
    private:
        std::vector<int32_t> _temp;
        std::vector<int32_t> _vol;
        std::string _data_file;
        Poco::Timestamp _start;
        Poco::Logger& _log;

        inline int read_data(const std::string& file, std::vector<int32_t>& data);
        dummy_hw_res(const dummy_hw_res&);
        dummy_hw_res& operator=(const dummy_hw_res&);

    public:
        dummy_hw_res(const std::string& file);
        virtual ~dummy_hw_res();
        int init();

        virtual int get_card_status(uint32_t& card_status);
        virtual int get_volt_readout(uint8_t id, readout& readout);
        virtual int get_thermal_readout(uint8_t id, readout& readout);
};

class dummy_factory: public hw_res_factory
{
    public:
        dummy_factory(std::string dummy_file): _file(dummy_file) {};

        virtual cmm_hw_res_t create_hw_res()
        {
            return (cmm_hw_res_t(new dummy_hw_res(_file)));
        }

    private:
        std::string _file;
};
#endif //#ifndef RPSW_PHALANX_RES_H
