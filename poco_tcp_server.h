#ifndef POCO_TCP_SERVER_H
#define POCO_TCP_SERVER_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/StreamSocket.h"

#include "rpsw_event_server.h"

class CmspServerConnection: public Poco::Net::TCPServerConnection
{
    public:
        CmspServerConnection(const Poco::Net::StreamSocket& s,rpsw_msg_dispatcher* p): Poco::Net::TCPServerConnection(s), _dsp(p) {};
        void run();

    private:
        rpsw_msg_dispatcher* _dsp;
};

class CmspServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory
{
    public:
        CmspServerConnectionFactory(rpsw_msg_dispatcher* p): _dsp(p){};
        Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
        {
            return new CmspServerConnection(socket, _dsp);
        }

    private:
        rpsw_msg_dispatcher* _dsp;
};

class CmspPocoServer: public rpsw_event_server
{
    public:
        CmspPocoServer(rpsw_msg_dispatcher* p, int port=9911):_srv(NULL),_dsp(p),_ss(port){};
        virtual ~CmspPocoServer();
        virtual int init();
        virtual void start();
        virtual void stop();

    private:
        Poco::Net::TCPServer* _srv;
        rpsw_msg_dispatcher* _dsp;
        Poco::Net::ServerSocket _ss;
};

class poco_server_factory: public rpsw_server_factory
{
    public:
        poco_server_factory(rpsw_msg_dispatcher* p):_dsp(p) {};
        virtual rpsw_event_server* create_server()
        {
            return (new CmspPocoServer(_dsp));
        };

    private:
        rpsw_msg_dispatcher* _dsp;
};

#endif //#ifndef POCO_TCP_SERVER_H
