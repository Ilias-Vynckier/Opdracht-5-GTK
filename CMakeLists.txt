cmake_minimum_required(VERSION 3.5)

set(PROJECT_NAME Opdracht5)
project(${PROJECT_NAME})

# Set the minimum version of cmake required to build this project
cmake_minimum_required(VERSION 2.6)
# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-2.0)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-2.4) # look into FindPkgConfig.cmake, 
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK2_INCLUDE_DIRS})
link_directories(${GTK2_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK2_CFLAGS_OTHER})
# Add an executable compiled from hello.c
add_executable(Opdracht5 main.c)
# Link the target to the GTK+ libraries
target_link_libraries(Opdracht5 ${GTK2_LIBRARIES})