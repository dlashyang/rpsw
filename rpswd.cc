#include <iostream>
#include <unistd.h>
#include <pthread.h>

#include "rpsw_event_handler.h"

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

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    rpsw_event_handler_c evnt_hdlr;
    evnt_hdlr.init(NULL);
    pthread_t event_handler_thread;
    pthread_create(&event_handler_thread, NULL, rpsw_event_handler, (void*)&evnt_hdlr);

    pthread_t fault_scanner_thread;
    pthread_create(&fault_scanner_thread, NULL, rpsw_fault_scanner, NULL);

    pthread_join(event_handler_thread, NULL);
    pthread_join(fault_scanner_thread, NULL);

    return 0;
}
