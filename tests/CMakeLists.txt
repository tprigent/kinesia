cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_COMPILER "gcc")
project(Logiciel_Kine C)

#include(FindPkgConfig)

#pkg_check_modules(GTK3 REQUIRED "gtk+-3.0")

#include_directories(${GTK_INCLUDE_DIRS})
#link_directories(${GTK3_LIBRARY_DIRS})

#add_definitions(${GTK3_CFLAGS_OTHER})
set(CMAKE_C_STANDARD 90)


include(${PROJECT_SOURCE_DIR}/cmake/FetchCMocka.cmake)
set(SOURCE_FILES ../src/UTest_UI.c ../src/connect_struct_UI.c ../src/patient.c ../src/sqlite3.c)
add_executable(CMockaExample ../src/UTest_UI.c ${SOURCE_FILES})

target_compile_features(CMockaExample PRIVATE c_std_99)
target_link_libraries(CMockaExample cmocka-static)

enable_testing()
add_test(NAME CMockaExample COMMAND CMockaExample)

find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
#target_link_libraries(${CMAKE_DL_LIBS} Threads::Threads)
target_link_libraries(CMockaExample ${GTK3_LIBRARIES} pthread)