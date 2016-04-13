#ifndef RPSW_EVENT_HANDLER_H
#define RPSW_EVENT_HANDLER_H

#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/StreamSocket.h"

#include "rpsw_common_hw_res.h"

class CmspServerConnection: public Poco::Net::TCPServerConnection
{
    public:
        CmspServerConnection(const Poco::Net::StreamSocket& s, cmm_hw_res* p_hw): Poco::Net::TCPServerConnection(s), _hw_res(p_hw) {};
        void run();

    private:
        std::string proc_msg(const std::string& msg);
        //int proc_msg(const std::string& msg, std::string& reply);
        cmm_hw_res* _hw_res;
};

class CmspServerConnectionFactory: public Poco::Net::TCPServerConnectionFactory
{
    public:
        CmspServerConnectionFactory(cmm_hw_res* p_hw): _hw_res(p_hw){};
        Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
        {
            return new CmspServerConnection(socket, _hw_res);
        }

    private:
        cmm_hw_res* _hw_res;
};

class rpsw_event_handler_c
{
    private:
        Poco::Net::ServerSocket _svs;
        Poco::Net::TCPServer* _p_srv;

    public:
        rpsw_event_handler_c():_svs(9911),_p_srv(NULL){};
        ~rpsw_event_handler_c();
        int init(cmm_hw_res* p_res);
        void start();
        void stop();
};

#endif //#ifndef RPSW_EVENT_HANDLER_H
