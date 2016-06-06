#ifndef RPSW_MSG_DISPATCHER_H
#define RPSW_MSG_DISPATCHER_H

#include <string>
#include <memory>
#include "rpsw_common_hw_res.h"

class rpsw_msg_dispatcher
{
    public:
        virtual ~rpsw_msg_dispatcher() {};
        virtual int register_hw(cmm_hw_res*)=0;
        virtual int deregister_hw()=0;
        virtual int proc_msg(const std::string& msg, std::string& reply)=0;
};

typedef std::auto_ptr<rpsw_msg_dispatcher> msg_disp_t;
class rpsw_msg_disp_factory
{
    public:
        virtual msg_disp_t create_dispatcher()=0;
};

#endif //#ifndef RPSW_MSG_DISPATCHER_H
