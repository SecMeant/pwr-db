cmake_minimum_required(VERSION 3.10)
project(useless)

include_directories(../src)

file( GLOB T_SRC "src/*.cc")

add_executable(m_tests ${T_SRC})
target_link_libraries(m_tests useless gtest_main gtest pthread fmt)

add_test(NAME database_managers COMMAND m_tests)
