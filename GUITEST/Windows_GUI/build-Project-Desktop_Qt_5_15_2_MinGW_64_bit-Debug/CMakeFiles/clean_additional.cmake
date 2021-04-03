# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Tolteca_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Tolteca_autogen.dir\\ParseCache.txt"
  "QT_cmake\\CMakeFiles\\Tolteca_GUI_autogen.dir\\AutogenUsed.txt"
  "QT_cmake\\CMakeFiles\\Tolteca_GUI_autogen.dir\\ParseCache.txt"
  "QT_cmake\\Tolteca_GUI_autogen"
  "Tolteca_autogen"
  )
endif()
