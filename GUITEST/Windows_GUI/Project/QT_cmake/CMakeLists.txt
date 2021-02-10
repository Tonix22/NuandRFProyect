cmake_minimum_required(VERSION 3.1.0)

project(Tolteca_GUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)


add_library(Tolteca_GUI
    Frameworkhelp.ui
    my_mainwindow.cpp   
    app.cpp
    logo.qrc
)

target_link_libraries(Tolteca_GUI Qt5::Widgets Bridge -L${QTMW}/lib/ -lqtmw -L${LMW}/lib/ -lmw)

target_include_directories (Tolteca_GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../Bridge ${QTMW}/include ${LMW}/include)
