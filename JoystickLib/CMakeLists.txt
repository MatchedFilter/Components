cmake_minimum_required(VERSION 3.16)

project(JoystickLib)

file(GLOB_RECURSE JOYSTICK_LIB_SRCS src/*.cpp)

add_library(${PROJECT_NAME}
    ${JOYSTICK_LIB_SRCS}
)

target_include_directories(${PROJECT_NAME} PUBLIC include)
