#include <iostream>
#include <unistd.h>

#include "rpsw_fault_scanner.h"

#include "rpsw_dummy_res.h"
#include "poco_net_service.h"
#include "simple_msg_dispatcher.h"

int main()
{
    std::cout<<"This is rpswd."<<std::endl;

    cmm_hw_res_t hw = dummy_factory("phalanx").create_hw_res();
    hw->init();

    msg_disp_t dsp = simple_msg_disp_factory().create_dispatcher();
    dsp->register_hw(hw.get());

    evnt_srv_t evnt_srv = poco_server_factory(dsp.get()).create_server();
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
