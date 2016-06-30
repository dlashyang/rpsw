#include <unistd.h>
#include <iostream>

#include "rpsw_fault_scanner.h"
#include "rpsw_alarm_sender.h"
#include "rpsw_alarm_object.h"
#include "readout.h"

rpsw_fault_scanner::~rpsw_fault_scanner()
{
    std::cout<<"~rpsw_fault_scanner"<<std::endl;
}

void rpsw_fault_scanner::start()
{
    _stop=false;
    _thrd.start(*this);
}

void rpsw_fault_scanner::stop()
{
    _stop=true;
    _thrd.join();
}

void rpsw_fault_scanner::run()
{
    rpsw_trace(Poco::Logger::get("rpswd.fault_scanner"), "fault_scanner is running");

    //Poco::Net::SocketAddress srv_addr("127.0.0.1:19993");
    //Poco::Net::DatagramSocket socket;
    //socket.connect(srv_addr);

    readout t(1);
    readout v(5);

    while(!_stop) {
        if (0 != _hw_res->get_thermal_readout(1, t)) {
            rpsw_alarm_obj a("thermal");
            _sender->send(a.to_json());
        } else {
            //t.set_value(temperature/100);
            if (t.get_value() > 150) {
                rpsw_alarm_obj a("thermal", alarm_major, t.get_value());
                _sender->send(a.to_json());
            }
        }

        int32_t voltage=0;
        if (0 != _hw_res->get_volt_readout(1, v)) {
            rpsw_alarm_obj a("voltage");
            _sender->send(a.to_json());
        } else {
            int32_t ret = v.get_value(voltage);
            if (ret !=0 || voltage>230 || voltage<210) {
                rpsw_alarm_obj a("voltage", alarm_major, voltage);
                _sender->send(a.to_json());
            }
        }

        sleep(5);
    }
}
