cmake_minimum_required(VERSION 3.16)

project(TC2004Lib)

file(GLOB_RECURSE TC2004_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${TC2004_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
