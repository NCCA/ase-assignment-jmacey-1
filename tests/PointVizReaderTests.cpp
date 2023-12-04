#include <gtest/gtest.h>

#include "PointVizReader.h"

TEST(PointVizReader,ctor)
{
    pv::PointVizReader r("files/singleValue10Frames.csv");
    EXPECT_TRUE(r.isOpen());
}

TEST(PointVizReader,parseSimple)
{
    {
        pv::PointVizReader r("files/singleValue10Frames.csv");
        EXPECT_TRUE(r.isOpen());
        EXPECT_TRUE(r.parse());
        r.print();
    }
    {
        pv::PointVizReader r("files/multipleValue10Frames.csv");
        EXPECT_TRUE(r.isOpen());
        EXPECT_TRUE(r.parse());
        r.print();
    }
}


TEST(PointVizReader,iterate)
{
    {
        pv::PointVizReader r("files/singleValue10Frames.csv");
        EXPECT_TRUE(r.isOpen());
        EXPECT_TRUE(r.parse());

        for (auto &f : r)
        {
            for(auto d : *f)
                EXPECT_EQ(d.size() , 3);
        }
    }
}