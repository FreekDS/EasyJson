#ifndef JSONPARSER_SIMPLEARRAY_H
#define JSONPARSER_SIMPLEARRAY_H

#include "../BaseTest.h"
#define ARRAY_PATH TEST_PATH "array/"

TEST_F(ParserTests, SimpleArray) // NOLINT
{
    std::string file = ARRAY_PATH "array.json";
    JsonParser& json = *parser;
    json.parse(file);
    JsonArray array = json["array2"].getArrayValue();
    JsonArray array2 = json["array"].getArrayValue();
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array2.size(), 2);
    EXPECT_TRUE(array2[0]->isArray());
    EXPECT_EQ(array2[0]->getArrayValue()[0]->getNumberValue(), 1);
    EXPECT_TRUE(array2[0]->getArrayValue()[1]->isNull());
    EXPECT_TRUE(array[0]->getBoolValue());
}

#endif //JSONPARSER_SIMPLEARRAY_H
