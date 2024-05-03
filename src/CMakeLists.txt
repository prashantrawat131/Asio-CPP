cmake_minimum_required(VERSION 3.29.0)

project(Learn-Socket-Programming)

add_executable(main ./udp_socket/daytime_synchronous_server.cpp)

target_include_directories(main PUBLIC C:/cpp_sdks/asio-1.28.0/include)