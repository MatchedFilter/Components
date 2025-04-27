cmake_minimum_required(VERSION 3.16)

project(NTCLib)

file(GLOB_RECURSE DHT11_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${DHT11_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
