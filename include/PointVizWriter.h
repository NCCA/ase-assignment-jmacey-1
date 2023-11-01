#ifndef POINTVIZWRITER_H_
#define POINTVIZWRITER_H_
#include <string_view>
#include <fstream>
#include <ostream>

#include <variant>

namespace pv
{
    enum class FrameTimeType {INT,FLOAT,DOUBLE};

    class PointVizWriter
    {
    public :
        // @brief construct with filename
        // @param _filename the name and path of file to open.
        PointVizWriter(std::string_view _filename, FrameTimeType _frameType=FrameTimeType::INT);
        ~PointVizWriter();
        // @brief write data to the stream verbatim
        void write(std::string_view _str);
        // @brief write data to stream and newline.
        void writeln(std::string_view _str);
        FrameTimeType getFrameType() const;
        bool setFrame(std::variant<int,float,double> _frame);
        std::variant<int,float,double> frameNumber() const ;

        /* code generate from co-pilot
         * prompt :
         * given this class how do I overload the << operator so I can write data to m_stream
         * in the form of obj<<1..0<<' '<<2.0<<'\n';
         * Code is copied verbatim
         */

        template<typename T>
        friend PointVizWriter& operator<<(PointVizWriter& pvw, const T& data)
        {
            pvw.m_stream << data;
            return pvw;
        }
        // end citation.
    private :
        std::ofstream m_stream;
        FrameTimeType m_frameType=FrameTimeType::INT;
        std::variant<int,float,double> m_frameNumber;
    };
}


#endif