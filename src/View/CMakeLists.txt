cmake_minimum_required(VERSION 3.5)
set(LIB_NAME "View")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS form)

include_directories(form)
include_directories(include)
include_directories(source)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

# file(GLOB SRC_FILES CONFIGURE_DEPENDS ${PROJECT_SOURCE_DIR}/${LIB_NAME}/source/*.cpp)


file(GLOB SRC_FILES
        ${PROJECT_SOURCE_DIR}/${LIB_NAME}/form/*.ui
        ${PROJECT_SOURCE_DIR}/${LIB_NAME}/include/*.h
        ${PROJECT_SOURCE_DIR}/${LIB_NAME}/source/*.cpp
    )
add_library(${LIB_NAME} ${SRC_FILES})
target_include_directories(${LIB_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/${LIB_NAME}/include)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(view
#         MANUAL_FINALIZATION
#         ${SRC_FILES}
#     )
# else()
#     add_executable(view ${SRC_FILES})
# endif()

target_link_libraries(${LIB_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Widgets)

# set_target_properties(${LIB_NAME} PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(View)
endif()
