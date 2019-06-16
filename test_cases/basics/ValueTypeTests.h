#ifndef JSONPARSER_VALUETYPETESTS_H
#define JSONPARSER_VALUETYPETESTS_H

#include <iostream>
#include "../BaseTest.h"

TEST_F(ValueTests, Constructors) // NOLINT(cert-err58-cpp)
{

    EXPECT_NO_THROW(auto val1 = JsonValue(););

    // Should throw exceptions
    try {
        auto val2 = JsonValue(ValueType::JSON_NULL);
        auto val3 = JsonValue(ValueType::JSON_BOOL);
        auto val4 = JsonValue(ValueType::JSON_NUM);
        auto val5 = JsonValue(ValueType::JSON_STRING);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Cannot create empty JSON Value", std::invalid_argument);

    // Should not throw exceptions
    EXPECT_NO_THROW(auto val6 = JsonValue(ValueType::JSON_OBJ););
    EXPECT_NO_THROW(auto val7 = JsonValue(ValueType::JSON_ARRAY););
}

TEST_F(ValueTests, BoolValueValid) // NOLINT(cert-err58-cpp)
{
    auto val1 = JsonValue(ValueType::JSON_BOOL, "true");
    ASSERT_TRUE(val1.isBool());
    EXPECT_TRUE(val1.getBoolValue());

    auto val2 = JsonValue(ValueType::JSON_BOOL, "1");
    ASSERT_TRUE(val2.isBool());
    EXPECT_TRUE(val2.getBoolValue());

    // Special numeric case
    auto val3 = JsonValue(ValueType::JSON_NUM, "1");
    ASSERT_TRUE(val3.isBool());
    EXPECT_TRUE(val3.getBoolValue());

    auto val4 = JsonValue(ValueType::JSON_BOOL, "false");
    ASSERT_TRUE(val4.isBool());
    EXPECT_FALSE(val4.getBoolValue());

    auto val5 = JsonValue(ValueType::JSON_BOOL, "0");
    ASSERT_TRUE(val5.isBool());
    EXPECT_FALSE(val5.getBoolValue());

    // Special numeric case
    auto val6 = JsonValue(ValueType::JSON_NUM, "0");
    ASSERT_TRUE(val6.isBool());
    EXPECT_FALSE(val6.getBoolValue());
}

TEST_F(ValueTests, BoolValueInvalid) // NOLINT(cert-err58-cpp)
{
    try {
        auto val1 = JsonValue();


        FAIL() << "Expected invalid_argument";
    }
    catch (...){}

}

#endif //JSONPARSER_VALUETYPETESTS_H
