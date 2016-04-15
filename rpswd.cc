#include <iostream>
#include <unistd.h>
#include <memory>

#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"

#include "rpsw_event_handler.h"
#include "rpsw_fault_scanner.h"

#include "rpsw_dummy_res.h"
#include "poco_tcp_server.h"
#include "simple_msg_dispatcher.h"

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    dummy_factory d("phalanx");
    cmm_hw_res* hw = d.create_hw_res();
    hw->init();
    std::auto_ptr<cmm_hw_res> _hw_just_for_gc(hw);

#if 0
    rpsw_event_handler evnt_hdlr;
    evnt_hdlr.init(hw);
    evnt_hdlr.start();
#endif

    rpsw_msg_dispatcher* dsp=simple_msg_disp_factory(hw).create_dispatcher();
    rpsw_event_server* evnt_srv=poco_server_factory(dsp).create_server();
    std::auto_ptr<rpsw_event_server> _srv_just_for_gc(evnt_srv);
    evnt_srv->init();
    evnt_srv->start();

    rpsw_fault_scanner fault_scanner(hw);
    Poco::Thread fault_scan_thrd;
    fault_scan_thrd.start(fault_scanner);

    //for debug
    int i;
    std::cin>>i;
    fault_scanner.stop();
    evnt_srv->stop();

    fault_scan_thrd.join();

    return 0;
}
