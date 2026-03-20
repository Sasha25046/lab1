#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <vector>
#include <string>
#include "Lexer.h"

const std::vector<std::string> KEYWORDS_TO_TEST = {
    "let", "const", "if", "return", "while", "class", "function"
};

struct TokenTestData {
    std::string input;
    TokenType expectedType;
    std::string expectedValue;
};

const std::vector<TokenTestData> LITERAL_TEST_DATA = {
    {"42", TokenType::INTEGER_LITERAL, "42"},
    {"myVar", TokenType::IDENTIFIER, "myVar"},
    {"{", TokenType::PUNCTUATOR, "{"}
};

#endif