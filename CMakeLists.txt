cmake_minimum_required(VERSION 3.0)
project(useless LANGUAGES CXX DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "enable tests" OFF)
option(BUILD_GUI "Build gui" ON)

find_library(libfmt fmt REQUIRED)
find_library(libmysqlclient mysqlclient REQUIRED)

include_directories(src)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -flto -march=native")

set(TARGET_NAME ${CMAKE_PROJECT_NAME})
set(TARGET_LIB_NAME ${TARGET_NAME}-base)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES_CXX
src/session_manager.cc
src/reservation_manager.cc
src/offer_manager.cc
src/hr_manager.cc
src/dbaccess/date.cc
src/dbaccess/data_access_manager.cc
src/dbaccess/manip/customer_manipulator.cc
src/dbaccess/manip/credentials_manipulator.cc
src/dbaccess/manip/employee_manipulator.cc
src/dbaccess/manip/tour_manipulator.cc
src/dbaccess/manip/offer_manipulator.cc
src/dbaccess/manip/category_manipulator.cc
src/dbaccess/db_connection.cc
src/hldb.cc
)

add_library(${TARGET_LIB_NAME} ${SRC_FILES_CXX})
target_link_libraries(${TARGET_LIB_NAME} ${libfmt} ${libmysqlclient})

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (BUILD_GUI)
  add_subdirectory(gui/bdg/)
 else()
  add_executable(${TARGET_NAME} main.cc)
  target_link_libraries(${TARGET_NAME} ${TARGET_LIB_NAME})
endif()


