#ifndef JSONPARSER_COMPLEXEXAMPLES_H
#define JSONPARSER_COMPLEXEXAMPLES_H

#define COMPL_PATH TEST_PATH "complex/"

TEST_F(ParserTests, AnimationExample) // NOLINT
{
    std::string file = COMPL_PATH "animation.json";
    JsonParser& json = *parser;
    json.parse(file);

    EXPECT_STREQ(json["file"].getStringValue().c_str(), "animation.png");
    ASSERT_EQ(json["tile_size"].getObjectValue()->size(), 2);
    EXPECT_EQ(json["tile_size"]["width"].getNumberValue(), 32);
    EXPECT_EQ(json["tile_size"]["height"].getNumberValue(), 32);
    EXPECT_TRUE(json["border"].isNumber());
    EXPECT_EQ(json["border"].getNumberValue(), 1);
    EXPECT_STREQ(json["type"].getStringValue().c_str(), "animation");
    ASSERT_TRUE(json["animations"].isArray());
    ASSERT_EQ(json["animations"].getArrayValue()->size(), 2);

    // TODO Change pointer to reference
    JsonArray& array = *json["animations"].getArrayValue();
    {
        JsonObject& obj = *array[0]->getObjectValue();

        EXPECT_STREQ(obj["name"]->getStringValue().c_str(), "walk_right");
        EXPECT_TRUE(obj["loop"]->getBoolValue());
        EXPECT_FALSE(obj["pingpong"]->getBoolValue());
        EXPECT_EQ(obj["frametime"]->getNumberValue(), 0.2);
    }
    {
        JsonObject& obj = *array[1]->getObjectValue();
        EXPECT_STREQ(obj["name"]->getStringValue().c_str(), "idle_front");
        EXPECT_TRUE(obj["loop"]->getBoolValue());
        EXPECT_FALSE(obj["pingpong"]->getBoolValue());
        EXPECT_EQ(obj["frametime"]->getNumberValue(), 0.8);
    }
}

#endif //JSONPARSER_COMPLEXEXAMPLES_H
