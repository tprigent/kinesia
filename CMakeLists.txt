cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_C_COMPILER "gcc")
set(CMAKE_C_STANDARD 90)

# Project settings
project(Logiciel_Kine C)

# Modules included
include(FindPkgConfig)
find_package(PkgConfig)
find_package(SQLite3)
#find_package(gtk)
pkg_check_modules(GTK3 REQUIRED "gtk+-3.0")
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})
include(${PROJECT_SOURCE_DIR}/tests/cmake/FetchCMocka.cmake)


# *************************************** TARGET FOR PROGRAM ***********************************

# Source files
set(SOURCE_FILES
        src/view/main_UI.c
        src/controller/display_helpers.c
        src/view/editor_views.c
        src/view/home_view.c
        src/view/work_view.c
        src/model/patient_manager.c
        src/model/folder_manager.c
        src/controller/UI_to_struct.c
        src/model/session_manager.c
        src/controller/extern_files_manager.c
        src/model/structures.h
        src/controller/struct_to_BDD_patient.c
        src/controller/BDD_to_struct_patient.c
        src/controller/struct_to_BDD_folder.c
        src/controller/struct_to_BDD_session.c
        src/controller/BDD_to_struct_session.c
        src/controller/BDD_to_struct_folder.c)

add_executable(Kinesia ${SOURCE_FILES})

# Code constants
target_compile_definitions(Kinesia PRIVATE DB_PATH="../src/model/data.db")

# Define OS macro
if(APPLE)
    target_compile_definitions(Kinesia PRIVATE OS="macOS")
endif(APPLE)

if(UNIX AND NOT APPLE)
    target_compile_definitions(Kinesia PRIVATE OS="linux")
endif (UNIX AND NOT APPLE)

if(WIN32)
    target_compile_definitions(Kinesia PRIVATE OS="Windows")
endif(WIN32)

# Linked libraries
target_link_libraries(Kinesia sqlite3 )

# Threads
find_package(Threads REQUIRED)
set(THREADS_PREFER_PTHREAD_FLAG ON)
target_link_libraries(Kinesia ${GTK3_LIBRARIES} pthread ${CMAKE_DL_LIBS} Threads::Threads)



# *************************************** TARGET FOR UNIT TESTS ***********************************

# Source files
set(SOURCE_FILES_TEST
        tests/UTest.c
        tests/UTest_display_helpers.c
        tests/UTest_ext_files_manager.c
        tests/UTest_BDD.c
        tests/UTest_session.c
        tests/UTest_BDD_session.c
        src/model/patient_manager.c
        src/model/folder_manager.c
        src/model/session_manager.c
        src/controller/display_helpers.c
        src/controller/extern_files_manager.c
        src/controller/struct_to_BDD_patient.c
        src/controller/struct_to_BDD_folder.c
        src/controller/struct_to_BDD_session.c
        src/controller/BDD_to_struct_patient.c
        src/controller/BDD_to_struct_session.c
        src/controller/BDD_to_struct_folder.c)

add_executable(UnitTest tests/UTest.c ${SOURCE_FILES_TEST})


# Code constants
target_compile_definitions(UnitTest PRIVATE DB_PATH="../src/model/data.db")

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