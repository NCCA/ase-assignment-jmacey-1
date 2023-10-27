cmake_minimum_required(VERSION 3.20)

if( NOT DEFINED CMAKE_TOOLCHAIN_FILE AND ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(PointViz_build)

set(CMAKE_CXX_STANDARD 17)
find_package(fmt CONFIG REQUIRED)


### Testing Code
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
set(TestName PointVizTests)
add_executable(${TestName} )
set(CMAKE_CXX_STANDARD 17)

target_include_directories(${TestName} PRIVATE include)
target_sources(${TestName} PRIVATE
        tests/PointVizWriterTests.cpp
        src/PointVizWriter.cpp
        include/PointVizWriter.h
)
target_link_libraries(${TestName} PRIVATE GTest::gtest GTest::gtest_main )
gtest_discover_tests(${TestName})