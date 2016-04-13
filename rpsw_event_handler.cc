#include <iostream>
#include <sstream>
#include <unistd.h>

#include "rpsw_event_handler.h"

void CmspServerConnection::run()
{
    std::cout<<"Request from "<<socket().peerAddress().toString()<<std::endl;;
    char buf[1000]={0};
    socket().receiveBytes(buf,1000);
    std::cout<<buf<<std::endl;

    std::string reply = proc_msg(buf);

    std::cout<<reply<<std::endl;
    socket().sendBytes(reply.data(), (int)reply.length());
}

std::string CmspServerConnection::proc_msg(const std::string& msg)
{
    std::stringstream ss;

    std::cout<<"Received message: "<<msg<<std::endl;

    if (msg=="get card status") {
        uint32_t card_stat=0;
        _hw_res->get_card_status(card_stat);
        ss<<"Card Status is "<<card_stat;
    } else if (msg=="get voltage") {
        int32_t vol=0;
        _hw_res->get_volt_readout(0, vol);
        ss<<"Voltage is "<<vol;
    } else if (msg=="get temperature") {
        int32_t temp=0;
        _hw_res->get_thermal_readout(0, temp);
        ss<<"Temperature is "<<temp;
    } else {
        std::cout<<"unknown message: "<<msg<<std::endl;
        ss<<"Unknown message!";
    }

    return ss.str();
}

rpsw_event_handler_c::~rpsw_event_handler_c()
{
    if (_p_srv != NULL) {
        delete _p_srv;
    }
}

int rpsw_event_handler_c::init(cmm_hw_res* p_res)
{
    // set-up a TCPServer instance
    _p_srv=new Poco::Net::TCPServer(new CmspServerConnectionFactory(p_res), _svs);

    std::cout<<"event_hhandler init done."<<std::endl;
    return 0;
}

void rpsw_event_handler_c::start()
{
    if (_p_srv != NULL) {
        std::cout<<"event_handler is running."<<std::endl;
        // start the TCPServer
        _p_srv->start();
    } else {
        std::cout<<"Need to init TCPServer first!"<<std::endl;
    }
}

void rpsw_event_handler_c::stop()
{
    std::cout<<"event_handler is stoping."<<std::endl;

    if (_p_srv != NULL) {
        _p_srv->stop();
    }
}
