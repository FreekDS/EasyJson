#ifndef JSONPARSER_BASETEST_H
#define JSONPARSER_BASETEST_H

#include <gtest/gtest.h>
#include "../jsonParser.h"

#define MY_CATCH(expected, exceptionType) \
catch(std::invalid_argument& e) { \
    EXPECT_STREQ(e.what(), expected); \
}catch(...){ \
    FAIL() << "Expected" << #exceptionType; \
}

struct ParserTests : public ::testing::Test {
    JsonParser* parser;
    ParserTests() : parser(new JsonParser) {}
    ~ParserTests() override {
        delete parser;
        parser = nullptr;
    }
};

struct ValueTests : public ::testing::Test{};

#endif //JSONPARSER_BASETEST_H
