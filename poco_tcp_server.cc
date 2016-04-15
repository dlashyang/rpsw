#include <iostream>
#include <sstream>
#include "poco_tcp_server.h"

void CmspServerConnection::run()
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

CmspPocoServer::~CmspPocoServer()
{
    if (_dsp != NULL) {
        delete _dsp;
    }
}

int CmspPocoServer::init()
{
    int ret = 0;

    if(_dsp != NULL) {
        _srv=new Poco::Net::TCPServer(new CmspServerConnectionFactory(_dsp), _ss);
    } else {
        ret = -1;
    }

    return ret;
}

void CmspPocoServer::start()
{
    if (_srv == NULL) {
        std::cout<<"No valid TCP server"<<std::endl;
        return;
    }

    _srv->start();
}

void CmspPocoServer::stop()
{
    if (_srv != NULL) {
        _srv->stop();
    }
}
