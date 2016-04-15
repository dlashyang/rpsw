#ifndef RPSW_EVENT_HANDLER_H
#define RPSW_EVENT_HANDLER_H

#include "rpsw_common_hw_res.h"
#include "rpsw_event_server.h"

class rpsw_event_handler
{
    private:
        cmm_hw_res* _res;
        rpsw_event_server* _srv;
        rpsw_msg_dispatcher* _dsp;

    public:
        rpsw_event_handler():_res(NULL),_srv(NULL),_dsp(NULL){};
        ~rpsw_event_handler();
        int init(cmm_hw_res* p_res);
        void start();
        void stop();
};

#endif //#ifndef RPSW_EVENT_HANDLER_H
