#include <iostream>

enum class HeaderType : char {Float='F',Char='C',Int='I',Double='D'};

template<typename T>
void writeHeaderDetail(T _type)
{
    static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");

    std::cout<<static_cast<char>(_type)<<' ';
}



template<typename T>
void writeHeader( T _type)
{
    static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");
    std::cout<<"Header "<<static_cast<char>(_type)<<'\n';
}

template<typename T, typename... Args>
void writeHeader(T first,Args... args)
{
    static_assert(std::is_same<T, HeaderType>::value, "Type must be HeaderType");
    std::cout<<"Header "<<static_cast<char>(first)<<' ';
    // fold expression to expand pack
    (writeHeaderDetail(args), ...);
    std::cout<<'\n';
}

int main()
{
    writeHeader(HeaderType::Float);
    writeHeader(HeaderType::Int);
    writeHeader(HeaderType::Double);
    writeHeader(HeaderType::Char);
    writeHeader(HeaderType::Float,HeaderType::Char,HeaderType::Int,HeaderType::Double);
    writeHeader(HeaderType::Float,HeaderType::Float,HeaderType::Float,HeaderType::Float);
//    writeHeader(1);
    return EXIT_SUCCESS;
}