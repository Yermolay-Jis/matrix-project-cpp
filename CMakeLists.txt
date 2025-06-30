cmake_minimum_required(VERSION 3.15)

project(MatrixProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(app ${SOURCE_FILES})