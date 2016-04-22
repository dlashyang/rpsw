cmake_minimum_required(VERSION 2.8.4)

add_library(poco_srv STATIC poco_tcp_server.cc)

find_library(poco_n PocoNet /usr)
target_link_libraries(poco_srv ${poco_n})
