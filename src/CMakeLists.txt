cmake_minimum_required(VERSION 3.5)
project(s21_SmartCalculator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options("-Wall" "-Wextra" "-Wpedantic" ) # "-Werror" "-Weffc++"
else()
    message("WE NEED GCC FOR CODE COVERAGE AND COMPILE OPTIONS REQUIRED BY SCHOOL")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/modules)

add_subdirectory(View)
add_subdirectory(Controller)
add_subdirectory(Model)
add_subdirectory(dependencies)
include_directories(View)

add_executable(s21_SmartCalculator main.cpp)

# ---- TEST COMPILATION ----
cmake_path(APPEND OBJECTS_PATH "${CMAKE_SOURCE_DIR}" "Model" "test")

# ---- FORMATTING ----
set(CLANG_FORMAT_EXCLUDE_PATTERNS  "build/" "dependencies/" "*/qcustomplot." ${CMAKE_BINARY_DIR})
find_package(ClangFormat)


target_link_libraries(${PROJECT_NAME} PUBLIC View)