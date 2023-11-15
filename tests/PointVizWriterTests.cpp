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


TEST(PointVizWriter,testFrame)
{
    pv::PointVizWriter o("t.csv");
    EXPECT_TRUE(o.setFrame(1));
    EXPECT_FALSE(o.setFrame(0));
}

TEST(PointVizWriter,writeFrameTestInt)
{
    pv::PointVizWriter o("test.csv");
    EXPECT_TRUE(fs::exists("test.csv"));
    for(int i=0; i<10; ++i)
    {
        o.setFrame(i);
        o.write("0.1,0.2,0.3\n");
        o.writeln("0.1,0.2,0.3");
    }
}


TEST(PointVizWriter,writeFrameTestFloat)
{
    pv::PointVizWriter o("test.csv",pv::FrameTimeType::FLOAT);
    EXPECT_TRUE(fs::exists("test.csv"));
    for(float i=0.0f; i<1.0f; i+=0.1f)
    {
        o.setFrame(i);
        o.write("0.1,0.2,0.3\n");
        o.writeln("0.1,0.2,0.3");
    }
}

TEST(PointVizWriter,writeFrameTestDouble)
{
    pv::PointVizWriter o("testDouble.csv",pv::FrameTimeType::DOUBLE);
    EXPECT_TRUE(fs::exists("testDouble.csv"));
    for(double i=0.00000; i<0.01; i+=0.001)
    {
        o.setFrame(i);
        o.write("0.1,0.2,0.3\n");
        o.writeln("0.1,0.2,0.3");
    }
}
TEST(PointVizWriter,overLoad) {
    pv::PointVizWriter o("testDouble.csv", pv::FrameTimeType::DOUBLE);
    EXPECT_TRUE(fs::exists("testDouble.csv"));
    for (double i = 0.0; i < 0.05; i += 0.01) {
        o.setFrame(i);
        o << i << ' ' << i << ' ' <<  i << " # this is comment \n";

    }
}

TEST(PointVizWriter,HeaderWrite)
{
    pv::PointVizWriter o("testHeader.csv");
    o.writeHeader(pv::HeaderType::Float,pv::HeaderType::Float,pv::HeaderType::Float);
}