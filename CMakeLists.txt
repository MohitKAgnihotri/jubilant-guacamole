cmake_minimum_required(VERSION 3.19)
project(sam_320_attachments)

set(CMAKE_CXX_STANDARD 14)

add_executable(sam_320 CppTest.cpp  round_robin.cpp fcfs.cpp priority.cpp priority.cpp PriorityFCFS.cpp sjf.cpp)