cmake_minimum_required(VERSION 2.6)
# 指令定义工程名称
PROJECT(Sim)
# 预定义宏
ADD_DEFINITIONS(-D __SIM__)
# SET指令的语法是  SET(VAR [VALUE] [CACHE TYPE DOCSTRING [FORCE]])
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

set(platform x64)
MESSAGE (STATUS "Project Dir: " ${PROJECT_DIR})

# 添加头文件路径
include_directories(${PROJECT_DIR}/src)
# include_directories(${PROJECT_DIR}/bin)
# 添加库路径
# link_directories(${PROJECT_DIR}/src)
# link_directories(${PROJECT_DIR}/bin)

file(GLOB APP_HEAD ${PROJECT_DIR}/src/*.h)
file(GLOB APP_SRC ${PROJECT_DIR}/src/*.cpp  ${PROJECT_DIR}/sim/*.cpp)

MESSAGE (STATUS "Include Dir:" ${INCLUDE_PATH})
MESSAGE (STATUS "Head Files: " ${APP_HEAD})
MESSAGE (STATUS "Src  Files: " ${APP_SRC})

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_DIR}/bin)
add_executable(Sim ${APP_SRC} ${APP_HEAD})

SET_TARGET_PROPERTIES(Sim PROPERTIES OUTPUT_NAME "sim.o")
GET_TARGET_PROPERTY (OUTPUT_VALUE Sim OUTPUT_NAME)

# 这个指令用于向终端输出用户定义的信息，包含了三种类型:
# SEND_ERROR，产生错误，生成过程被跳过。
# SATUS，输出前缀为—的信息。
# FATAL_ERROR，立即终止所有cmake过程。
MESSAGE (STATUS "OUTPUT_FILE: " ${EXECUTABLE_OUTPUT_PATH} "/" ${OUTPUT_VALUE})