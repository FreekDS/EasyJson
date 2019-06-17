#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <fstream>
#include "jsonParser.h"

bool JsonValue::isBool() const
{
    bool numeric_bool = false;
    if (type==ValueType::JSON_NUM) {
        if (number_value==0 || number_value==1)
            numeric_bool = true;
    }
    return type==ValueType::JSON_BOOL || numeric_bool;
}

bool JsonValue::isNull() const
{
    return type==ValueType::JSON_NULL;
}

bool JsonValue::isString() const
{
    return type==ValueType::JSON_STRING;
}

bool JsonValue::isArray() const
{
    return type==ValueType::JSON_ARRAY;
}

bool JsonValue::isObject() const
{
    return type==ValueType::JSON_OBJ;
}

bool JsonValue::isNumber() const
{
    return type==ValueType::JSON_NUM;
}

bool JsonValue::getBoolValue() const
{
    if (isNumber()) {
        if (number_value==0)
            return false;
        else if (number_value==1)
            return true;
        else
            throw std::invalid_argument("Unexpected value for JsonBool");
    }
    if(isBool())
        return bool_value;
    else
        throw std::invalid_argument("Unexpected value for JsonBool");
}

double JsonValue::getNumberValue() const
{
    if (!isNumber())
        throw std::invalid_argument("Invalid type for: number");
    return number_value;
}

std::string JsonValue::getStringValue() const
{
    if (!isString())
        throw std::invalid_argument("Invalid type for: string");
    return *string_value;
}

JsonArray* JsonValue::getArrayValue() const
{
    if (!isArray())
        throw std::invalid_argument("Invalid type for: JsonArray");
    return array_value;
}

JsonObject* JsonValue::getObjectValue() const
{
    if (!isObject())
        throw std::invalid_argument("Invalid type for: JsonObject");
    return object_value;
}

JsonValue::JsonValue()
        :type(ValueType::JSON_NULL), copied(false)
{

}

JsonValue::JsonValue(const ValueType& valueType, const std::string& value)
        :copied(false)
{

//    std::transform(value.begin(), value.end(), value.begin(), ::tolower);

    switch (valueType) {
    default:
        type = ValueType::JSON_NULL;
        break;
    case ValueType::JSON_STRING: {
        type = ValueType::JSON_STRING;
        string_value = new std::string(value);
        break;
    }
    case ValueType::JSON_BOOL: {
        type = ValueType::JSON_BOOL;
        if (strcmp(value.c_str(), "0")==0 || strcmp(value.c_str(), "false")==0)
            bool_value = false;
        else if (strcmp(value.c_str(), "1")==0 || strcmp(value.c_str(), "true")==0)
            bool_value = true;
        else
            type = ValueType::JSON_NULL;
        break;
    }
    case ValueType::JSON_NUM: {
        type = ValueType::JSON_NUM;
        number_value = std::stod(value);
        break;
    }
    case ValueType::JSON_ARRAY: {
        type = ValueType::JSON_ARRAY;
        array_value = new JsonArray;
        break;
    }
    case ValueType::JSON_OBJ: {
        type = ValueType::JSON_OBJ;
        object_value = new JsonObject;
        break;
    }
    }
}

JsonValue::~JsonValue()
{
    if (copied)
        return;
    switch (type) {
    default:
        break;
    case ValueType::JSON_OBJ:
        for (auto it = object_value->begin(); it!=object_value->end();) {
            delete it->second;
            it->second = nullptr;
            it = object_value->erase(it);
        }
        delete object_value;
        object_value = nullptr;
        break;
    case ValueType::JSON_ARRAY:
        if (array_value==nullptr)
            break;
        for (auto* obj : (*array_value)) {
            delete obj;
            obj = nullptr;
        }
        array_value->clear();
        delete array_value;
        array_value = nullptr;
        break;
    case ValueType::JSON_STRING:
        delete string_value;
        string_value = nullptr;
        break;
    }
}

