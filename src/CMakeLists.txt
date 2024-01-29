cmake_minimum_required(VERSION 3.5)
project(s21_SmartCalculator)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

if("${CMAKE_C_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options("-Wall" "-Werror" "-Wextra" "-Wpedantic" "-Weffc++")
else()
    message("WE NEED GCC FOR CODE COVERAGE AND COMPILE OPTIONS REQUIRED BY SCHOOL")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/modules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_AUTOUIC ON)
# set(CMAKE_AUTOMOC ON)
# set(CMAKE_AUTORCC ON)

add_subdirectory(Model)
add_subdirectory(View)
add_subdirectory(dependencies)


# ---- TEST COMPILATION ----
cmake_path(APPEND OBJECTS_PATH "${CMAKE_SOURCE_DIR}" "Model" "test")
#file(GLOB TEST_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_LIST_DIR}/Model/test/*.cc)
#add_executable(test ${TEST_FILES})
#target_link_libraries(test PUBLIC ${PROJECT_NAME} gtest gtest_main)

# ---- FORMATTING ----
set(CLANG_FORMAT_EXCLUDE_PATTERNS  "build/" "dependencies/" ${CMAKE_BINARY_DIR})
find_package(ClangFormat)

# cmake_path(APPEND OBJECTS_PATH "${CMAKE_SOURCE_DIR}" "View" "test")
# configure_file(settings_path.h.in settings_path.h @ONLY)
# add_subdirectory(View)

# find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
# find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# # remove this 
# set(PROJECT_SOURCES
#         ./View/source/main.cpp
#         ./View/source/mainwindow.cpp
#         ./View/include/mainwindow.h
#         ./View/source/mainwindow.ui
#         qcustomplot.cpp
#         qcustomplot.h
# )

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(s21_SmartCalculator
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
#     target_link_libraries(s21_SmartCalculator PRIVATE View Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::OpenGLWidgets Qt${QT_VERSION_MAJOR}::OpenGL giflib)
# else()
#     add_executable(s21_SmartCalculator
#             ${PROJECT_SOURCES}
#     )
#     target_link_libraries(s21_SmartCalculator PRIVATE View Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui giflib)
# endif()

# target_link_libraries(s21_SmartCalculator PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# set_target_properties(s21_SmartCalculator PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(s21_SmartCalculator)
# endif()

