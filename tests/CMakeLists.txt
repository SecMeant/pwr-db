cmake_minimum_required(VERSION 3.10)

file( GLOB T_SRC "src/*.cc")
find_library(libgtest gtest REQUIRED)
find_library(libgtestmain gtest_main REQUIRED)
find_library(libgmock gmock REQUIRED)
find_library(libpthread pthread REQUIRED)

add_executable(m_tests ${T_SRC})
target_link_libraries(m_tests ${libgtestmain} ${libgtest} ${libgmock} ${libpthread} ${TARGET_LIB_NAME} ${libfmt})

add_test(NAME database_managers COMMAND m_tests)
