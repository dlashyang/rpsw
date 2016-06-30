#include <stdlib.h>
#include <string>
#include <fstream>
#include <iostream>

#include "rpsw_dummy_res.h"

dummy_hw_res::dummy_hw_res(const std::string& file):_temp(0), _vol(0),
                                _log(Poco::Logger::get("rpswd.hw_res"))
{
    _data_file = file;
}

inline int dummy_hw_res::read_data(const std::string& file, std::vector<int32_t>& data)
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
        rpsw_critical(_log, "%s: read file failed!", std::string(__func__));
        return -1;
    }

    ifs.close();
    return 0;
}

int dummy_hw_res::init()
{
    read_data(_data_file+("_temp"), _temp);
    read_data(_data_file+("_vol"), _vol);

    int t_num = _temp.size();
    rpsw_debug(_log, "We have temperature data for %d:%d:%d",
            t_num/3600, (t_num%3600)/60, t_num%60);

    int v_num = _vol.size();
    rpsw_debug(_log, "We have voltage data for %d:%d:%d",
            v_num/3600, (v_num%3600)/60, v_num%60);

    return 0;
}

int dummy_hw_res::get_card_status(uint32_t& card_status)
{
    card_status=1;

    return 0;
}

int dummy_hw_res::get_volt_readout(uint8_t id, readout& readout)
{
    int ret = 0;
    int32_t v = 0;

    Poco::Timestamp::TimeDiff elapsed=_start.elapsed();

    uint32_t idx = elapsed/1000000;
    if (idx>=_vol.size()) {
        rpsw_error(_log, "no valid data");
        ret = -1;
    }

    v =_vol[idx];
    readout.set_value(v);

    rpsw_debug(_log, "Time is %ld, readout is %d", elapsed/1000000, v);

    return ret;
}

int dummy_hw_res::get_thermal_readout(uint8_t id, readout& readout)
{
    int ret = 0;
    int32_t v = 0;

    Poco::Timestamp::TimeDiff elapsed=_start.elapsed();
    try {
        v =_temp.at(elapsed/1000000);
    }
    catch (const std::out_of_range& e){
        rpsw_error(_log, "no valid data");
        ret = -1;
    }


    readout.set_value(v/100);
    rpsw_debug(_log, "Time is %ld, readout is %d", elapsed/1000000, v);

    return ret;
}

dummy_hw_res::~dummy_hw_res()
{
    rpsw_trace(_log, std::string(__func__));
}
