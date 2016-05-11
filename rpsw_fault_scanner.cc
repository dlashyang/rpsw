#include <unistd.h>
#include <iostream>

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"

#include "rpsw_fault_scanner.h"

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

    Poco::Net::SocketAddress srv_addr("127.0.0.1:19993");
    Poco::Net::DatagramSocket socket;
    socket.connect(srv_addr);

    while(!_stop) {
        int32_t temperature=0;
        if (0 != _hw_res->get_thermal_readout(1, temperature)) {
            std::cout<<"temperature read fault!"<<std::endl;
            std::string msg("temperature read fault!");
            socket.sendBytes(msg.data(), msg.size());
        } else {
            temperature/=100;
            if (temperature>150) {
                std::cout<<"temperature fault!"<<std::endl;
                std::string msg("temperature fault!");
                socket.sendBytes(msg.data(), msg.size());
            }
        }

        int32_t voltage=0;
        if (0 != _hw_res->get_volt_readout(1, voltage)) {
            std::cout<<"voltage read fault!"<<std::endl;
            std::string msg("voltage read fault!");
            socket.sendBytes(msg.data(), msg.size());
        } else {
            if (voltage>230 || voltage<210) {
                std::cout<<"voltage fault!"<<std::endl;
                std::string msg("voltage fault!");
                socket.sendBytes(msg.data(), msg.size());
            }
        }

        sleep(5);
    }
}
