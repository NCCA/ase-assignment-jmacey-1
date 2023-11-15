#ifndef POINTVIZDATAMODEL_H_
#define POINTVIZDATAMODEL_H_
#include <vector>
#include <variant>
namespace pv
{
    struct Frame
    {
        Frame()=default;
        Frame(const Frame &)=default;
        Frame( Frame &&)=default;

        std::variant<int,float,double> m_actualFrameTime;
        std::vector<std::vector<std::variant<int,float,double>>> m_frameData;
    };
}



#endif
