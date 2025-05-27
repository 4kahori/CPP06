#include "ScalarConverter.hpp"
#include <iostream>

int main(int argc, char* argv[])
{

    if (argc != 2) {
        std::cout << "Usage: ./convert <literal>" << std::endl; // 正しい使い方を提示
        return 1;
    }

    ScalarConverter::convert(argv[1]);

    return 0;
}
