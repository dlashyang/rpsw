#include <unistd.h>
#include <iostream>

#include "rpsw_fault_scanner.h"
#include "rpsw_alarm_sender.h"
#include "readout.h"

rpsw_fault_scanner::~rpsw_fault_scanner()
{
    std::cout<<"~rpsw_fault_scanner"<<std::endl;
}

void rpsw_fault_scanner::start()
{
    _stop=false;
    _thrd.start(*this);
}

void rpsw_fault_scanner::stop()
{
    _stop=true;
    _thrd.join();
}

void rpsw_fault_scanner::run()
{
    std::cout<<"fault_scanner is running"<<std::endl;

    //Poco::Net::SocketAddress srv_addr("127.0.0.1:19993");
    //Poco::Net::DatagramSocket socket;
    //socket.connect(srv_addr);

    readout t(1);
    readout v(5);

    while(!_stop) {
        if (0 != _hw_res->get_thermal_readout(1, t)) {
            std::cout<<"temperature read fault!"<<std::endl;
            _sender->send("temperature read fault!");
        } else {
            //t.set_value(temperature/100);
            if (t.get_value() > 150) {
                std::cout<<"temperature fault!"<<std::endl;
                _sender->send("temperature fault!");
            }
        }

        int32_t voltage=0;
        if (0 != _hw_res->get_volt_readout(1, v)) {
            std::cout<<"voltage read fault!"<<std::endl;
            _sender->send("voltage read fault!");
        } else {
            int32_t ret = v.get_value(voltage);
            if (ret !=0 || voltage>230 || voltage<210) {
                std::cout<<"voltage fault!"<<std::endl;
                _sender->send("voltage fault!");
            }
        }

        sleep(5);
    }
}
