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
    MY_CATCH("Cannot create empty JSON Value", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Cannot create empty JSON Value", std::invalid_argument)

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
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "-1");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "3");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "-1");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY, "array");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "string");
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_OBJ);
        val.getBoolValue();
        FAIL() << "Expected invalid argument error";
    }
    MY_CATCH("Unexpected value for JsonBool", std::invalid_argument)
}

///////////////////////////////////////////////////////////////////////////////////////////////

//String Value/////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, StringValueValid)  // NOLINT(cert-err58-cpp)
{
    auto val1 = JsonValue(ValueType::JSON_STRING, "varkentje");
    ASSERT_FALSE(val1.getStringValue().empty());
    EXPECT_STREQ(val1.getStringValue().c_str(), "varkentje");
    auto val2 = JsonValue(ValueType::JSON_STRING, "");
    EXPECT_TRUE(val2.getStringValue().empty());
    auto val3 = JsonValue(ValueType::JSON_STRING);
    EXPECT_TRUE(val2.getStringValue().empty());
}

TEST_F(ValueTests, StringValueInvalid)  // NOLINT(cert-err58-cpp)
{
    try {
        auto val = JsonValue(ValueType::JSON_OBJ, "");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_OBJ);
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "-1");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NULL);
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NULL, "-1");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "1");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY, "");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "true");
        val.getStringValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonString", std::invalid_argument)

}

///////////////////////////////////////////////////////////////////////////////////////////////

//Number Value////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, NumberValueValid)  // NOLINT(cert-err58-cpp)
{
    auto val1 = JsonValue(ValueType::JSON_NUM, "1");
    EXPECT_EQ(val1.getNumberValue(), 1);
    auto val2 = JsonValue(ValueType::JSON_NUM, "1.0");
    EXPECT_EQ(val2.getNumberValue(), 1.0);
    auto val3 = JsonValue(ValueType::JSON_NUM, "2.578");
    EXPECT_EQ(val3.getNumberValue(), 2.578);
    auto val4 = JsonValue(ValueType::JSON_NUM, "-5");
    EXPECT_EQ(val4.getNumberValue(), -5);
    auto val5 = JsonValue(ValueType::JSON_NUM, "-3.201");
    EXPECT_EQ(val5.getNumberValue(), -3.201);
}

TEST_F(ValueTests, NumberValueInvalid)  // NOLINT(cert-err58-cpp)
{
    try {
        auto val = JsonValue(ValueType::JSON_NUM, "");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument (stod)";
    }
    MY_CATCH("stod", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NUM, "flapdrol");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument (stod)";
    }
    MY_CATCH("stod", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "1");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_BOOL, "false");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_STRING, "test");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_STRING);
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY, "array");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_OBJ, "obj");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_OBJ);
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument)

    try {
        auto val = JsonValue(ValueType::JSON_NULL);
        val.getNumberValue();
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Invalid type for: JsonNumber", std::invalid_argument); // NOLINT
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Array Value//////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, ArrayValidAccessMethods) // NOLINT(cert-err58-cpp)
{
    auto val = JsonValue(ValueType::JSON_ARRAY);
    val.addToArray(new JsonValue(ValueType::JSON_BOOL, "true"));
    ASSERT_EQ(val.getArrayValue().size(), 1);
    EXPECT_TRUE(val.getArrayValue().front()->getBoolValue());
    val.addToArray(new JsonValue(ValueType::JSON_BOOL, "false"));
    ASSERT_EQ(val.getArrayValue().size(), 2);
    EXPECT_FALSE(val.getArrayValue().back()->getBoolValue());
    val.addToArray(new JsonValue(ValueType::JSON_NUM, "2"));
    ASSERT_EQ(val.getArrayValue().size(), 3);
    EXPECT_TRUE(val[0].getBoolValue());
    EXPECT_FALSE(val[1].getBoolValue());
    EXPECT_EQ(val[2].getNumberValue(), 2);
}

TEST_F(ValueTests, ArrayInvalidAccessMethods) // NOLINT(cert-err58-cpp)
{

    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum.addToArray(nullptr);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum.addToArray(new JsonValue);
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum[1];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try {
        auto val = JsonValue(JSON_ARRAY);
        val[0];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Index out of range, got [0], but JsonArray is empty", std::invalid_argument)

    try {
        auto val = JsonValue(JSON_ARRAY);
        val[-1];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Index out of range, got [-1], but JsonArray is empty", std::invalid_argument)

    try {
        auto val = JsonValue(JSON_ARRAY);
        val[1];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Index out of range, got [1], but JsonArray is empty", std::invalid_argument)

    try {
        auto val = JsonValue(JSON_ARRAY);
        val.addToArray(new JsonValue);
        val.addToArray(new JsonValue);
        val.addToArray(new JsonValue);
        val[30];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Index out of range, got [30], max is [2]", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL);
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING);
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_OBJ);
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_OBJ, "object");
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NUM, "3");
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_BOOL, "true");
        val[0];
    }
    MY_CATCH("Object is not of type JsonArray", std::invalid_argument)
}

