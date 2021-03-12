# CMake settings
cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 90)

# Project settings
project(Logiciel_Kine C)
find_package(SQLite3)
include(${PROJECT_SOURCE_DIR}/cmake/FetchCMocka.cmake)

# Source files
set(SOURCE_FILES
        UTest.c
        UTest_UI.c
        ../src/controler/struct_to_UI.c
        ../src/patient.c
        ../src/controler/UI_to_struct.c)

add_executable(UnitTest UTest.c ${SOURCE_FILES})

# Code constants
target_compile_definitions(UnitTest PRIVATE DB_PATH="../../src/model/data.db")

# Testing
enable_testing()
add_test(NAME UnitTest COMMAND UnitTest)

# Linked libraries
target_link_libraries(UnitTest sqlite3)
target_link_libraries(UnitTest cmocka-static)

# Threads
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(UnitTest ${CMAKE_DL_LIBS} Threads::Threads)
