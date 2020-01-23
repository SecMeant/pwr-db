cmake_minimum_required(VERSION 3.1.0)

project(bdgui)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Charts REQUIRED)

add_executable(bdgui
    src/mainwindow.ui
    src/mainwindow.cpp
    src/main.cpp
    src/login_popup.ui
    src/login_popup.cpp
)
target_include_directories(bdgui PUBLIC src)
target_include_directories(bdgui PUBLIC ${Qt5Charts_INCLUDE_DIRS})

target_link_libraries(bdgui Qt5::Widgets Qt5::Charts useless)
