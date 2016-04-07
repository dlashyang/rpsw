cmake_minimum_required(VERSION 2.8)

PROJECT(RPSWD)

ADD_DEFINITIONS(
    -g
    -Wall
    )

ADD_EXECUTABLE(rpswd rpswd.cc rpsw_event_handler.cc rpsw_phalanx_res.cc)

TARGET_LINK_LIBRARIES(rpswd pthread)
