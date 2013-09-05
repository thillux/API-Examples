cmake_minimum_required(VERSION 2.8)
project(png_snippet)

FILE(GLOB_RECURSE Sources *.cc)

add_definitions("-O0 -std=c++11 -march=native -g -Wall -Wextra -pedantic")

add_executable(${PROJECT_NAME} ${Sources})

## Link libraries
find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${PNG_LIBRARY})

