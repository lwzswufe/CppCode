cmake_minimum_required(VERSION 2.6)

# 兼容C++11标准
# set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# 64位
set(platform x64)
set(PROJECT_DIR ${PROJECT_SOURCE_DIR})
# 预定义宏
add_subdirectory(sim)
add_subdirectory(bin)