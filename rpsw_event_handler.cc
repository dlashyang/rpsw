#include <iostream>
#include <sstream>
#include <unistd.h>

#include "rpsw_event_handler.h"

#include "poco_tcp_server.h"
#include "simple_msg_dispatcher.h"

rpsw_event_handler::~rpsw_event_handler()
{
    if (_srv != NULL) {
        delete _srv;
    }
}

int rpsw_event_handler::init(cmm_hw_res* p_res)
{
    std::cout<<"event_handler init."<<std::endl;

    _res=p_res;
    //need a seperated method later
    _srv=new CmspPocoServer(new simple_msg_dispatcher(_res));
    _srv->init();

    return 0;
}

void rpsw_event_handler::start()
{
    if (_srv != NULL) {
        std::cout<<"event_handler is running."<<std::endl;
        // start the TCPServer
        _srv->start();
    } else {
        std::cout<<"Need to init Event Server first!"<<std::endl;
    }
}

void rpsw_event_handler::stop()
{
    std::cout<<"event_handler will stop."<<std::endl;

    if (_srv != NULL) {
        _srv->stop();
    }
}