TEST_F(ValueTests, ArrayValueInvalid)  // NOLINT(cert-err58-cpp)
{
    try{
        auto val = JsonValue(ValueType::JSON_NULL);
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING);
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_OBJ);
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_OBJ, "object");
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NUM, "1");
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_BOOL, "true");
        val.getArrayValue();
    }
    MY_CATCH("Invalid type for: JsonArray", std::invalid_argument)
}

///////////////////////////////////////////////////////////////////////////////////////////////

//Object Value/////////////////////////////////////////////////////////////////////////////////

TEST_F(ValueTests, ObjectValidAccessMethods)  // NOLINT(cert-err58-cpp)
{
    auto val = JsonValue(ValueType::JSON_OBJ);
    val.addToObject(new JsonValue(ValueType::JSON_BOOL, "true"), "key1");
    ASSERT_EQ(val.getObjectValue().size(), 1);
    EXPECT_TRUE(val.getObjectValue().at("key1")->getBoolValue());
    val.addToObject(new JsonValue(ValueType::JSON_BOOL, "false"), "key2");
    ASSERT_EQ(val.getObjectValue().size(), 2);
    EXPECT_FALSE(val.getObjectValue().at("key2")->getBoolValue());
    val.addToObject(new JsonValue(ValueType::JSON_NUM, "-6"), "key3");
    ASSERT_EQ(val.getObjectValue().size(), 3);
    EXPECT_EQ(val.getObjectValue().at("key3")->getNumberValue(), -6);

    EXPECT_TRUE(val["key1"].getBoolValue());
    EXPECT_FALSE(val["key2"].getBoolValue());
    EXPECT_EQ(val["key3"].getNumberValue(), -6);
}

TEST_F(ValueTests, ObjectInvalidAcessMethods) // NOLINT(cert-err58-cpp)
{
    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum.addToObject(nullptr, "key");
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum.addToObject(new JsonValue, "key");
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try {
        auto jsonNum = JsonValue(JSON_NUM, "3");
        jsonNum["key"];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(JSON_OBJ);
        val["key"];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Did not find key 'key' in JsonObject", std::invalid_argument)
    
    try{
        auto val = JsonValue(JSON_OBJ);
        val.addToObject(new JsonValue, "key1");
        val.addToObject(new JsonValue, "key7");
        val.addToObject(new JsonValue, "sheep");
        val["key"];
        FAIL() << "Expected std::invalid_argument";
    }
    MY_CATCH("Did not find key 'key' in JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL);
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING);
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_ARRAY, "array");
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NUM, "3");
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_BOOL, "true");
        val["key"];
    }
    MY_CATCH("Object is not of type JsonObject", std::invalid_argument)
}

TEST_F(ValueTests, ObjectValueInvalid)  // NOLINT(cert-err58-cpp)
{
    try{
        auto val = JsonValue(ValueType::JSON_NULL);
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NULL, "null");
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING);
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_STRING, "string");
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_ARRAY);
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_ARRAY, "array");
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_NUM, "1");
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)

    try{
        auto val = JsonValue(ValueType::JSON_BOOL, "true");
        val.getObjectValue();
    }
    MY_CATCH("Invalid type for: JsonObject", std::invalid_argument)
}

///////////////////////////////////////////////////////////////////////////////////////////////


#endif //JSONPARSER_VALUETYPETESTS_H
