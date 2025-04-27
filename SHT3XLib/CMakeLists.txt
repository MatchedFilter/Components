cmake_minimum_required(VERSION 3.16)

project(SHT3XLib)

file(GLOB_RECURSE SHT3X_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${SHT3X_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
