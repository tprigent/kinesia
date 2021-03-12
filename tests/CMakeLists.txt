cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_COMPILER "gcc")
project(Logiciel_Kine C)

set(CMAKE_C_STANDARD 90)
find_package(SQLite3)


include(${PROJECT_SOURCE_DIR}/cmake/FetchCMocka.cmake)
set(SOURCE_FILES ../src/UTest.c ../src/UTest_UI.c ../src/UTest_BDD.c ../src/connect_struct_UI.c ../src/patient.c)
add_executable(UnitTest ../src/UTest.c ${SOURCE_FILES})

#define the path to open database in test mode
target_compile_definitions(UnitTest PRIVATE DB_PATH="../../src/database/Bdd.db")

target_compile_features(UnitTest PRIVATE c_std_90)
target_link_libraries(UnitTest cmocka-static)

enable_testing()
add_test(NAME UnitTest COMMAND UnitTest)

target_link_libraries(UnitTest sqlite3)
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(UnitTest ${CMAKE_DL_LIBS} Threads::Threads)
