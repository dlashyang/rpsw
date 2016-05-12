#include <iostream>
#include <unistd.h>
#include <memory>

#include "rpsw_fault_scanner.h"

#include "rpsw_dummy_res.h"
#include "poco_net_service.h"
#include "simple_msg_dispatcher.h"

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    dummy_factory d("phalanx");
    std::auto_ptr<cmm_hw_res> hw(d.create_hw_res());
    hw->init();

#if 0
    rpsw_event_handler evnt_hdlr;
    evnt_hdlr.init(hw);
    evnt_hdlr.start();
#endif

    std::auto_ptr<rpsw_msg_dispatcher> dsp(simple_msg_disp_factory().create_dispatcher());
    dsp->register_hw(hw.get());

    std::auto_ptr<rpsw_event_server> evnt_srv(poco_server_factory(dsp.get()).create_server());
    evnt_srv->init();
    evnt_srv->start();

    rpsw_fault_scanner fault_scanner(hw.get());
    fault_scanner.start();

    //for debug
    int i;
    std::cin>>i;
    fault_scanner.stop();
    evnt_srv->stop();

    return 0;
}
