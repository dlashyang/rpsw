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
        phalanx_hw_res* phalan=new phalanx_hw_res();
        phalan->init("phalanx");
        return (dynamic_cast<cmm_hw_res*>(phalan));
    } else {
        return NULL;
    }
}

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    cmm_hw_res* hw=get_hw_res("phalanx");
    std::auto_ptr<cmm_hw_res> _hw_just_for_gc(hw);

    rpsw_event_handler evnt_hdlr;
    evnt_hdlr.init(hw);
    evnt_hdlr.start();

    rpsw_fault_scanner fault_scanner(hw);
    Poco::Thread fault_scan_thrd;
    fault_scan_thrd.start(fault_scanner);

    //for debug
    int i;
    std::cin>>i;
    fault_scanner.stop();
    evnt_hdlr.stop();

    fault_scan_thrd.join();

    return 0;
}
