#ifndef POINTVIZWRITER_H_
#define POINTVIZWRITER_H_
#include <string_view>
#include <fstream>
#include <variant>

namespace pv
{
    enum class FrameTimeType {INT,FLOAT,DOUBLE};

    class PointVizWriter
    {
    public :
        // @brief construct with filename
        // @param _filename the name and path of file to open.
        PointVizWriter(std::string_view _filename);
        ~PointVizWriter();
        // @brief write data to the stream verbatim
        void write(std::string_view _str);
        // @brief write data to stream and newline.
        void writeln(std::string_view _str);
        void setFrameType(FrameTimeType _t);
        FrameTimeType getFrameType() const;


    private :
        std::ofstream m_stream;
        FrameTimeType m_frameType=FrameTimeType::INT;
        std::variant<int,float,double> m_frameNumber=0;
    };
}
#endif