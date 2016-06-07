cmake_minimum_required(VERSION 2.8.4)

PROJECT(RPSWD)

add_definitions(
    -g
    -Wall
    )

include_directories(
    include
    readout
    hw_res/include
    event_util/include
    )

add_executable(rpswd rpswd.cc rpsw_fault_scanner.cc rpswd_alarm_object.cc)

find_library(poco_f PocoFoundation /usr/local)
find_library(poco_p PocoJSON /usr/local)

target_link_libraries(rpswd 
    dummy_res 
    simple_msg_disp
    poco_srvc
    readout
    ${poco_f} 
    ${poco_p} 
    )

add_subdirectory(event_util/poco_net_service)
add_subdirectory(event_util/simple_msg_disp)
add_subdirectory(hw_res/dummy_res)
add_subdirectory(readout)
