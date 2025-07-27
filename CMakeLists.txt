cmake_minimum_required(VERSION 3.15)

project(MatrixProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

include_directories(include)


add_subdirectory(lib/cpp_subprocess)
add_subdirectory(lib/FTXUI)


file(GLOB SOURCE_FILES "src/*.cpp")



add_executable(app ${SOURCE_FILES})

# add_compile_options(-finput-charset=UNICODE)

target_compile_options(app PRIVATE -Wall -Wextra)

target_link_libraries(app PRIVATE ftxui::screen ftxui::dom ftxui::component)
