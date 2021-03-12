# CMake settings
cmake_minimum_required(VERSION 3.17)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 90)

# Project settings
project(Logiciel_Kine C)

# Modules included
include(FindPkgConfig)
find_package(SQLite3)
pkg_check_modules(GTK3 REQUIRED "gtk+-3.0")
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

# Source files
set(SOURCE_FILES
        src/main.c
        src/UI.c
        src/connect_struct_UI.c
        src/editor_views.c
        src/home_view.c
        src/work_view.c
        src/patient.c
        src/connect_UI_struct.c
        #src/seance.c
        src/extern_files_manager.c src/extern_files_manager.h)

add_executable(Kinesia ${SOURCE_FILES})

# Code constants
target_compile_definitions(Kinesia PRIVATE DB_PATH="../src/database/Bdd.db")

# Linked libraries
target_link_libraries(Kinesia sqlite3)

# Threads
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(Kinesia ${GTK3_LIBRARIES} pthread ${CMAKE_DL_LIBS} Threads::Threads)
