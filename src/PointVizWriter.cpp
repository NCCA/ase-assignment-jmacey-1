#include "PointVizWriter.h"

namespace pv
{

    PointVizWriter::PointVizWriter(std::string_view _filename,FrameTimeType _frameType) :
    m_frameType{_frameType}
    {
        m_stream.open(_filename);

        switch (m_frameType) {
            case FrameTimeType::INT :
                m_frameNumber = 0;
                break;
            case FrameTimeType::FLOAT :
                m_frameNumber = 0.0f;
                break;
            case FrameTimeType::DOUBLE :
                m_frameNumber = 0.0;
                break;

        }

    }

    PointVizWriter::~PointVizWriter()
    {
        m_stream.close();
    }



    FrameTimeType PointVizWriter::getFrameType() const
    {
        return m_frameType;
    }


    void PointVizWriter::write(std::string_view _str)
    {
        m_stream<<_str;
    }
    void PointVizWriter::writeln(std::string_view _str)
    {
        m_stream<<_str<<'\n';
    }

    bool PointVizWriter::setFrame(std::variant<int, float, double> _frame)
    {
        bool canSet=false;
        switch (m_frameType)
        {
            case FrameTimeType::INT :
                if (std::get<int>(_frame) >= std::get<int>(m_frameNumber))
                {
                    m_frameNumber=_frame;
                    canSet=true;
                    m_stream<<"Frame "<<std::get<int>(m_frameNumber)<<'\n';
                }
            break;
            case FrameTimeType::FLOAT :
                if (std::get<float>(_frame) >= std::get<float>(m_frameNumber))
                {
                    m_frameNumber=_frame;
                    canSet=true;
                    m_stream<<"Frame "<<std::get<float>(m_frameNumber)<<'\n';
                }
            break;

            case FrameTimeType::DOUBLE :
                if (std::get<double>(_frame) >= std::get<double>(m_frameNumber))
                {
                    m_frameNumber=_frame;
                    canSet=true;
                    m_stream<<"Frame "<<std::get<double>(m_frameNumber)<<'\n';
                }
            break;

        }
    return canSet;
    }


std::variant<int,float,double> PointVizWriter::frameNumber() const
{
        return m_frameNumber;
}

}

