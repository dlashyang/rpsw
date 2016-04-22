cmake_minimum_required(VERSION 2.8.4)

PROJECT(RPSWD)

ADD_DEFINITIONS(
    -g
    -Wall
    )

include_directories(
    include
    msg_disp/include
    hw_res/include
    event_srv/include
    )

add_executable(rpswd rpswd.cc rpsw_fault_scanner.cc)

find_library(poco_f PocoFoundation /usr/local)
find_library(poco_n PocoNet /usr)

TARGET_LINK_LIBRARIES(rpswd 
    dummy_res 
    simple_msg_disp
    poco_srv
    ${poco_f} 
    ${poco_n}
    )

ADD_SUBDIRECTORY(event_srv/poco_tcp_srv)
ADD_SUBDIRECTORY(msg_disp/simple_msg_disp)
ADD_SUBDIRECTORY(hw_res/dummy_res)
