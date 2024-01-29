set(LIB_NAME "Model")
#include_directories(include)
#include_directories(source)
#include_directories(test)

# ---- LIB COMPILATION ----
file(GLOB SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/${LIB_NAME}/source/*.cpp)
add_library(${LIB_NAME} ${SRC_FILES})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${LIB_NAME}/include)


# ---- LIB COMPILATION ----
#file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/include/*.h)
#file(GLOB SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/source/*.cpp)
#add_library(${PROJECT_NAME} ${SRC_FILES})
#target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib)


# ---- TEST COMPILATION ----
file(GLOB TEST_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/${LIB_NAME}/test/*.cc)
add_executable(test ${TEST_FILES})
target_link_libraries(test PUBLIC ${LIB_NAME} gtest gtest_main)

# ---- GCOV-REPORT ----
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" AND CMAKE_BUILD_TYPE STREQUAL "Debug")
include(CodeCoverage)
append_coverage_compiler_flags_to_target(test)
append_coverage_compiler_flags_to_target(${LIB_NAME})
setup_target_for_coverage_lcov(
            NAME test_coverage
            EXECUTABLE test
            EXCLUDE ${CMAKE_BINARY_DIR}/* "${PROJECT_SOURCE_DIR}/dependencies/*" "/Applications/*" "/usr/local/*" "/usr/include/*"
            DEPENDENCIES test ${LIB_NAME} 
    )
endif()
