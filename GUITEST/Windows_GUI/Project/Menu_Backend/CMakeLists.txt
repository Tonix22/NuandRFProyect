cmake_minimum_required(VERSION 3.1.0)
project(Backend VERSION 1.0.0 LANGUAGES CXX)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

add_library(Backend Sci_units.cpp Input_text.cpp Bridge_broker.cpp Load_File.cpp)

target_link_libraries(Backend Qt5::Widgets Tolteca_GUI Bridge)

target_include_directories (Backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../QT_cmake ${CMAKE_CURRENT_SOURCE_DIR}/../Bridge)
