#include "PointVizWriter.h"

namespace pv
{

    PointVizWriter::PointVizWriter(std::string_view _filename)
    {
        m_stream.open(_filename);
    }

    PointVizWriter::~PointVizWriter()
    {
        m_stream.close();
    }

    void PointVizWriter::setFrameType(FrameTimeType _t)
    {
        m_frameType=_t;
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
}