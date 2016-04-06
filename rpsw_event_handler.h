#ifndef RPSW_EVENT_HANDLER_H
#define RPSW_EVENT_HANDLER_H

class cmm_hw_res
{
};

class rpsw_event_handler_c
{
    private:
        cmm_hw_res* _hw_res;

    public:
        rpsw_event_handler_c():_hw_res(NULL){};
        int init(cmm_hw_res* p_res);
        void* run();
};

#endif
