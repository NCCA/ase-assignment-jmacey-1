#include "PointVizReader.h"
#include <iostream>
#include <string_view>
#include <iostream>
#include <sstream>

namespace pv {
    // function from https://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
    std::istream &safeGetline(std::istream &is, std::string &t) {
        t.clear();
        // The characters in the stream are read one-by-one using a std::streambuf.
        // That is faster than reading them one-by-one using the std::istream.
        // Code that uses streambuf this way must be guarded by a sentry object.
        // The sentry object performs various tasks,
        // such as thread synchronization and updating the stream state.

        std::istream::sentry se(is, true);
        std::streambuf *sb = is.rdbuf();

        for (;;) {
            int c = sb->sbumpc();
            switch (c) {
                case '\n':
                    return is;
                case '\r':
                    if (sb->sgetc() == '\n')
                        sb->sbumpc();
                    return is;
                case std::streambuf::traits_type::eof():
                    // Also handle the case when the last line has no line ending
                    if (t.empty())
                        is.setstate(std::ios::eofbit);
                    return is;
                default:
                    t += static_cast< char >(c);
            }
        }
    }

    std::vector<std::string> split(std::string_view s, std::string_view delimiters = " ;,\t") {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s.data());
        while (std::getline(tokenStream, token)) {
            size_t prev = 0, pos;
            while ((pos = token.find_first_of(delimiters, prev)) != std::string::npos) {
                if (pos > prev)
                    tokens.push_back(token.substr(prev, pos - prev));
                prev = pos + 1;
            }
            if (prev < token.length())
                tokens.push_back(token.substr(prev, std::string::npos));
        }
        return tokens;
    }


    std::variant<int, float, double> getFrameTime(std::string_view _s) {
        std::variant<int, float, double> ret;
        if (_s.find('.') != std::string::npos) {
            ret = static_cast<float>(std::atof(_s.data()));
        } else {
            ret = static_cast<int>(std::atoi(_s.data()));
        }
        return ret;
    }

    PointVizReader::PointVizReader(std::string_view _filename) {
        m_stream.open(_filename);
    }

    PointVizReader::~PointVizReader() {
        m_stream.close();
    }

    bool PointVizReader::isOpen() const {
        return m_stream.is_open();
    }


    bool PointVizReader::parse() {
        std::string str;
        std::unique_ptr<pv::Frame> currentFrame;
        while (!safeGetline(m_stream, str).eof()) {
            bool status = true;
            // Line contains string of length > 0 then parse it
            if (!str.empty())
            {
                auto tokens = split(str);
                if (tokens[0] == "Frame")
                {
                    if (currentFrame != nullptr)
                    {
                        m_dataModel.emplace_back(std::move(currentFrame));
                    }
                    currentFrame = std::make_unique<pv::Frame>();
                    currentFrame->m_actualFrameTime = getFrameTime(tokens[1]);
                }

                else if (tokens[0] == "Header")
                {
                    // process header info
                    m_hasFormat = true;
                }
                else
                {
                    // all other data
                    if (m_hasFormat)
                    {
                        parseFormattedLine(tokens);
                    }
                    else
                    {
                        currentFrame->m_frameData.push_back(  parseFloatLine(tokens));
                    }
                }

            }
        }
        return true;
    }


    void PointVizReader::parseFormattedLine(const std::vector<std::string> &_s)
    {

    }

    std::vector<std::variant<int,float,double>> PointVizReader::parseFloatLine(const std::vector<std::string> &_s)
    {
        std::vector<std::variant<int,float,double>> entry(_s.size());
        std::transform(std::begin(_s),std::end(_s),std::begin(entry),
                       [](auto v)
                       {
                        return std::stof(v);
                       });

        return entry;
    }

    void PointVizReader::print() const
    {
        for(auto &f : m_dataModel)
        {
            std::cout<<"Frame ";
            std::visit([](auto&& arg) {
                std::cout << arg;
            }, f->m_actualFrameTime);
            std::cout<<'\n';
            std::cout<<"Data \n";
            for(auto &d : f->m_frameData)
            {
                for(auto v : d)
                {
                    std::visit([](auto&& arg) {
                        std::cout << arg<<' ';
                    }, v);
                }
                std::cout<<'\n';
            }
        }
    }

} // end namespace

