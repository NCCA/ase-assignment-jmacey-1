#include <iostream>
#include <cstdlib>
#include "PointVizWriter.h"

int main()
{
    {
        pv::PointVizWriter op("singleValue10Frames.csv");
        for (int frame = 0; frame < 10; ++frame) {
            op.setFrame(frame);
            auto p = static_cast<float>(frame) / 10.0f;
            op << p << ',' << p << ',' << p << '\n';
        }
    }
    {
        pv::PointVizWriter op("multipleValue10Frames.csv");
        for (int frame = 0; frame < 10; ++frame) {
            op.setFrame(frame);
            for (int pnum = 0; pnum <= 10; ++pnum) {
                auto p = static_cast<float>(pnum)+frame / 10.0f;
                op << p << ',' << p << ',' << p << '\n';
            }
        }
    }

    {
        pv::PointVizWriter op("singleValueWithHeader.csv");
        op.writeHeader(pv::HeaderType::Float,pv::HeaderType::Float,pv::HeaderType::Float,pv::HeaderType::Int);
        for (int frame = 0; frame < 10; ++frame)
        {
            op.setFrame(frame);
            auto p = static_cast<float>(frame) / 10.0f;
            op << p << ',' << p << ',' << p <<','<<frame<<'\n';
        }
    }



    return EXIT_SUCCESS;
}