#include <unistd.h>
#include <iostream>
#include "rpsw_fault_scanner.h"

rpsw_fault_scanner::~rpsw_fault_scanner()
{
    if(_hw_res != NULL) {
        _hw_res=NULL;
    }
}

void rpsw_fault_scanner::run()
{
    std::cout<<"fault_scanner is running"<<std::endl;

    while(!_stop) {
        int32_t temperature=0;
        _hw_res->get_thermal_readout(1, temperature);
        temperature/=100;
        if (temperature>150) {
            std::cout<<"temperature fault!"<<std::endl;
        }

        int32_t voltage=0;
        _hw_res->get_volt_readout(1, voltage);
        if (voltage>230 || voltage<210) {
            std::cout<<"voltage fault!"<<std::endl;
        }

        sleep(5);
    }
}
