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

poco_udp_sender::poco_udp_sender(const std::string& srv_addr): _srv_addr(srv_addr)
{
    _socket.connect(_srv_addr);
}

int poco_udp_sender::send(const std::string& msg)
{
    return _socket.sendBytes(msg.data(), msg.size());
}
