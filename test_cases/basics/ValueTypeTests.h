#ifndef JSONPARSER_VALUETYPETESTS_H
#define JSONPARSER_VALUETYPETESTS_H

#include <iostream>
#include "../BaseTest.h"

//Constructors/////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, Constructors) // NOLINT(cert-err58-cpp)
{
    // Should throw exceptions
    try {
        auto val = JsonValue(ValueType::JSON_BOOL);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Cannot create empty JSON Value", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_NUM);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Cannot create empty JSON Value", std::invalid_argument);

    // Should not throw exceptions
    EXPECT_NO_THROW(auto val = JsonValue(););
    EXPECT_NO_THROW(auto val = JsonValue(ValueType::JSON_NULL););
    EXPECT_NO_THROW(auto val = JsonValue(ValueType::JSON_STRING););
    EXPECT_NO_THROW(auto val = JsonValue(ValueType::JSON_OBJ););
    EXPECT_NO_THROW(auto val = JsonValue(ValueType::JSON_ARRAY););
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Boolean Value////////////////////////////////////////////////////////////////////////////////

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
        auto val = JsonValue(ValueType::JSON_BOOL, "3");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "-1");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "3");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "-1");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY, "array");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "string");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);

    try {
        auto val = JsonValue(ValueType::JSON_OBJ);
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument);
}

///////////////////////////////////////////////////////////////////////////////////////////////

//String Value/////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, StringValueValid)  // NOLINT(cert-err58-cpp)
{

}

TEST_F(ValueTests, StringValueInvalid)  // NOLINT(cert-err58-cpp)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////

//Number Value////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, NumberValueValid)  // NOLINT(cert-err58-cpp)
{

}

TEST_F(ValueTests, NumberValueInvalid)  // NOLINT(cert-err58-cpp)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////

//Array Value//////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, ArrayValueValid)  // NOLINT(cert-err58-cpp)
{

}

TEST_F(ValueTests, ArrayValueInvalid)  // NOLINT(cert-err58-cpp)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////

//Object Value/////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, ObjectValueValid)  // NOLINT(cert-err58-cpp)
{

}

TEST_F(ValueTests, ObjectValueInvalid)  // NOLINT(cert-err58-cpp)
{

}

///////////////////////////////////////////////////////////////////////////////////////////////


#endif //JSONPARSER_VALUETYPETESTS_H
