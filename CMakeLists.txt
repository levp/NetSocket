cmake_minimum_required(VERSION 3.15)
project(winsocketing)

set(CMAKE_CXX_STANDARD 17)

find_package(Threads REQUIRED)

file(GLOB_RECURSE Source_Files "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(winsocketing ${Source_Files} src/net/windows/ServerSocket.hpp src/FAIL.hpp src/net/windows/WinSocketEnv.hpp src/net/windows/ClientSocket.hpp src/net/WebServer.hpp src/net/SocketEnv.hpp src/net/windows/WinSocketEnv.cpp)
target_link_libraries(winsocketing PUBLIC Threads::Threads ws2_32)
