#ifndef SIMPLE_MSG_DISPATCHER_H
#define SIMPLE_MSG_DISPATCHER_H

#include "rpsw_msg_dispatcher.h"
#include "rpsw_common_hw_res.h"

class simple_msg_dispatcher: public rpsw_msg_dispatcher
{
    public:
        simple_msg_dispatcher(cmm_hw_res* p):_res(p){};
        virtual ~simple_msg_dispatcher();
        virtual int proc_msg(const std::string& msg, std::string& reply);

    private:
        cmm_hw_res* _res;
};

class simple_msg_disp_factory: public rpsw_msg_disp_factory
{
    public:
        simple_msg_disp_factory(cmm_hw_res* p): _res(p) {};
        virtual rpsw_msg_dispatcher* create_dispatcher()
        {
            return (new simple_msg_dispatcher(_res));
        };

    private:
        cmm_hw_res* _res;
};

#endif //#ifndef SIMPLE_MSG_DISPATCHER_H