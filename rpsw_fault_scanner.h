#ifndef RPSW_FAULT_SCANNER_H
#define RPSW_FAULT_SCANNER_H

#include "Poco/Runnable.h"
#include "rpsw_common_hw_res.h"

class rpsw_fault_scanner : public Poco::Runnable
{
    private:
        cmm_hw_res* _hw_res;

    public:
        rpsw_fault_scanner(cmm_hw_res* p_hw):_hw_res(p_hw){};
        ~rpsw_fault_scanner();

        virtual void run();
};

#endif //#ifndef RPSW_FAULT_SCANNER_H
