cmake_minimum_required(VERSION 3.22)
set(LIB_NAME "Controller")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ---- LIB COMPILATION ----
file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/source/*.cpp)
add_library(${LIB_NAME} ${SRC_FILES})
target_include_directories(${LIB_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)

target_link_libraries(${LIB_NAME} PUBLIC Model)
