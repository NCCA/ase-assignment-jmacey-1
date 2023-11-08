cmake_minimum_required(VERSION 3.20)

if( NOT DEFINED CMAKE_TOOLCHAIN_FILE AND ENV{CMAKE_TOOLCHAIN_FILE})
    set(CMAKE_TOOLCHAIN_FILE $ENV{CMAKE_TOOLCHAIN_FILE})
endif()

project(PointViz_build)

set(CMAKE_CXX_STANDARD 17)
find_package(fmt CONFIG REQUIRED)

## Test Data Gen Programs
set(GenDataName GenerateTestDataFiles)
add_executable(${GenDataName} )
target_include_directories(${GenDataName} PRIVATE include)
target_sources(${GenDataName} PRIVATE
        src/GenerateTestDataFiles.cpp
        src/PointVizWriter.cpp
        include/PointVizWriter.h
        include/PointVizTypes.h
        include/PointVizDataModel.h
)


### Testing Code
find_package(GTest CONFIG REQUIRED)
include(GoogleTest)
set(TestName PointVizTests)
add_executable(${TestName} )
set(CMAKE_CXX_STANDARD 17)

target_include_directories(${TestName} PRIVATE include)
target_sources(${TestName} PRIVATE
        tests/PointVizWriterTests.cpp
        tests/PointVizReaderTests.cpp
        src/PointVizWriter.cpp
        include/PointVizWriter.h
        src/PointVizReader.cpp
        include/PointVizReader.h
        include/PointVizTypes.h
        include/PointVizDataModel.h

)
target_link_libraries(${TestName} PRIVATE  GTest::gtest_main )
gtest_discover_tests(${TestName})

add_custom_target(${TestName}CopyTestFiles ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/files
        ${PROJECT_BINARY_DIR}/files
)

ADD_DEPENDENCIES(${TestName} ${TestName}CopyTestFiles)
