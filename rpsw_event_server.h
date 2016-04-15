#ifndef RPSW_EVENT_SERVER_H
#define RPSW_EVENT_SERVER_H

#include <string>
#include "rpsw_common_hw_res.h"

class rpsw_msg_dispatcher
{
    public:
        virtual ~rpsw_msg_dispatcher() {};
        virtual int proc_msg(const std::string& msg, std::string& reply)=0;
};

class rpsw_event_server
{
    public:
        virtual ~rpsw_event_server() {};
        virtual int init()=0;
        virtual void start()=0;
        virtual void stop()=0;
};

#endif//#ifndef RPSW_EVENT_SERVER_H
