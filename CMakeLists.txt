cmake_minimum_required(VERSION 3.16)

project(MatrixProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()


# # add_subdirectory(lib/cpp_subprocess)
add_subdirectory(lib/FTXUI)

set(APP_SOURCES 
        src/main.cpp
        src/ui/mainMenuComponent.cpp


        src/ui/screens/array_operations/menuLab_1.cpp
        src/ui/screens/array_operations/CreateArrayView.cpp
        src/ui/screens/array_operations/FillArrayView.cpp
        src/ui/screens/array_operations/FillArrayRandomView.cpp
        src/ui/screens/array_operations/ShowArrayView.cpp
        src/ui/screens/array_operations/SubMenuSortArray.cpp
        src/ui/screens/array_operations/SubMenuSearchComponent.cpp

        src/ui/screens/matrix_operations/menuLab_3.cpp 
        src/ui/screens/file_operations/menuLab2.cpp

        src/ui/components/InfoComponent.cpp 
        )

set(CORE_SOURCES 
        core/array_logic/ArrayModel.cpp 
        core/array_logic/ArrayAutoFiller.cpp

        core/matrix_logic/matrix.cpp
        )

set(UTILS_SOURCES 
        utils/io/portable_io.cpp 

        utils/io/sorting/MergeSort.cpp
        utils/io/math/math_utils.cpp
        )

add_executable(app 
            ${APP_SOURCES}
            ${CORE_SOURCES}
            ${UTILS_SOURCES}
            )


target_compile_options(app PRIVATE -Wall -Wextra)
target_precompile_headers(app PRIVATE src/pch.h)
target_include_directories(app PRIVATE ${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/core ${PROJECT_SOURCE_DIR}/utils)
target_link_libraries(app PRIVATE ftxui::screen ftxui::dom ftxui::component)
