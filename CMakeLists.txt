cmake_minimum_required(VERSION 3.14)

project(MatrixProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

include(FetchContent)
FetchContent_Declare(ftxui GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git GIT_TAG v5.0.0)
FetchContent_MakeAvailable(ftxui)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(app ${SOURCE_FILES})

add_compile_options(-finput-charset=UTF-8)

target_compile_options(app PRIVATE -Wall -Wextra)

target_link_libraries(app PRIVATE ftxui::screen)
