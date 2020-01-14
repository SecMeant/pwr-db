cmake_minimum_required(VERSION 3.10)

set (TEST_NAME useless_test)

file( GLOB T_SRC "src/*.cc")
find_library(libgtest gtest REQUIRED)
find_library(libgtestmain gtest_main REQUIRED)
find_library(libgmock gmock REQUIRED)
find_library(libpthread pthread REQUIRED)

add_executable(${TEST_NAME} ${T_SRC})
target_link_libraries(${TEST_NAME} ${libgtestmain} ${libgtest} ${libgmock} ${libpthread} useless ${libfmt})
