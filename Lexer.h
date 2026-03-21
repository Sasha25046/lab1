#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cctype>
#include <stdexcept>

enum class TokenType {
    KEYWORD, IDENTIFIER, INTEGER_LITERAL, FLOAT_LITERAL,
    HEX_LITERAL, CHAR_LITERAL, STRING_LITERAL, TEMPLATE_LITERAL,
    COMMENT, OPERATOR, PUNCTUATOR, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    Token(TokenType t, const std::string& v) : type(t), value(v) {}
};

class LexicalAnalyzer {
private:
    std::string input;
    size_t position;
    std::unordered_map<std::string, TokenType> keywords;

    void initKeywords() {
        std::string words[] = {"var","let","const","function","return","if","else","for","while","class","new","this","true","false","null","undefined","import","export"};
        for (auto& w : words) keywords[w] = TokenType::KEYWORD;
    }

    bool isAlpha(char c) { return isalpha(c) || c == '_' || c == '$'; }
    bool isDigit(char c) { return isdigit(c); }

public:
    LexicalAnalyzer(const std::string& source) : input(source), position(0) { initKeywords(); }

    std::vector<Token> tokenize() {
        std::vector<Token> tokens;
        while (position < input.size()) {
            char c = input[position];
            if (isspace(c)) { position++; continue; }

            if (c == '"' || c == '\'' || c == '`') {
                size_t start = position++;
                while (position < input.size() && input[position] != c) position++;
                
                if (position >= input.size()) {
                    throw std::runtime_error("Unterminated string literal");
                }
                position++;
                tokens.emplace_back(TokenType::STRING_LITERAL, input.substr(start, position - start));
                continue;
            }

            if (isAlpha(c)) {
                size_t start = position;
                while (position < input.size() && (isalnum(input[position]) || input[position] == '_' || input[position] == '$')) position++;
                std::string word = input.substr(start, position - start);
                if (keywords.count(word)) tokens.emplace_back(TokenType::KEYWORD, word);
                else tokens.emplace_back(TokenType::IDENTIFIER, word);
                continue;
            }
            if (isdigit(c)) {
                size_t start = position;
                bool hasDot = false;
                while (position < input.size()) {
                    char current = input[position];
                    if (isdigit(current)) {
                        position++;
                    } 
                    else if (current == '.' && !hasDot) {
                        if (position + 1 < input.size() && isdigit(input[position + 1])) {
                            hasDot = true;
                            position++;
                        } else {
                            break;
                        }
                    } 
                    else {
                        break;
                    }
                }
                std::string value = input.substr(start, position - start);
                if (hasDot) {
                    tokens.emplace_back(TokenType::FLOAT_LITERAL, value);
                } else {
                    tokens.emplace_back(TokenType::INTEGER_LITERAL, value);
                }
                continue;
            }

            std::string punct = "();,.{}[]=";
            if (punct.find(c) != std::string::npos) {
                tokens.emplace_back(TokenType::PUNCTUATOR, std::string(1, c));
                position++;
                continue;
            }

            tokens.emplace_back(TokenType::UNKNOWN, std::string(1, c));
            position++;
        }
        return tokens;
    }
};

#endif