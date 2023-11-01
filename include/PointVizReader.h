#ifndef POINTVIZREADER_H_
#define POINTVIZREADER_H_
#include <string_view>
#include <fstream>

namespace pv
{
    class PointVizReader
    {
    public :
        PointVizReader(std::string_view filename);
        ~PointVizReader();
        bool isOpen() const;
    private :
        std::ifstream m_stream;

    };
}



#endif
