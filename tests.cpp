#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <algorithm>
#include "Lexer.h"
#include "test_config.h"

class LexerFixture : public ::testing::Test {
protected:
    LexicalAnalyzer* lexer;
    void SetUp() override { lexer = nullptr; }
    void TearDown() override { delete lexer; }
};

class KeywordParamTest : public ::testing::TestWithParam<std::string> {};
TEST_P(KeywordParamTest, ChecksKeywords) {
    LexicalAnalyzer lex(GetParam());
    auto tokens = lex.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::KEYWORD);
}
INSTANTIATE_TEST_SUITE_P(JSKeywords, KeywordParamTest, ::testing::ValuesIn(KEYWORDS_TO_TEST));

class LiteralParamTest : public ::testing::TestWithParam<TokenTestData> {};
TEST_P(LiteralParamTest, ChecksDifferentTypes) {
    TokenTestData data = GetParam();
    LexicalAnalyzer lex(data.input);
    auto tokens = lex.tokenize();
    ASSERT_FALSE(tokens.empty());
    EXPECT_EQ(tokens[0].type, data.expectedType);
    EXPECT_EQ(tokens[0].value, data.expectedValue);
}
INSTANTIATE_TEST_SUITE_P(Literals, LiteralParamTest, ::testing::ValuesIn(LITERAL_TEST_DATA));

TEST_F(LexerFixture, AdvancedAndExceptionTests) {
    lexer = new LexicalAnalyzer("const x = 42;");
    auto tokens = lexer->tokenize();

    std::vector<std::string> expected = {"const", "x", "=", "42", ";"};
    std::vector<std::string> actual;
    for(const auto& t : tokens) actual.push_back(t.value);

    ASSERT_EQ(actual.size(), expected.size());
    EXPECT_TRUE(std::equal(actual.begin(), actual.end(), expected.begin()));

    EXPECT_STREQ(tokens[0].value.c_str(), "const");

    EXPECT_EQ(tokens[3].type, TokenType::INTEGER_LITERAL);
    
    ASSERT_FALSE(tokens.empty());
}

TEST_F(LexerFixture, ThrowsOnUnterminatedString) {
    LexicalAnalyzer badLexer("\"error");
    EXPECT_THROW(badLexer.tokenize(), std::runtime_error);
}

TEST_F(LexerFixture, SkipTest) {
    #ifdef _WIN32
        GTEST_SKIP() << "Skipping: this specific test is only for Linux environment";
    #endif

    LexicalAnalyzer l("var a;");
    auto tokens = l.tokenize();
    ASSERT_FALSE(tokens.empty());
    EXPECT_EQ(tokens[0].value, "var");
}

TEST_F(LexerFixture, CoversUnknown) {
    LexicalAnalyzer l("@");
    auto tokens = l.tokenize();
    ASSERT_EQ(tokens.size(), 1);
    EXPECT_EQ(tokens[0].type, TokenType::UNKNOWN);
}