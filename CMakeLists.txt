cmake_minimum_required(VERSION 3.20)
project(flight_planner)

set(CMAKE_CXX_STANDARD 14)

add_executable(flight_planner main.cpp adjacency_list.h graph_list.h)
