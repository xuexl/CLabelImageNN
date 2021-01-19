cmake_minimum_required(VERSION 3.16.0)

project(labelimage VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(PROJECT_SOURCES
        main.cxx
        MainWindow.cxx
        MainWindow.h
        MainWindow.ui
        Config.h
        ImageViewer.h
        ImageViewer.cxx
        Cout.h
)

add_executable(labelimage ${PROJECT_SOURCES})

target_link_libraries(labelimage PRIVATE Qt6::Widgets ${OpenCV_LIBS})
