cmake_minimum_required(VERSION 3.0)
project(useless LANGUAGES CXX DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(libfmt fmt REQUIRED)
find_library(libmysqlclient mysqlclient REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native")

set(TARGET_NAME ${CMAKE_PROJECT_NAME})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES_CXX ${SRC_DIR}/*.cc)

add_executable(${TARGET_NAME} ${SRC_FILES_CXX})

target_link_libraries(${TARGET_NAME} ${libfmt} ${libmysqlclient})
