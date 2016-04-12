cmake_minimum_required(VERSION 2.8)

PROJECT(RPSWD)

ADD_DEFINITIONS(
    -g
    -Wall
    )

ADD_EXECUTABLE(rpswd rpswd.cc rpsw_event_handler.cc rpsw_phalanx_res.cc rpsw_fault_scanner.cc)

TARGET_LINK_LIBRARIES(rpswd pthread /usr/local/lib/libPocoFoundation.30.dll.a /usr/local/lib/libPocoNet.30.dll.a)
