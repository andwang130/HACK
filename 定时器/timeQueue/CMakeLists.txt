cmake_minimum_required(VERSION 3.12)
project(timeQueue)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-std=c++11 -pthread")
add_executable(timeQueue main.cpp TimeQueue.cpp TimeQueue.h Timer.cpp Timer.h)
