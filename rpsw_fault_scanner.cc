#include <unistd.h>
#include <iostream>

#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
//#include "Poco/Net/SocketStream.h"

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

    Poco::Net::SocketAddress srv_addr("127.0.0.1:19993");
    Poco::Net::DatagramSocket socket;
    socket.connect(srv_addr);

    while(!_stop) {
        int32_t temperature=0;
        _hw_res->get_thermal_readout(1, temperature);
        temperature/=100;
        if (temperature>150) {
            std::cout<<"temperature fault!"<<std::endl;
            std::string msg("temperature fault!");
            socket.sendBytes(msg.data(), msg.size());
        }

        int32_t voltage=0;
        _hw_res->get_volt_readout(1, voltage);
        if (voltage>230 || voltage<210) {
            std::cout<<"voltage fault!"<<std::endl;
            std::string msg("voltage fault!");
            socket.sendBytes(msg.data(), msg.size());
        }

        sleep(5);
    }
}
