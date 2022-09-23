cmake_minimum_required(VERSION 3.0.0)

project(tcpServer)

add_executable(${PROJECT_NAME}
    ./main.cpp
    ./tcpServer.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    ./
)

target_compile_options(${PROJECT_NAME} PUBLIC
    -Wall
)