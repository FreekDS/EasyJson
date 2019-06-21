#ifndef JSONPARSER_ONEVAR_H
#define JSONPARSER_ONEVAR_H

#include "../BaseTest.h"

#define STR_PATH TEST_PATH "string/"

TEST_F(ParserTests, SingleString) // NOLINT
{
    std::string file = STR_PATH "string1.json";
    JsonParser& json = *parser;
    json.parse(file);
    EXPECT_STREQ(json["string"].getStringValue().c_str(), "test");
}

TEST_F(ParserTests, MultipleStrings) // NOLINT
{
    std::string file = STR_PATH "string2.json";
    JsonParser& json = *parser;
    json.parse(file);
    EXPECT_STREQ(json["sheep"].getStringValue().c_str(), "beeeiii");
    EXPECT_STREQ(json["pig"].getStringValue().c_str(), "oink");
    EXPECT_STREQ(json["cat"].getStringValue().c_str(), "meow");
}

TEST_F(ParserTests, InvalidComma) // NOLINT
{
    std::string file = STR_PATH "string3.json";
    try {
        parser->parse(file);
        FAIL() << "Expected ParseError";
    }
    MY_CATCH("Error at line 3: Expected new object after ','", ParseError)
}

TEST_F(ParserTests, ValidComma) // NOLINT
{
    std::string file = STR_PATH "string4.json";
    JsonParser& json = *parser;
    ASSERT_NO_THROW(json.parse(file));
    EXPECT_STREQ(json["pig"].getStringValue().c_str(), "oink");
    EXPECT_STREQ(json["sheep"].getStringValue().c_str(), "bei");
}

TEST_F(ParserTests, NoQuotes) // NOLINT
{
    std::string file = STR_PATH "string5.json";
    JsonParser& json = *parser;
    try{
        parser->parse(file);
        FAIL() << "Expected ParseError";
    }
    MY_CATCH("Error at line 2:\n|\nmiauw\nUnexpected token: 'm'", ParseError)
}

TEST_F(ParserTests, SingleQuoted) // NOLINT
{
    std::string file = STR_PATH "string6.json";
    JsonParser& json = *parser;
    json.parse(file);
    EXPECT_STREQ(json["string"].getStringValue().c_str(), "test");
}


#endif //JSONPARSER_ONEVAR_H