void JsonValue::addToArray(JsonValue* value)
{
    if (!isArray())
        throw std::invalid_argument("Object is not of type JsonArray");
    array_value->push_back(value);
}

void JsonValue::addToObject(JsonValue* value, const std::string& key)
{
    if (!isObject())
        throw std::invalid_argument("Object is not of type JsonObject");
    if (object_value->count(key)) {
        throw std::invalid_argument("Duplicate key: '"+key+"'");
    }
    (*object_value)[key] = value;
}

JsonValue& JsonValue::operator[](int index)
{
    if (type!=ValueType::JSON_ARRAY) {
        throw std::invalid_argument("Object is not of type JsonArray");
    }

    if (index>=array_value->size())
        throw std::invalid_argument(
                "Index out of range, got ["+std::to_string(index)+"], max is ["+std::to_string(array_value->size()-1)
                        +"]");

    return *((*array_value)[index]);
}

JsonValue& JsonValue::operator[](const std::string& key)
{
    if (type!=ValueType::JSON_OBJ)
        throw std::invalid_argument("Object is not of type JsonObject");

    if (object_value->count(key)==0)
        throw std::invalid_argument("Did not find key '"+key+"' in JsonObject");

    return *((*object_value)[key]);
}

JsonValue::JsonValue(const ValueType& vt)
{
    switch (vt) {
    case JSON_ARRAY:
        array_value = new std::vector<JsonValue*>{};
        type = vt;
        break;
    case JSON_OBJ:
        object_value = new JsonObject{};
        type = vt;
        break;
    case JSON_NULL:
        type = vt;
        break;
    case JSON_STRING:
        string_value = new std::string("");
        type = vt;
        break;
    default:
        throw std::invalid_argument("Cannot create empty JSON Value");
    }
}

JsonValue& JsonValue::operator=(const JsonValue& other)
{
    type = other.type;
    copied = true;
    switch (other.type) {
    case JSON_NULL:
        break;
    case JSON_NUM:
        number_value = other.number_value;
        break;
    case JSON_ARRAY:
        array_value = other.array_value;
        break;
    case JSON_OBJ:
        object_value = other.object_value;
        break;
    case JSON_STRING:
        string_value = other.string_value;
        break;
    case JSON_BOOL:
        bool_value = other.bool_value;
        break;
    }
    return *this;
}

JsonValue::JsonValue(const JsonValue& other)
{
    type = other.type;
    copied = true;
    switch (other.type) {
    case JSON_NULL:
        break;
    case JSON_NUM:
        number_value = other.number_value;
        break;
    case JSON_ARRAY:
        array_value = other.array_value;
        break;
    case JSON_OBJ:
        object_value = other.object_value;
        break;
    case JSON_STRING:
        string_value = other.string_value;
        break;
    case JSON_BOOL:
        bool_value = other.bool_value;
        break;
    }

}

void JsonParser::skipWhiteSpace(std::string& line)
{
    if (line.empty())
        return;
    while (line.front()==' ')
        line.erase(0, 1);
}

