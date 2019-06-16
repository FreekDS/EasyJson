#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include <string>
#include <map>
#include <vector>
#include <stack>

class JsonValue;

using JsonObject = std::map<std::string, JsonValue*>;
using JsonArray = std::vector<JsonValue*>;

enum ValueType {
    JSON_NULL,
    JSON_NUM,
    JSON_ARRAY,
    JSON_OBJ,
    JSON_STRING,
    JSON_BOOL
};

class JsonValue {
private:
    ValueType type;

    bool copied;

    union {
        bool bool_value;
        double number_value;
        std::string* string_value;
        JsonObject* object_value;
        JsonArray* array_value;
    };

public:

    JsonValue(const JsonValue& other);
    JsonValue& operator=(const JsonValue& other);

    void clear();
    JsonValue();
    explicit JsonValue(const ValueType&);
    JsonValue(const ValueType&, const std::string&);
    ~JsonValue();
    bool isBool() const;
    bool isNull() const;
    bool isString() const;
    bool isArray() const;
    bool isObject() const;
    bool isNumber() const;

    bool getBoolValue() const;

    double getNumberValue() const;

    std::string getStringValue() const;

    JsonArray* getArrayValue() const;

    JsonObject* getObjectValue() const;

    void addToArray(JsonValue*);

    void addToObject(JsonValue*, const std::string&);

    JsonValue& operator[](int);

    JsonValue& operator[](const std::string&);
};

class ParseError : public std::exception {
private:
    std::string message;
public:

    ParseError(int line, const std::string& content, const std::string& message) : ParseError(line, message)
    {
        if(content.empty())
            return;
        this->message = "Error at line "+std::to_string(line)+":\n|\n"+content+"\n"+message;
    }

    ParseError(int line, const std::string& message){
        this->message = "Error at line "+std::to_string(line)+ ": " + message;
    }

    const char* what() const noexcept override;
};

class JsonParser {
private:

    enum PARSE_STATE{
        NORMAL,
        ARRAY,
        OBJECT
    };

    std::stack<PARSE_STATE> parseState;

    std::stack<std::pair<std::string, JsonValue*>> unfinishedObjects;
    std::stack<std::pair<std::string, JsonValue*>> unfinishedArrays;

    JsonObject root;
    int m_curlyCount;
    int m_straightCount;
    int currentLine;
    bool canCreateValue;
    static void skipWhiteSpace(std::string& line);
    static std::string getQuotedString(std::string& line, char quoteChar);
    static bool expectChar(std::string& line, char c);
    void removeAllWhiteSpaces(std::string& line);
    bool expectBoolVal(std::string& line);
    std::string readNumberValue(std::string& line);
    void clear();

public:
    JsonParser();

    ~JsonParser();

    void parse(const std::string&);

    JsonValue& operator[](const std::string& key);
};

#endif //JSONPARSER_JSONPARSER_H
