#include <vector>
#include <string>
#include <string_view>
#include <iostream>
#include <sstream>

std::vector<std::string> split(std::string_view s,std::string_view delimiters=" ;,\t")
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s.data());
    while (std::getline(tokenStream, token))
    {
        size_t prev = 0, pos;
        while ((pos = token.find_first_of(delimiters, prev)) != std::string::npos)
        {
            if (pos > prev)
                tokens.push_back(token.substr(prev, pos-prev));
            prev = pos+1;
        }
        if (prev < token.length())
            tokens.push_back(token.substr(prev, std::string::npos));
    }
    return tokens;
}

int main()
{
    for (auto s : split("1.2,2.3,3.4,4"))
        std::cout << s << '\n';

    for (auto s : split("Frame 1"))
        std::cout << s << '\n';


}