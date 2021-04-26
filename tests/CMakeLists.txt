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
        #UTest_BDD.c
        #UTest_session.c
        #UTest_BDD_session.c
        ../src/model/session_manager.c
        ../src/model/folder_manager.c
        ../src/model/patient_manager.c
        ../src/controller/BDD_to_struct_patient.c
        ../src/controller/BDD_to_struct_folder.c
        ../src/controller/BDD_to_struct_session.c
        ../src/controller/display_helpers.c
        ../src/controller/extern_files_manager.c
        ../src/controller/struct_to_BDD_folder.c
        ../src/controller/struct_to_BDD_session.c
        ../src/controller/struct_to_BDD_patient.c)

add_executable(UnitTest UTest.c ${SOURCE_FILES})

# Code constants
target_compile_definitions(UnitTest PRIVATE DB_PATH="../../src/model/data.db")

# Define OS macro
if(APPLE)
    target_compile_definitions(UnitTest PRIVATE OS="macOS")
endif(APPLE)

if(UNIX AND NOT APPLE)
    target_compile_definitions(UnitTest PRIVATE OS="linux")
endif (UNIX AND NOT APPLE)

if(WIN32)
    target_compile_definitions(UnitTest PRIVATE OS="Windows")
endif(WIN32)

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
