#ifndef RPSW_MSG_DISPATCHER_H
#define RPSW_MSG_DISPATCHER_H

#include <string>

class rpsw_msg_dispatcher
{
    public:
        virtual ~rpsw_msg_dispatcher() {};
        virtual int proc_msg(const std::string& msg, std::string& reply)=0;
};

class rpsw_msg_disp_factory
{
    public:
        virtual rpsw_msg_dispatcher* create_dispatcher()=0;
};

#endif //#ifndef RPSW_MSG_DISPATCHER_H
