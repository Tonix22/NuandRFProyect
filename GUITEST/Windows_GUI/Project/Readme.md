
### System Verions 
	* Windows10 Home and higher
	* CMAKE 3.19.3
	* C++11
	* QT Creator 4.14

### System Dependencies
	For making building work in QT Creator, you must have an IPDI dependency installed.
	Unzip the [IPDI Folder](ipdi-qt-wrapper-installer-x64-(20210205).zip) and install depencies. You can ommit the restart message prompted after instalation
	

### IMPORT THIS PROJECT INTO QT CREATOR

	1. Delete CmakeLists.txt.user
	2. Open main CMakeLists in QT Createor
	3. Configure Project


## NOT REQUIRED BUT USEFUL INFO

To make .qrc image work on upper folder there is neede to call this 
seters, so the make file will fetch the QT_cmake/logo.qrc.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
https://cmake.org/cmake/help/v3.0/manual/cmake-qt.7.html

Notes for windows 
cmake for windows

cmake -S E:/5.15.2/mingw81_64/GUITEST/Project -B E:/5.15.2/mingw81_64/GUITEST/build-Project-Desktop_Qt_5_15_2_MinGW_64_bit-Release -GNinja "-DCMAKE_BUILD_TYPE:String=Release" "-DQT_QMAKE_EXECUTABLE:STRING=E:/5.15.2/mingw81_64/bin/qmake.exe" "-DCMAKE_PREFIX_PATH:STRING=E:/5.15.2/mingw81_64" "-DCMAKE_C_COMPILER:STRING=E://Tools/mingw810_64/bin/gcc.exe" "-DCMAKE_CXX_COMPILER:STRING=E://Tools/mingw810_64/bin/g++.exe" in E:\5.15.2\mingw81_64\GUITEST\build-Project-Desktop_Qt_5_15_2_MinGW_64_bit-Release.