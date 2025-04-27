cmake_minimum_required(VERSION 3.16)

project(Eeprom24CLib)

file(GLOB_RECURSE EEPROM24C_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${EEPROM24C_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