void JsonParser::parse(const std::string& file_name)
{

    clear();
    root = JsonObject{};

    std::ifstream file(file_name);
    if (!file.is_open())
        throw std::invalid_argument("File not found '"+file_name+'\'');

    std::string line;
    bool first = false;
    while (getline(file, line)) {

        if (line.empty())
            continue;

        currentLine++;
        skipWhiteSpace(line);
        while (!line.empty()) {
            skipWhiteSpace(line);
            char current = line.front();
            switch (current) {

            case '{':
                m_curlyCount++;
                if (!first) {
                    first = true;
                    break;
                }
                if (parseState.top()==ARRAY) {
                    if (!canCreateValue) {
                        throw ParseError(currentLine, line, "Missing ','");
                    }
                    unfinishedObjects.push({"", new JsonValue(ValueType::JSON_OBJ)});
                    parseState.push(OBJECT);
                    break;
                }
            case '}':
                m_curlyCount--;
                if (parseState.top()==OBJECT)
                    parseState.pop();

                if (parseState.top()==ARRAY) {
                    if (!unfinishedObjects.empty()) {
                        line.erase(0, 1);
                        auto top = unfinishedObjects.top();
                        unfinishedObjects.pop();
                        auto array = unfinishedArrays.top().second;
                        array->addToArray(top.second);
                        skipWhiteSpace(line);
                        canCreateValue = expectChar(line, ',');
                        continue;
                    }
                    break;
                }

                if (!unfinishedObjects.empty()) {
                    auto top = unfinishedObjects.top();
                    unfinishedObjects.pop();
                    if (unfinishedObjects.empty())
                        root[top.first] = top.second;
                    else {
                        auto attachTo = unfinishedObjects.top().second;
                        attachTo->addToObject(top.second, top.first);
                    }
                }
                break;
            case '[':
                // start new array
                m_straightCount++;
                if (parseState.top()==ARRAY) {
                    parseState.push(ARRAY);
                    unfinishedArrays.push({"", new JsonValue(ValueType::JSON_ARRAY)});
                    break;
                }
            case ']':
                // end array
                m_straightCount--;
                if (parseState.top()==ARRAY) {
                    line.erase(0, 1);
                    auto top = unfinishedArrays.top();
                    parseState.pop();
                    unfinishedArrays.pop();
                    if (unfinishedArrays.empty()) {
                        root[top.first] = top.second;
                    }
                    else {
                        auto addTo = unfinishedArrays.top().second;
                        addTo->addToArray(top.second);
                    }
                    canCreateValue = expectChar(line, ',');
                    continue;
                }
            case 't':
                if (parseState.top()==ARRAY) {
                    if (strcmp(line.substr(0, 4).c_str(), "true")==0) {
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_BOOL, "true");
                        auto addTo = unfinishedArrays.top().second;
                        addTo->addToArray(jsonVal);
                        // Remove 'true'
                        std::string s = "true";
                        std::string::size_type i = line.find(s);
                        if (i!=std::string::npos)
                            line.erase(i, s.length());
                        skipWhiteSpace(line);
                        canCreateValue = expectChar(line, ',');
                        continue;
                    }
                }
            case 'f':
                if (parseState.top()==ARRAY) {
                    if (strcmp(line.substr(0, 5).c_str(), "false")==0) {
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_BOOL, "false");
                        auto addTo = unfinishedArrays.top().second;
                        addTo->addToArray(jsonVal);
                        // Remove 'true'
                        std::string s = "false";
                        std::string::size_type i = line.find(s);
                        if (i!=std::string::npos)
                            line.erase(i, s.length());
                        skipWhiteSpace(line);
                        canCreateValue = expectChar(line, ',');
                        continue;
                    }
                }
            case '\'':
            case '"': {

                if (!canCreateValue) {
                    throw ParseError(currentLine, line, "Missing ',' after last created object");
                }

                std::string key = getQuotedString(line, current);
                skipWhiteSpace(line);

                if (parseState.top()==ARRAY) {
                    auto top = unfinishedArrays.top().second;
                    top->addToArray(new JsonValue(ValueType::JSON_STRING, key));
                    canCreateValue = expectChar(line, ',');
                    continue;
                }

                if (!expectChar(line, ':'))
                    throw ParseError(currentLine, line, "Missing ':' after \""+key+"\"");

                skipWhiteSpace(line);
                char new_current = line.front();

                // We need to read the value after the key
                switch (new_current) {
                case '"':
                case '\'': {
                    std::string value = getQuotedString(line, new_current);

                    JsonValue* jsonVal = new JsonValue(ValueType::JSON_STRING, value);

                    switch (parseState.top()) {
                    case ARRAY: {

                    }
                    case OBJECT: {
                        auto obj = unfinishedObjects.top().second;
                        obj->addToObject(jsonVal, key);
                        break;
                    }
                    case NORMAL:
                        root[key] = jsonVal;
                        break;
                    }
                    skipWhiteSpace(line);
                    canCreateValue = expectChar(line, ',');
                    break;
                }
                case 't': {
                    if (strcmp(line.substr(0, 4).c_str(), "true")==0) {
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_BOOL, "true");
                        switch (parseState.top()) {
                        case ARRAY: {

                        }
                        case OBJECT: {
                            auto obj = unfinishedObjects.top().second;
                            obj->addToObject(jsonVal, key);
                            break;
                        }
                        case NORMAL:
                            root[key] = jsonVal;
                            break;
                        }
                        // Remove 'true'
                        std::string s = "true";
                        std::string::size_type i = line.find(s);
                        if (i!=std::string::npos)
                            line.erase(i, s.length());
                        skipWhiteSpace(line);
                        if (!line.empty() && line[0]!=',' && line[0]!='\n' && line[0]!=' ') {
                            std::string c(1, line[0]);
                            throw ParseError(currentLine, line, "Unexpected token: '"+c+"'");
                        }
                        canCreateValue = expectChar(line, ',');
                        break;
                    }
                }
                case 'f': {
                    if (strcmp(line.substr(0, 5).c_str(), "false")==0) {
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_BOOL, "false");
                        switch (parseState.top()) {
                        case ARRAY: {

                        }
                        case OBJECT: {
                            auto obj = unfinishedObjects.top().second;
                            obj->addToObject(jsonVal, key);
                            break;
                        }
                        case NORMAL:
                            root[key] = jsonVal;
                            break;
                        }
                        // Remove 'false'
                        std::string s = "false";
                        std::string::size_type i = line.find(s);
                        if (i!=std::string::npos)
                            line.erase(i, s.length());
                        skipWhiteSpace(line);
                        if (!line.empty() && line[0]!=',' && line[0]!='\n' && line[0]!=' ') {
                            std::string c(1, line[0]);
                            throw ParseError(currentLine, line, "Unexpected token: '"+c+"'");
                        }
                        canCreateValue = expectChar(line, ',');
                        break;
                    }
                }
                case '[': {
                    m_straightCount++;
                    parseState.push(ARRAY);
                    unfinishedArrays.push({key, new JsonValue(ValueType::JSON_ARRAY)});
                    canCreateValue = true;
                    break;
                }
                case '{': {
                    m_curlyCount++;
                    parseState.push(OBJECT);
                    unfinishedObjects.push({key, new JsonValue(ValueType::JSON_OBJ)});
                    break;
                }
                case '}': {
                    m_curlyCount--;
                    if (unfinishedObjects.empty())
                        throw ParseError(currentLine, line, "Unbalanced {}, missing '}'");
                    auto top = unfinishedObjects.top();
                    parseState.pop();
                    unfinishedObjects.pop();
                    if (unfinishedObjects.empty())
                        root[top.first] = top.second;
                    else {
                        auto attachTo = unfinishedObjects.top().second;
                        attachTo->addToObject(top.second, top.first);
                    }
                    skipWhiteSpace(line);
                    canCreateValue = expectChar(line, ',');
                    break;
                }
                case ']' : {
                    m_straightCount--;
                    if (unfinishedArrays.empty())
                        throw ParseError(currentLine, line, "Unbalanced [], missing ']'");
                    auto top = unfinishedArrays.top();
                    unfinishedArrays.pop();
                    parseState.pop();
                    if (unfinishedArrays.empty())
                        root[top.first] = top.second;
                    else {
                        auto attachTo = unfinishedArrays.top().second;
                        attachTo->addToArray(top.second);
                    }
                    skipWhiteSpace(line);
                    canCreateValue = expectChar(line, ',');
                    break;
                }
                default: {
                    if (isdigit(new_current) || new_current=='-') {
                        std::string value = readNumberValue(line);
                        skipWhiteSpace(line);
                        if (!line.empty() && line.front()!=',' && line.front()!=' ' && line.front()!='\n') {
                            std::string c(1, line.front());
                            throw ParseError(currentLine, line, "Unexpected token "+c);
                        }
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_NUM, value);
                        switch (parseState.top()) {
                        case ARRAY: {

                        }
                        case OBJECT: {
                            auto obj = unfinishedObjects.top().second;
                            obj->addToObject(jsonVal, key);
                            break;
                        }
                        case NORMAL:
                            root[key] = jsonVal;
                            break;
                        }
                        canCreateValue = expectChar(line, ',');
                        break;
                    }
                    std::string c(1, new_current);
                    throw ParseError(currentLine, line, "Unexpected token: '"+c+"'");
                }

                }
                break;
            }
            default:
                if (parseState.top()==ARRAY) {
                    if (isdigit(current) || current=='-') {
                        std::string value = readNumberValue(line);
                        skipWhiteSpace(line);
                        JsonValue* jsonVal = new JsonValue(ValueType::JSON_NUM, value);
                        auto addTo = unfinishedArrays.top().second;
                        addTo->addToArray(jsonVal);
                        canCreateValue = expectChar(line, ',');
                        continue;
                    }
                }
                std::string ch;
                ch += current;
                throw ParseError(currentLine, line, "Unexpected token: '"+ch+"'");
            }
            if (!first)
                throw ParseError(currentLine, line, "Missing root '{'");
            if (m_straightCount<0)
                throw ParseError(currentLine, line, "Unbalanced '[]'");
            if (m_curlyCount<0)
                throw ParseError(currentLine, line, "Unbalanced '{}'");

            skipWhiteSpace(line);
            line.erase(0, 1);
        }
    }

    if (canCreateValue)
        throw ParseError(currentLine, "Expected new object after ','");
    if (m_curlyCount!=0 || !unfinishedObjects.empty())
        throw ParseError(currentLine, "END OF FILE", "Unbalanced {}");
    if (m_straightCount!=0 || !unfinishedArrays.empty())
        throw ParseError(currentLine, "END OF FILE", "Unbalanced []");
}

