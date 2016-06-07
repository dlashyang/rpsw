#include <iostream>
#include <sstream>

#include "simple_msg_dispatcher.h"

simple_msg_dispatcher::~simple_msg_dispatcher()
{
    std::cout<<"~simple_msg_dispatcher"<<std::endl;
}

int simple_msg_dispatcher::register_hw(cmm_hw_res* p)
{
    if (p == NULL) {
        std::cout<<"NULL hw_res pointer!"<<std::endl;
        return -1;
    }

    _res = p;
    return 0;
}

int simple_msg_dispatcher::deregister_hw()
{
    _res = NULL;
    return 0;
}

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
        readout vol(5);
        for(int i=0; i<5; i++) {
            _res->get_volt_readout(0, vol);
        }
        ss<<"Voltage is "<<vol.get_value();
    } else if (msg=="get temperature") {
        readout temp(3);
        for (int i=0; i<3; i++) {
            _res->get_thermal_readout(0, temp);
        }
        ss<<"Temperature is "<<temp.get_value();
    } else {
        std::cout<<"unknown message: "<<msg<<std::endl;
        ss<<"Unknown message!";
        ret = -1;
    }

    reply = ss.str();
    return ret;
}
