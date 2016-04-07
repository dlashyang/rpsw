#ifndef RPSW_EVENT_HANDLER_H
#define RPSW_EVENT_HANDLER_H

#include "rpsw_common_hw_res.h"

class rpsw_event_handler_c
{
    private:
        cmm_hw_res* _hw_res;

    public:
        rpsw_event_handler_c():_hw_res(NULL){};
        int init(cmm_hw_res* p_res);
        void* run();
};

#endif //#ifndef RPSW_EVENT_HANDLER_H
