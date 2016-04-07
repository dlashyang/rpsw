#include <iostream>
#include <unistd.h>
#include <memory>

#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"

#include "rpsw_event_handler.h"
#include "rpsw_fault_scanner.h"
#include "rpsw_phalanx_res.h"

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
    std::auto_ptr<cmm_hw_res> hw1(hw);

    rpsw_event_handler_c evnt_hdlr;
    evnt_hdlr.init(hw);
    Poco::RunnableAdapter<rpsw_event_handler_c> runnable(evnt_hdlr, &rpsw_event_handler_c::run);
    Poco::Thread evnt_hdlr_thrd;
    evnt_hdlr_thrd.start(runnable);

    rpsw_fault_scanner fault_scanner(hw);
    Poco::Thread fault_scan_thrd;
    fault_scan_thrd.start(fault_scanner);

    evnt_hdlr_thrd.join();
    fault_scan_thrd.join();

    return 0;
}
