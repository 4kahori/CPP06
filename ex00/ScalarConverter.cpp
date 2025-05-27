//与えられた文字列（数字や文字）を、異なるスカラー型（char, int, float, double）に変換して表示

// ScalarConverter.cpp
#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <iomanip>


ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other; 
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}


void ScalarConverter::convert(const std::string& literal) {
    std::cout << "DEBUG: convert function called with literal: " << literal << std::endl;

}