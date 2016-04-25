#ifndef RPSW_FAULT_SCANNER_H
#define RPSW_FAULT_SCANNER_H

#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "rpsw_common_hw_res.h"

class rpsw_fault_scanner : public Poco::Runnable
{
    private:
        Poco::Thread _thrd;
        cmm_hw_res* _hw_res;
        bool _stop;

    public:
        rpsw_fault_scanner(cmm_hw_res* p_hw):_hw_res(p_hw),_stop(true){};
        ~rpsw_fault_scanner();

        virtual void run();
        void start();
        void stop();
};

#endif //#ifndef RPSW_FAULT_SCANNER_H
