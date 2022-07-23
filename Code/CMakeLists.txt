cmake_minimum_required(VERSION 3.14)

project(Code LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_executable(Code
  sources/main.cpp
  headers/httpcontroller.h      sources/httpcontroller.cpp
  headers/jsonconverter.h       sources/jsonconverter.cpp
  headers/topology.h            sources/topology.cpp
  headers/topologyelements.h    sources/topologyelements.cpp
  headers/eventhandler.h        sources/eventhandler.cpp
)
target_link_libraries(Code Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Network)
