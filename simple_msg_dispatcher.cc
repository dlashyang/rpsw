#include <iostream>
#include <sstream>

#include "simple_msg_dispatcher.h"

int simple_msg_dispatcher::proc_msg(const std::string& msg, std::string& reply)
{
    if (_res == NULL) {
        reply = "No valid hardware!";
        return -1;
    }

    int ret=0;
    std::stringstream ss;

    std::cout<<"Received message: "<<msg<<std::endl;

    if (msg=="get card status") {
        uint32_t card_stat=0;
        _res->get_card_status(card_stat);
        ss<<"Card Status is "<<card_stat;
    } else if (msg=="get voltage") {
        int32_t vol=0;
        _res->get_volt_readout(0, vol);
        ss<<"Voltage is "<<vol;
    } else if (msg=="get temperature") {
        int32_t temp=0;
        _res->get_thermal_readout(0, temp);
        ss<<"Temperature is "<<temp;
    } else {
        std::cout<<"unknown message: "<<msg<<std::endl;
        ss<<"Unknown message!";
        ret = -1;
    }

    reply = ss.str();
    return ret;
}
