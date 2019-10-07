#ifndef JSONPARSER_SIMPLEARRAY_H
#define JSONPARSER_SIMPLE_H

#include "../BaseTest.h"
#define NULL_PATH TEST_PATH "null/"

TEST_F(ParserTests, SimpleNull) // NOLINT
{
    std::string file = NULL_PATH "null1.json";
    JsonParser& json = *parser;
    json.parse(file);
    EXPECT_TRUE(json["null"].isNull());
    EXPECT_EQ(json["null"].getNullValue(), nullptr);
}

#endif //JSONPARSER_SIMPLEARRAY_H
