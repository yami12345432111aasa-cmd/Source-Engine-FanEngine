cmake_minimum_required(VERSION 3.21)
project(FanEngineEditor VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Widgets)

qt_add_executable(FanEngineEditor
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
)

target_link_libraries(FanEngineEditor PRIVATE Qt6::Widgets)
