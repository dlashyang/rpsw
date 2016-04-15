#include <iostream>
#include <unistd.h>
#include <memory>

#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"

#include "rpsw_event_handler.h"
#include "rpsw_fault_scanner.h"

#include "rpsw_dummy_res.h"

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    dummy_factory d("phalanx");
    cmm_hw_res* hw = d.create_hw_res();
    hw->init();
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
