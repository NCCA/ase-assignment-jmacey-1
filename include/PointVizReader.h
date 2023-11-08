#ifndef POINTVIZREADER_H_
#define POINTVIZREADER_H_
#include <string_view>
#include <string>
#include <vector>
#include <fstream>
#include <memory>
#include "PointVizDataModel.h"
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
        void parseFormattedLine(const std::vector<std::string> &_s);
        std::vector<std::variant<int,float,double>> parseFloatLine(const std::vector<std::string> &_s);
    };
}



#endif
