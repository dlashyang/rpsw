cmake_minimum_required(VERSION 2.8.4)

add_library(poco_srvc STATIC poco_net_service.cc)

find_library(poco_n PocoNet /usr)
target_link_libraries(poco_srvc ${poco_n})
