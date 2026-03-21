#ifndef TEST_CONFIG_H
#define TEST_CONFIG_H

#include <vector>
#include <string>
#include "Lexer.h"

struct ComplexTestData {
    std::string description;           
    std::string input;                 
    std::vector<std::string> expected; 
};

const std::vector<ComplexTestData> COMPLEX_SCENARIOS = {
    {
        "Variable and Math",
        "let x = 42; const y = 3.14; let res = x + y;",
        {"let", "x", "=", "42", ";", "const", "y", "=", "3.14", ";", "let", "res", "=", "x", "+", "y", ";"}
    },
    {
        "Function Declaration",
        "function sum(a, b) { return a + b; }",
        {"function", "sum", "(", "a", ",", "b", ")", "{", "return", "a", "+", "b", ";", "}"}
    },
    {
        "Error and Unknown",
        "let bad = @123;",
        {"let", "bad", "=", "@", "123", ";"}
    }
};

const std::vector<std::string> KEYWORDS_LIST = {"let", "const", "if", "for", "while", "class", "function", "return"};

#endif