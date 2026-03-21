#include <gtest/gtest.h>
#include <algorithm>
#include "Lexer.h"
#include "test_config.h"

class LexerFixture : public ::testing::Test {
protected:
    LexicalAnalyzer* lexer;
    void SetUp() override { lexer = nullptr; }
    void TearDown() override { delete lexer; }
};

class ComplexCodeTest : public ::testing::TestWithParam<ComplexTestData> {};

TEST_P(ComplexCodeTest, ValidatesFullCodeBlocks) {
    ComplexTestData data = GetParam();
    LexicalAnalyzer lex(data.input);
    auto tokens = lex.tokenize();

    ASSERT_EQ(tokens.size(), data.expected.size()) << "Failed on: " << data.description;
    
    for (size_t i = 0; i < tokens.size(); ++i) {
        EXPECT_EQ(tokens[i].value, data.expected[i]) << "Mismatch at index " << i;
    }
}
INSTANTIATE_TEST_SUITE_P(JSBlocks, ComplexCodeTest, ::testing::ValuesIn(COMPLEX_SCENARIOS));

class KeywordParamTest : public ::testing::TestWithParam<std::string> {};

TEST_P(KeywordParamTest, ChecksIndividualKeywords) {
    LexicalAnalyzer lex(GetParam());
    auto tokens = lex.tokenize();
    ASSERT_FALSE(tokens.empty());
    EXPECT_EQ(tokens[0].type, TokenType::KEYWORD);
}
INSTANTIATE_TEST_SUITE_P(Keywords, KeywordParamTest, ::testing::ValuesIn(KEYWORDS_LIST));

TEST_F(LexerFixture, ThrowsOnUnterminatedString) {
    LexicalAnalyzer badLex("\"missing end quote");
    EXPECT_THROW(badLex.tokenize(), std::runtime_error);
}

TEST_F(LexerFixture, AdvancedAssertsDemo) {
    lexer = new LexicalAnalyzer("const x = 42;");
    auto tokens = lexer->tokenize();

    ASSERT_FALSE(tokens.empty());                      
    EXPECT_EQ(tokens.size(), 5);                       
    
    EXPECT_STREQ(tokens[0].value.c_str(), "const");    
    
    EXPECT_TRUE(tokens[3].type == TokenType::INTEGER_LITERAL); 
}

TEST_F(LexerFixture, PlatformSpecificSkip) {
    #ifdef _WIN32
        GTEST_SKIP() << "Skipping this test because it's only for non-Windows environments";
    #endif

    LexicalAnalyzer lex("var a = 1;");
    auto tokens = lex.tokenize();
    EXPECT_EQ(tokens[0].value, "var");
}