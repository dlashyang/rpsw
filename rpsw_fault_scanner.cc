#include <iostream>
#include "rpsw_fault_scanner.h"

rpsw_fault_scanner::~rpsw_fault_scanner()
{
    if(_hw_res != NULL) {
        _hw_res=NULL;
    }
}

void rpsw_fault_scanner::run()
{
    std::cout<<"rpsw_fault_scanner is running"<<std::endl;
}
