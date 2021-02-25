cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_COMPILER "gcc")
project(Logiciel_Kine C)

set(CMAKE_C_STANDARD 90)


include(${PROJECT_SOURCE_DIR}/cmake/FetchCMocka.cmake)
set(SOURCE_FILES ../src/UTest.c ../src/UTest_UI.c ../src/connect_struct_UI.c ../src/patient.c ../src/sqlite3.c)
add_executable(CMockaExample ../src/UTest.c ${SOURCE_FILES})

#define the path to open database in test mode
target_compile_definitions(CMockaExample PRIVATE DB_PATH="../../src/database/Bdd.db")

target_compile_features(CMockaExample PRIVATE c_std_90)
target_link_libraries(CMockaExample cmocka-static)

enable_testing()
add_test(NAME CMockaExample COMMAND CMockaExample)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(CMockaExample ${CMAKE_DL_LIBS} Threads::Threads)