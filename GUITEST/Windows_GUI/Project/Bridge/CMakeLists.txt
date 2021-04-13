cmake_minimum_required(VERSION 3.1.0)
project(Bridge VERSION 1.0.0 LANGUAGES CXX)

set(IPDI_WIN "C:/ipdi")
set(QTMW "${IPDI_WIN}/wrappers/Qt")
set(LMW "${IPDI_WIN}/base")

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_library(Bridge bridge.cpp COM_finder.cpp)

target_link_libraries(Bridge Qt5::Widgets Tolteca_GUI -L${QTMW}/lib/ -lqtmw -L${LMW}/lib/ -lmw -lshlwapi)

target_include_directories (Bridge PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../QT_cmake ${QTMW}/include ${LMW}/include)
