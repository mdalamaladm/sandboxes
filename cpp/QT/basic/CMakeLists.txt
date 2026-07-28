cmake_minimum_required(VERSION 3.16)
project(HelloQt)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(HelloQt main.cpp)
target_link_libraries(HelloQt PRIVATE Qt6::Widgets)
