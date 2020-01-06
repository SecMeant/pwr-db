cmake_minimum_required(VERSION 3.10)

file( GLOB T_SRC "src/*.cc")

add_executable(m_tests ${T_SRC})
target_link_libraries(m_tests gtest_main gtest pthread ${TARGET_LIB_NAME} ${libfmt})

add_test(NAME database_managers COMMAND m_tests)
