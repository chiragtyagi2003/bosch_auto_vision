cmake_minimum_required(VERSION 3.10)
project(auto_vision)

# find opencv package
find_package(OpenCV REQUIRED)

# include the directories from OpenCV
include_directories(${OpenCV_INCLUDE_DIRS})


# create the executable
add_executable(auto_vision main.cpp)


# link opencv libraries
target_link_libraries(auto_vision ${OpenCV_LIBS})