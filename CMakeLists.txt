cmake_minimum_required (VERSION 3.0.0)
project(52 VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#use the c++ 14 standard
set(CMAKE_CXX_STANDARD 14)

#Bring the headers, such as game.h into the project
include_directories( include )

#Find all cpp files
file(GLOB SOURCES "src/*.cpp")

#Building SeWorms
add_executable(52 ${SOURCES})

target_link_libraries(52 ${OpenCV_LIBS})