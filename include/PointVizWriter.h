#ifndef POINTVIZWRITER_H_
#define POINTVIZWRITER_H_
#include <string_view>
#include <fstream>
#include <ostream>
#include <variant>
#include "PointVizTypes.h"
namespace pv
{

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

        template<typename T>
        void writeHeaderDetail(T _type)
        {
            static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");
            m_stream<<static_cast<char>(_type)<<' ';
        }

        template<typename T>
        void writeHeader( T _type)
        {
            static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");
            m_stream<<"Header "<<static_cast<char>(_type)<<'\n';
        }

        template<typename T, typename... Args>
        void writeHeader(T first,Args... args)
        {
            static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");
            m_stream<<"Header "<<static_cast<char>(first)<<' ';
            // fold expression to expand pack
            (writeHeaderDetail(args), ...);
            m_stream<<'\n';
        }


    private :
        std::ofstream m_stream;
        FrameTimeType m_frameType=FrameTimeType::INT;
        std::variant<int,float,double> m_frameNumber;
    };
}


#endif