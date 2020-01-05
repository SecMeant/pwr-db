cmake_minimum_required(VERSION 3.5)

project(asdf LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC OFF)

set(UI ${CMAKE_CURRENT_LIST_DIR}/mainwindow.ui)

find_package(Qt5Core REQUIRED)

qt5_wrap_ui(UI_HEADERS ${UI})
add_executable(${PROJECT_NAME} ${UI_HEADERS} ${RESOURCE} ${SOURCES} )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



add_executable(asdf
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui)

target_link_libraries(asdf PRIVATE  Qt5::Core)
