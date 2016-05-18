#ifndef POCO_TCP_SERVER_H
#define POCO_TCP_SERVER_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/StreamSocket.h"

#include "rpsw_event_server.h"
#include "rpsw_msg_dispatcher.h"

class poco_srv_connection: public Poco::Net::TCPServerConnection
{
    public:
        poco_srv_connection(const Poco::Net::StreamSocket& s,rpsw_msg_dispatcher* p): Poco::Net::TCPServerConnection(s), _dsp(p) {};
        void run();

    private:
        rpsw_msg_dispatcher* _dsp;
};

class poco_srv_con_factory: public Poco::Net::TCPServerConnectionFactory
{
    public:
        poco_srv_con_factory(rpsw_msg_dispatcher* p): _dsp(p){};
        Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
        {
            return new poco_srv_connection(socket, _dsp);
        }

    private:
        rpsw_msg_dispatcher* _dsp;
};

class cmsp_poco_server: public rpsw_event_server
{
    private:
        cmsp_poco_server(const cmsp_poco_server&);
        cmsp_poco_server& operator=(const cmsp_poco_server&);

    public:
        cmsp_poco_server(rpsw_msg_dispatcher* p, int port=9911):_srv(NULL),_dsp(p),_ss(port){};
        virtual ~cmsp_poco_server() {};
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
            return (new cmsp_poco_server(_dsp));
        };

    private:
        rpsw_msg_dispatcher* _dsp;
};

#endif //#ifndef POCO_TCP_SERVER_H
