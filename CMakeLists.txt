cmake_minimum_required(VERSION 3.16)
project(Robot_Logist)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES Robot_App/src/*.cpp)

add_executable(Robot_Logist ${SOURCES})
# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(Robot_App/libs/raylib-4.1 ./Robot_App/libs/raylib)
target_link_libraries(Robot_Logist PRIVATE raylib)
