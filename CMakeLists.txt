cmake_minimum_required(VERSION 2.8)

PROJECT(RPSWD)

ADD_DEFINITIONS(
    -g
    -Wall
    )

ADD_EXECUTABLE(rpswd rpswd.cc rpsw_event_handler.cc rpsw_phalanx_res.cc rpsw_fault_scanner.cc poco_tcp_server.cc simple_msg_dispatcher.cc)

LINK_DIRECTORIES(/usr/local/lib)

TARGET_LINK_LIBRARIES(rpswd pthread /usr/local/lib/libPocoFoundation.so /usr/local/lib/libPocoNet.so)
