cmake_minimum_required(VERSION 3.0)
project(useless LANGUAGES CXX C DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "enable tests" OFF)
option(BUILD_GUI "Build gui" ON)

find_library(libfmt fmt REQUIRED)
find_library(libmysqlclient mysqlclient REQUIRED)
find_library(libcurl curl REQUIRED)

include_directories(src)

set(CMAKE_CXX_FLAGS_DEBUG "-fsanitize=address -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set(TARGET_NAME ${CMAKE_PROJECT_NAME})
set(TARGET_LIB_NAME ${TARGET_NAME}-base)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(SRC_FILES_CXX
src/app/useless/session_manager.cc
src/app/useless/reservation_manager.cc
src/app/useless/offer_manager.cc
src/app/useless/hr_manager.cc
src/app/useless/dbaccess/date.cc
src/app/useless/dbaccess/data_access_manager.cc
src/app/useless/dbaccess/manip/customer_manipulator.cc
src/app/useless/dbaccess/manip/credentials_manipulator.cc
src/app/useless/dbaccess/manip/employee_manipulator.cc
src/app/useless/dbaccess/manip/tour_manipulator.cc
src/app/useless/dbaccess/manip/offer_manipulator.cc
src/app/useless/dbaccess/manip/category_manipulator.cc
src/app/useless/dbaccess/db_connection.cc
src/app/useless/hldb.cc
)

add_library(${TARGET_LIB_NAME} ${SRC_FILES_CXX})
target_link_libraries(${TARGET_LIB_NAME} ${libfmt} ${libmysqlclient})
target_include_directories(${TARGET_LIB_NAME} PUBLIC "src/app/useless/")

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

if (BUILD_GUI)
  add_subdirectory(src/app/ui/)
 else()
  add_executable(${TARGET_NAME} main.cc)
  target_link_libraries(${TARGET_NAME} ${TARGET_LIB_NAME})
endif()

add_executable(sendmail src/app/useless/notify/sendmail.c)
target_link_libraries(sendmail ${libcurl})
