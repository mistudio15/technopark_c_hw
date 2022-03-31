cmake_minimum_required(VERSION 3.16)


project(hw2)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Werror  -fprofile-arcs -ftest-coverage -fPIC -pthread")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC -pthread")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )


include_directories(include)


set(FIND_CONSISTENT_LIB  ${PROJECT_SOURCE_DIR}/include/lib.h lib_consistent/lib_proc_consistent.c lib_manage_data/manage_data.c)
add_library(FIND_CONSISTENT_LIB STATIC ${FIND_CONSISTENT_LIB})
target_include_directories(FIND_CONSISTENT_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)


set(FIND_PARALLEL_LIB  ${PROJECT_SOURCE_DIR}/include/lib.h lib_parallel/lib_proc_parallel.c lib_manage_data/manage_data.c)
add_library(FIND_PARALLEL_LIB SHARED ${FIND_PARALLEL_LIB})
target_include_directories(FIND_PARALLEL_LIB PUBLIC ${PROJECT_SOURCE_DIR}/include)


add_executable(${PROJECT_NAME} main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE FIND_CONSISTENT_LIB)
target_link_libraries(${PROJECT_NAME} PRIVATE FIND_PARALLEL_LIB)


find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
add_executable(tests tests/gtests.cpp)
target_link_libraries(tests ${GTEST_LIBRARIES} FIND_CONSISTENT_LIB FIND_PARALLEL_LIB GTest::GTest gtest_main)


