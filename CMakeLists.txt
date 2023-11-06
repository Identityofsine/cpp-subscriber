cmake_minimum_required(VERSION 3.0)

project(SubscribeLibrary)

# Set the C++ standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the source file to the project
add_executable(SubscribeLibrary main.cpp subscriberobj.cpp)
