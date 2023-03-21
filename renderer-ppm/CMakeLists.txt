cmake_minimum_required(VERSION 3.26.0)

project(RENDERER VERSION 1.0)
add_executable(RENDERER Source.cpp)

target_include_directories(RENDERER PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)