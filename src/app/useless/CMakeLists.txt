cmake_minimum_required(VERSION 3.0)
project(useless LANGUAGES CXX C DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_library(libfmt fmt REQUIRED)
find_library(libmysqlclient mysqlclient REQUIRED)
find_library(libcurl curl REQUIRED)

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -ggdb -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native")

set(TARGET_LIB_NAME useless)

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
target_include_directories(${TARGET_LIB_NAME} PUBLIC "src/")

add_executable(sendmail src/notify/sendmail.c)
target_link_libraries(sendmail ${libcurl})
