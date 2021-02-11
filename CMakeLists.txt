cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "gcc")
project(Logiciel_Kine C)

include(FindPkgConfig)
pkg_check_modules(GTK REQUIRED "gtk+-3.0")

include_directories(${GTK_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})
set(CMAKE_C_STANDARD 90)

set(SOURCE_FILES main.c main_UI.c gtk_functions.c main_UI.h patient.c patient.h)

add_executable(main.c ${SOURCE_FILES} sqlite3.c)
target_link_libraries(main.c ${GTK3_LIBRARIES} pthread)
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(Logiciel_Kine PRIVATE ${CMAKE_DL_LIBS} Threads::Threads)