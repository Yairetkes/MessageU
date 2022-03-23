cmake_minimum_required(VERSION 3.21)
project(untitled)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled main.cpp ClientConnect.cpp ClientConnect.h ClientUi.cpp ClientUi.h Request.cpp Request.h Tools.cpp Tools.h)
