# CMakeList.txt : CMake project for BugReportingTool, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project(BugReportingTool)

set( DCMAKE_TOOLCHAIN_FILE "D:/Code/vcpkg/Microsoft/vcpkg/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Boost 1.77.0 COMPONENTS filesystem thread system)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set ( CXX_SRCS
	BRTool.cpp
	BRWindow.cpp
	BRModel.cpp
	BRData.cpp
	BRController.cpp
	BRCreateDialog.cpp
	screenshotVideoWidget.cpp
)

include_directories(
	"D:/Code/vcpkg/Microsoft/vcpkg/installed/x64-windows/include/qt5"
	"D:/Code/vcpkg/Microsoft/vcpkg/installed/x64-windows/include/boost"
)

# Add source to this project's executable.
add_executable (project ${CXX_SRCS})

# TODO: Add tests and install targets if needed.
target_link_libraries( project
	Qt5::Core
	Qt5::Widgets
)
