#include <gtest/gtest.h>
#include "PointVizWriter.h"
#include <filesystem>
#include <fstream>
namespace fs=std::filesystem;

TEST(PointVizWriter,ctor)
{
    pv::PointVizWriter o("test.csv");
    EXPECT_TRUE(fs::exists("test.csv"));
    fs::remove("test.csv");
    EXPECT_FALSE(fs::exists("test.csv"));
}

TEST(PointVizWriter,writeTest)
{
    pv::PointVizWriter o("test.csv");
    EXPECT_TRUE(fs::exists("test.csv"));
    o.write("0.1,0.2,0.3\n");
    o.writeln("0.1,0.2,0.3");
}

TEST(PointVizWriter,frameType)
{
    pv::PointVizWriter o("t.csv");
    EXPECT_TRUE(o.getFrameType() == pv::FrameTimeType::INT);
    o.setFrameType(pv::FrameTimeType::DOUBLE);
    EXPECT_TRUE(o.getFrameType() == pv::FrameTimeType::DOUBLE);
    o.setFrameType(pv::FrameTimeType::FLOAT);
    EXPECT_TRUE(o.getFrameType() == pv::FrameTimeType::FLOAT);
    fs::remove("t.csv");
}

TEST(PointVizWriter,testFrame)
{
    pv::PointVizWriter o("t.csv");
    o.setFrame(1);
}




