cmake_minimum_required(VERSION 3.10)
project(TreeVisualization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Set Qt installation path
set(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5")

# Find the Qt package
find_package(Qt5 COMPONENTS Widgets Core Gui REQUIRED)

# Add source files
set(SOURCES
        main.cpp
        mainwindow.cpp
)

# Add the .ui file
qt5_wrap_ui(UI_HEADERS mainwindow.ui)

# Add the .hpp file for moc
set(HEADERS
        mainwindow.hpp
)

# Process the headers with moc
qt5_wrap_cpp(MOC_SOURCES ${HEADERS})

# Add executable
add_executable(TreeVisualization ${SOURCES} ${UI_HEADERS} ${MOC_SOURCES})

# Include directories
target_include_directories(TreeVisualization PRIVATE ${Qt5Widgets_INCLUDE_DIRS} ${Qt5Core_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS})

# Link the Qt libraries
target_link_libraries(TreeVisualization Qt5::Widgets Qt5::Core Qt5::Gui)