#ifndef POINTVIZREADER_H_
#define POINTVIZREADER_H_
#include <string_view>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "PointVizDataModel.h"
#include "PointVizTypes.h"
namespace pv
{
    class PointVizReader
    {
    public :
        PointVizReader(std::string_view filename);
        ~PointVizReader();
        bool isOpen() const;
        bool parse();
        void print() const;
    private :
        std::ifstream m_stream;
        std::vector<std::unique_ptr<pv::Frame>> m_dataModel;
        bool m_hasFormat = false;
        std::vector<std::variant<int,float,double>> parseFormattedLine(const std::vector<std::string> &_s);
        std::vector<std::variant<int,float,double>> parseFloatLine(const std::vector<std::string> &_s);
        void parseHeader(const std::vector<std::string> &_s);
        std::vector<HeaderType> m_header;
    };
}



#endif
