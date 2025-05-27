//与えられた文字列（数字や文字）を、異なるスカラー型（char, int, float, double）に変換して表示
#include "ScalarConverter.hpp"

ScalarConverter::ScalarConverter() {}

ScalarConverter::ScalarConverter(const ScalarConverter& other) {
    (void)other; 
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other) {
    (void)other;
    return *this;
}

void ScalarConverter::convert(const std::string& literal) 
{
    char c_val;
    int i_val;
    float f_val;
    double d_val;

    bool possible_to_char = true;
    bool possible_to_int = true;
    bool possible_to_float = true;
    bool possible_to_double = true;

    // 擬似リテラル
    if (literal == "nan" || literal == "nanf") {
        d_val = std::numeric_limits<double>::quiet_NaN();
        f_val = std::numeric_limits<float>::quiet_NaN();
        // nanはcharやintには変換できないので不可能フラグを立てる
        possible_to_char = false;
        possible_to_int = false;
        // floatのnanf、doubleのnanは可能とする
    } else if (literal == "+inf" || literal == "+inff") {
        d_val = std::numeric_limits<double>::infinity();
        f_val = std::numeric_limits<float>::infinity();
        possible_to_char = false;
        possible_to_int = false;
    } else if (literal == "-inf" || literal == "-inff") {
        d_val = -std::numeric_limits<double>::infinity();
        f_val = -std::numeric_limits<float>::infinity();
        possible_to_char = false;
        possible_to_int = false;
    }
    // charリテラルをチェック
    else if (literal.length() == 3 && literal[0] == '\'' && literal[2] == '\'') {
        c_val = literal[1]; // シングルクォートの中の文字を取得
        i_val = static_cast<int>(c_val);
        f_val = static_cast<float>(c_val);
        d_val = static_cast<double>(c_val);
    }
    // 数値リテラルをチェック（int, float, double）
    else {
        char* end_ptr;
        errno = 0;
        d_val = std::strtod(literal.c_str(), &end_ptr);

        if (*end_ptr == '\0' || (*end_ptr == 'f' && *(end_ptr + 1) == '\0')) {
            // 文字列全体が数値として解釈できた場合、または 'f' で終わる場合
            if (errno == ERANGE) {
                possible_to_char = false;
                possible_to_int = false;
                possible_to_float = false;
                possible_to_double = false;
                std::cerr << RED << "Error: Value out of range for double." << RESET << std::endl;
            } else {
                if (*end_ptr == 'f' || *end_ptr == 'F') { // float リテラルの場合 (末尾に 'f' がある)
                    f_val = static_cast<float>(d_val);
                    if (f_val != d_val && !std::isinf(d_val) && !std::isnan(d_val)) {
                         possible_to_float = false;
                    }
                } else { // double リテラル、または int リテラル（小数点なし）の場合
                    f_val = static_cast<float>(d_val);
                }

                // int への変換
                if (d_val >= std::numeric_limits<int>::min() && d_val <= std::numeric_limits<int>::max()) {
                    i_val = static_cast<int>(d_val);
                } else {
                    possible_to_int = false;
                }

                // char への変換
                if (d_val >= std::numeric_limits<char>::min() && d_val <= std::numeric_limits<char>::max() && possible_to_int) {
                    c_val = static_cast<char>(d_val);
                } else {
                    possible_to_char = false;
                }
            }
        } else {
            possible_to_char = false;
            possible_to_int = false;
            possible_to_float = false;
            possible_to_double = false;
            std::cerr << RED "Error: Invalid literal format." RESET << std::endl;
        }
    }

    std::cout << "char: ";
    if (!possible_to_char) {
        std::cout << "impossible" << std::endl;
    } else if (c_val < 32 || c_val > 126) {
        std::cout << "Non displayable" << std::endl;
    } else {
        std::cout << "'" << c_val << "'" << std::endl;
    }

    std::cout << "int: ";
    if (!possible_to_int) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << i_val << std::endl;
    }

    std::cout << "float: ";
    if (!possible_to_float) {
        std::cout << "impossible" << std::endl;
    } else {
        // 小数点以下の桁数を固定して表示する設定
        std::cout << std::fixed << std::setprecision(1) << f_val << "f" << std::endl;
    }

    std::cout << "double: ";
    if (!possible_to_double) {
        std::cout << "impossible" << std::endl;
    } else {
        std::cout << std::fixed << std::setprecision(1) << d_val << std::endl;
    }
}