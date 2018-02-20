cmake_minimum_required(VERSION 3.2)
project(MazeSolver)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

set(SOURCE_FILES main.cpp Cell.h Cell.cpp MazeGenerator.h MazeGenerator.cpp)
add_executable(MazeSolver ${SOURCE_FILES})

target_link_libraries(MazeSolver SDL2main SDL2)