#include <iostream>
#include <unistd.h>

#include "rpsw_event_handler.h"

void* rpsw_event_handler_c::run()
{
    std::cout<<"event_handler is running."<<std::endl;
    sleep(5);

    return NULL;
}

int rpsw_event_handler_c::init(cmm_hw_res* p_res)
{
    _hw_res=p_res;

    std::cout<<"event_hhandler init done."<<std::endl;
    return 0;
}
