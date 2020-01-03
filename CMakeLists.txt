cmake_minimum_required(VERSION 3.0)
project(useless LANGUAGES CXX DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(GTESTS_ENABLED "enable math tests" OFF)

find_library(libfmt fmt REQUIRED)
find_library(libmysqlclient mysqlclient REQUIRED)

include_directories(src)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native")

set(TARGET_NAME ${CMAKE_PROJECT_NAME})

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB_RECURSE SRC_FILES_CXX ${SRC_DIR}/*.cc)

add_library(${TARGET_NAME} ${SRC_FILES_CXX})
add_executable(app main.cc)

if(${GTESTS_ENABLED})
  enable_testing()
  add_subdirectory(tests)
endif()


target_link_libraries(${TARGET_NAME} ${libfmt} ${libmysqlclient})
target_link_libraries(app ${TARGET_NAME})

