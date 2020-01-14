cmake_minimum_required(VERSION 3.0)
project(pwr-db LANGUAGES CXX C DESCRIPTION "It's useless")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "enable tests" OFF)
option(BUILD_GUI "Build gui" ON)

add_subdirectory(src/app/useless/)

if (BUILD_GUI)
  add_subdirectory(src/app/ui/)
endif()

if(BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()

