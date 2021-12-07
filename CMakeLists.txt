cmake_minimum_required(VERSION 3.0.0)
project(Opdracht5 VERSION 0.1.0)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK2 REQUIRED gtk+-2.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK2_CFLAGS_OTHER})

add_executable(Opdracht5 main.c)

target_link_libraries(Opdracht5 ${GTK2_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

