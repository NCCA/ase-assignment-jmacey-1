#include <gtest/gtest.h>

#include "PointVizReader.h"

TEST(PointVizReader,ctor)
{
    pv::PointVizReader r("files/singleValue10Frames.csv");
    EXPECT_TRUE(r.isOpen());
}