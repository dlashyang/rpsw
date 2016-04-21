cmake_minimum_required(VERSION 2.8.4)

PROJECT(RPSWD)

ADD_DEFINITIONS(
    -g
    -Wall
    )

ADD_EXECUTABLE(rpswd rpswd.cc rpsw_dummy_res.cc rpsw_fault_scanner.cc poco_tcp_server.cc simple_msg_dispatcher.cc)

find_library(poco_f PocoFoundation /usr/local)
find_library(poco_n PocoNet /usr)

TARGET_LINK_LIBRARIES(rpswd pthread ${poco_f} ${poco_n})
