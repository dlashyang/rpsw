#include <iostream>
#include <unistd.h>

#include "Poco/ConsoleChannel.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
#include "Poco/Logger.h"
#include "Poco/LogStream.h"
#include "Poco/AutoPtr.h"

#include "rpsw_log.h"
#include "rpsw_fault_scanner.h"

#include "rpsw_dummy_res.h"
#include "poco_net_service.h"
#include "simple_msg_dispatcher.h"

static inline void rpswd_logger_init()
{
    Poco::AutoPtr<Poco::ConsoleChannel> pCons(new Poco::ConsoleChannel);
    Poco::AutoPtr<Poco::PatternFormatter> pPF(new Poco::PatternFormatter);
    pPF->setProperty("pattern", "%Y-%m-%d %H:%M:%S %s: %t");
    Poco::AutoPtr<Poco::FormattingChannel> pFC(new Poco::FormattingChannel(pPF, pCons));
    Poco::Logger::root().setChannel(pFC);

    Poco::Logger& _logger = Poco::Logger::get("rpswd");
    //_logger.setLevel(Poco::Message::PRIO_TRACE);
    rpsw_info(_logger, "rpswd_logger_init done with level[%d]", _logger.getLevel());

    //make line shorter
    pPF->setProperty("pattern", "%H:%M:%S: [%p] %t");

    return;
}

int main()
{
    rpswd_logger_init();
    Poco::Logger& _logger = Poco::Logger::get("rpswd");
    rpsw_trace(_logger, "%s: Rpswd starting", std::string(__func__));

    cmm_hw_res_t hw = dummy_factory("phalanx").create_hw_res();
    hw->init();
    rpsw_trace(_logger, "%s: hw_res init done", std::string(__func__));

    msg_disp_t dsp = simple_msg_disp_factory().create_dispatcher();
    dsp->register_hw(hw.get());
    rpsw_trace(_logger, "%s: message dispacher ready", std::string(__func__));

    evnt_srv_t evnt_srv = poco_server_factory(dsp.get()).create_server();
    evnt_srv->init();
    evnt_srv->start();
    rpsw_trace(_logger, "%s: event server ready", std::string(__func__));

    alarm_sender_t sender = poco_sender_factory("127.0.0.1:19993").create_sender();
    rpsw_fault_scanner fault_scanner(hw.get(), sender);
    fault_scanner.start();
    rpsw_trace(_logger, "%s: fault scanner ready", std::string(__func__));

    //for debug
    int i;
    std::cin>>i;
    fault_scanner.stop();
    evnt_srv->stop();
    rpsw_trace(_logger, "%s: all things done", std::string(__func__));

    return 0;
}
