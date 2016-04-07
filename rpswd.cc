#include <iostream>
#include <unistd.h>

#include "rpsw_event_handler.h"
#include "rpsw_phalanx_res.h"
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"

static void* rpsw_event_handler(void* args)
{
    std::cout<<"This is event_handler."<<std::endl;

    rpsw_event_handler_c* p_evnt_hdlr=(rpsw_event_handler_c*)args;
    p_evnt_hdlr->run();

    return NULL;
}

static void* rpsw_fault_scanner(void* args)
{
    std::cout<<"This is fault_scanner."<<std::endl;
    sleep(5);

    return NULL;
}

cmm_hw_res* get_hw_res(const std::string& name)
{
    std::cout<<"hardware is "<<name<<std::endl;

    if (name=="phalanx") {
        return (new phalanx_hw_res());
    } else {
        return NULL;
    }
}

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    cmm_hw_res* hw=get_hw_res("phalanx");

    rpsw_event_handler_c evnt_hdlr;
    evnt_hdlr.init(hw);
    Poco::RunnableAdapter<rpsw_event_handler_c> runnable(evnt_hdlr, &rpsw_event_handler_c::run);
    Poco::Thread evnt_hdlr_thrd;
    evnt_hdlr_thrd.start(runnable);

    pthread_t fault_scanner_thread;
    pthread_create(&fault_scanner_thread, NULL, rpsw_fault_scanner, NULL);

    evnt_hdlr_thrd.join();
    pthread_join(fault_scanner_thread, NULL);

    delete hw;

    return 0;
}