std::string JsonParser::getQuotedString(std::string& line, char quoteChar)
{
    std::string result;
    line.erase(0, 1);
    while (line.front()!=quoteChar) {
        result += line.front();
        line.erase(0, 1);
    }
    line.erase(0, 1);

    skipWhiteSpace(line);
    return result;
}

bool JsonParser::expectChar(std::string& line, char c)
{
    if (line.empty())
        return false;
    if (line.front()==c) {
        line.erase(0, 1);
        return true;
    }
    return false;
}

JsonParser::JsonParser()
        :parseState(), currentLine(0), m_curlyCount(0), m_straightCount(0)
{
    parseState.push(NORMAL);
    root = JsonObject();
    canCreateValue = true;
}

JsonValue& JsonParser::operator[](const std::string& key)
{
    return *(root[key]);
}

std::string JsonParser::readNumberValue(std::string& line)
{
    bool readDot = false;
    bool readMin = false;
    auto valid = [&](std::string& line) {
        if (line.front()=='.') {
            if (!readDot) {
                readDot = true;
            }
            else {
                throw ParseError(currentLine, line, "Incorrect number format");
            }
        }
        if (line.front()=='-') {
            if (!readMin) {
                readMin = true;
            }
            else {
                throw ParseError(currentLine, line, "Incorrect number format");
            }
        }
        return isdigit(line.front()) || line.front()=='.' || line.front()=='-';
    };

    std::string result;
    while (valid(line)) {
        result += line.front();
        line.erase(0, 1);
    }
    return result;
}

JsonParser::~JsonParser()
{
    clear();
}

void JsonParser::clear()
{
    currentLine = 0;
    parseState = std::stack<PARSE_STATE>{};
    parseState.push(PARSE_STATE::NORMAL);
    canCreateValue = true;
    for (auto it = root.begin(); it!=root.end();) {
        delete root[it->first];
        it = root.erase(it);
    }
    root.clear();
}

JsonParser::JsonParser(const std::string& file_name)
        :JsonParser()
{
    parse(file_name);
}

