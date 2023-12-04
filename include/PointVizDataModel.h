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
        auto begin() { return std::begin(m_frameData);}
        auto end() { return std::end(m_frameData);}
        auto cbegin() const { return std::cbegin(m_frameData);}
        auto cend() const { return std::cend(m_frameData);}

        size_t size() const {return m_frameData.size();}
        std::variant<int,float,double> m_actualFrameTime;
        std::vector<std::vector<std::variant<int,float,double>>> m_frameData;

    };
}



#endif
