cmake_minimum_required(VERSION 3.13)
project(sparser)

set(CMAKE_CXX_STANDARD 14)

add_executable(sparser main.cpp json.cpp cookie.cpp)