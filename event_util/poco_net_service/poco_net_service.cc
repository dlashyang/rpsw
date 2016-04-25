#include <iostream>
#include <sstream>
#include "poco_net_service.h"

void poco_srv_connection::run()
{
    if (_dsp == NULL) {
        std::cout<<"No valid message dispatcher!"<<std::endl;
        return;
    }

    std::cout<<"Request from "<<socket().peerAddress().toString()<<std::endl;;
    char buf[1000]={0};
    socket().receiveBytes(buf,1000);
    std::cout<<buf<<std::endl;

    std::string reply;
    _dsp->proc_msg(buf, reply);

    std::cout<<reply<<std::endl;
    socket().sendBytes(reply.data(), (int)reply.length());
}

cmsp_poco_server::~cmsp_poco_server()
{
    if (_dsp != NULL) {
        delete _dsp;
    }
}

int cmsp_poco_server::init()
{
    int ret = 0;

    if(_dsp != NULL) {
        _srv=new Poco::Net::TCPServer(new poco_srv_con_factory(_dsp), _ss);
    } else {
        std::cout<<"No valid dispatcher"<<std::endl;
        ret = -1;
    }

    return ret;
}

void cmsp_poco_server::start()
{
    if (_srv == NULL) {
        std::cout<<"No valid TCP server"<<std::endl;
        return;
    }

    _srv->start();
}

void cmsp_poco_server::stop()
{
    if (_srv != NULL) {
        _srv->stop();
    }
}
