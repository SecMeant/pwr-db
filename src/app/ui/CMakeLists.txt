cmake_minimum_required(VERSION 3.1.0)

project(bdgui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(bdgui
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/login_popup.ui
    src/login_popup.cpp
)
target_include_directories(bdgui PUBLIC src)

target_link_libraries(bdgui Qt5::Widgets useless)
