cmake_minimum_required(VERSION 3.8) # Kittens will die if you switch to an earlier version of CMake.

project(BIKE)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -MMD -MP")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(BIKE src/main.cpp src/Log.cpp src/RentLog.cpp src/ReturnLog.cpp src/Station.cpp)

find_package(Boost REQUIRED COMPONENTS filesystem system)

target_link_libraries(BIKE
    PRIVATE
        Boost::filesystem
        Boost::system
)
