cmake_minimum_required(VERSION 3.1.0)

project(bdgui)
include_directories(src)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(bdgui
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
)

target_link_libraries(bdgui Qt5::Widgets ${TARGET_LIB_NAME})
