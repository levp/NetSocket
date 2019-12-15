cmake_minimum_required(VERSION 3.15)
project(NetSocket)

set(Executable_Name "NetSocket")
set(Project_Root "${CMAKE_SOURCE_DIR}")
set(Source_Dir "${Project_Root}/src")
set(Output_Dir "${Project_Root}/output")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${Output_Dir}")

set(Entry_Point "${Source_Dir}/main.cpp")
file(GLOB_RECURSE Source_Files "${Source_Dir}/net/*.cpp")
add_executable("${Executable_Name}" ${Entry_Point} ${Source_Files})
target_include_directories("${Executable_Name}" PUBLIC "${Source_Dir}")

find_package(Threads REQUIRED)
target_link_libraries("${Executable_Name}" PUBLIC Threads::Threads)

if (WIN32)
	target_link_libraries("${Executable_Name}" PUBLIC ws2_32)
	add_compile_definitions("${Executable_Name}" WIN32_LEAN_AND_MEAN)
endif()
