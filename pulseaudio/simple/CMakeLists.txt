cmake_minimum_required(VERSION 2.8)
project(music)

FILE(GLOB_RECURSE Sources *.cc)

add_definitions("-O0 -std=c++11 -march=native -g -Wall -Wextra -pedantic")

add_executable(${PROJECT_NAME} ${Sources})

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  FIND_LIBRARY(COREAUDIO_LIBRARY CoreAudio)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    target_link_libraries(${PROJECT_NAME} pulse-simple)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
