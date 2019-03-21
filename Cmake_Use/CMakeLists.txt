# https://www.jianshu.com/p/8909efe13308
cmake_minimum_required(VERSION 2.6)

PROJECT(run_Strategy)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(platform x64)

# 添加头文件路径
include_directories(${PROJECT_SOURCE_DIR})
# 添加库路径
link_directories(${PROJECT_SOURCE_DIR})

file(GLOB APP_HEAD *.h)
file(GLOB APP_SRC *.cpp)
set(SOURCE_FILES run_Strategy.cpp)
set(HEAD_FILES Buy_Strategy.h Strategy.h)
set(ADD_LIBS strategy)
# 输出目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
# 编译为可执行文件
add_executable(run_Strategy ${SOURCE_FILES} ${HEAD_FILES})
# 链接库
target_link_libraries(run_Strategy ${ADD_LIBS})

set_target_properties(run_Strategy PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR})  
set_target_properties(run_Strategy PROPERTIES RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}) 
MESSAGE (STATUS "This is the PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR})