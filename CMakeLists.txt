cmake_minimum_required(VERSION 3.0.0)
project(main)

add_subdirectory(lib)

message("COUNTRIES_LIB_INCLUDE_DIRS = ${COUNTRIES_LIB_INCLUDE_DIRS}")
message("COUNTRIES_LIB_LIBRARIES = ${COUNTRIES_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${COUNTRIES_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${COUNTRIES_LIB_LIBRARIES})

add_subdirectory(tests)
