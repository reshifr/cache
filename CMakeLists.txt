cmake_minimum_required(VERSION 3.0)

project(cache)

set(CMAKE_CXX_STANDARD 20)
add_compile_options(-O3)

# Sources
set(SOURCES main.cpp)

include_directories(.)

# Executables
set(EXE cache)

add_executable(${EXE} ${SOURCES} ${HEADERS})
target_link_libraries(${EXE} crypto++)