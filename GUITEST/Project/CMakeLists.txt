cmake_minimum_required(VERSION 3.1.0)

project(RF_APP)

#To make .qrc image work on upper folder there is neede to call this 
#seters, so the make file will fetch the QT_cmake/logo.qrc.
#set(CMAKE_AUTOMOC ON) set(CMAKE_AUTORCC ON) set(CMAKE_AUTOUIC ON)
#https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html

find_package(Qt5 COMPONENTS Widgets REQUIRED)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


add_subdirectory(QT_cmake)

add_executable (Tolteca main.cpp QT_cmake/logo.qrc)

target_link_libraries (Tolteca PRIVATE Tolteca_GUI)
