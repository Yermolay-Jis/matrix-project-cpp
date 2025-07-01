cmake_minimum_required(VERSION 3.15)

project(MatrixProject CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
  GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(ftxui)



include_directories(include)

file(GLOB SOURCE_FILES "src/*.cpp")

add_executable(app ${SOURCE_FILES})

add_compile_options(-finput-charset=UTF-8)

target_compile_options(app PRIVATE -w)

target_link_libraries(app PRIVATE ftxui::dom ftxui::screen)
