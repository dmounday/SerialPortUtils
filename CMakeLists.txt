cmake_minimum_required(VERSION 3.0.0)
project(SerialUtils VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(SerialIOLib)


add_executable(SerialUtils main.cpp)
target_include_directories(SerialUtils PRIVATE plog/include SerialIOLib)
target_link_libraries(SerialUtils PRIVATE pthread SerialIOLib)

