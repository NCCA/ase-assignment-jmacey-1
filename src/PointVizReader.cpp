#include "PointVizReader.h"

namespace pv
{
    PointVizReader::PointVizReader(std::string_view _filename)
    {
        m_stream.open(_filename);
    }

    PointVizReader::~PointVizReader()
    {
        m_stream.close();
    }
    bool PointVizReader::isOpen() const
    {
        return m_stream.is_open();
    }

}