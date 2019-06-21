#ifndef JSONPARSER_JSONPARSER_H
#define JSONPARSER_JSONPARSER_H

#include <string>
#include <map>
#include <vector>
#include <stack>

//! Forward declaration to make using statements valid
class JsonValue;

/**
 * Some easy names for 'larger' data structures
 */
using JsonObject = std::map<std::string, JsonValue*>;
using JsonArray = std::vector<JsonValue*>;

/**
 * Possible JSON Values
 */
enum ValueType {
    JSON_NULL,
    JSON_NUM,
    JSON_ARRAY,
    JSON_OBJ,
    JSON_STRING,
    JSON_BOOL
};

/**
 * This class is the blueprint for each possible JSON Value.
 */
class JsonValue {
private:
    ValueType type;                 /**< Type of the value*/
    bool copied;                    /**< Copied flag, flag is set in copy constructor, default false*/
    union {                         /**< Union of possible Json types*/
        bool bool_value;            /**< Container if value is boolean type*/
        double number_value;        /**< Container if value is number type*/
        std::string* string_value;  /**< Container if value is string type*/
        JsonObject* object_value;   /**< Container if value is JsonObject type*/
        JsonArray* array_value;     /**< Container if value is JsonArray type*/
    };

public:

    /**
     * Copy constructor. First created object keeps delete rights.
     * The new object's copied flag will be set to true.
     * @param other Original JsonValue object.
     */
    JsonValue(const JsonValue& other);

    /**
     * Assignment operator. First created object keeps delete rights.
     * The new object's copied flag will be set to true.
     * @param other Original JsonValue object.
     * @return reference to this object.
     */
    JsonValue& operator=(const JsonValue& other);

    /**
     * Default constructor. Sets value type to null.
     */
    JsonValue();

    /**
     * Constructor taking a value type as input parameter.
     * This constructor should be used to create an empty json array structure, or an
     * empty json object structure
     * @throws invalid argument error if type is other than JsonArray or JsonObject
     */
    explicit JsonValue(const ValueType&);

    /**
     * Constructor taking a value type and key (as string) as input parameters.
     * @param type Type of the value (ValueType)
     * @param key Key for the value (string)
     */
    JsonValue(const ValueType& type, const std::string& key);

    /**
     * Destructor of the JsonValue class.
     * If the copied flag is set, no destruction will happen.
     */
    ~JsonValue();

    /**
     * Check whether the JsonValue is of JsonBool type.
     * @return true if the type is a JsonBool.
     */
    bool isBool() const;

    /**
     * Check whether the JsonValue is of JsonNull type.
     * @return true if the type is JsonNull.
     */
    bool isNull() const;

    /**
     * Check whether the JsonValue is of JsonString type.
     * @return true if the type is JsonString.
     */
    bool isString() const;

    /**
     * Check whether the JsonValue is of JsonArray type.
     * @return true if the type is JsonArray.
     */
    bool isArray() const;

    /**
     * Check whether the JsonValue is of JsonObject type.
     * @return true if the type is JsonObject.
     */
    bool isObject() const;

    /**
     * Check whether the JsonValue is of JsonNum type.
     * @return True if the type is JsonNum.
     */
    bool isNumber() const;

    /**
     * Get the boolean value of the JsonValue.
     * If the type is JsonNum, it will check whether it's 0 or 1, and it converts those
     * to a boolean value.
     * @throw invalid argument if the type is not JsonBool or the JsonNum is not 0 or 1.
     * @return the boolean value of the JsonValue.
     */
    bool getBoolValue() const;

    /**
     * Get the number value of the JsonValue.
     * @throw invalid argument if the type is not JsonNum.
     * @return the number value of the JsonValue.
     */
    double getNumberValue() const;

    /**
     * Get the string value of the JsonValue
     * @throw invalid argument if the type is not JsonString
     * @return the string value of the JsonValue
     */
    std::string getStringValue() const;

    /**
     * Get the entire array object of the JsonValue.
     * @throw invalid argument if the type is not JsonArray.
     * @return the entire array object of the JsonValue (std::vector semantics)
     */
    JsonArray* getArrayValue() const;

    /**
     * Get the entire object value of the JsonValue.
     * @throw invalid argument if the type is not JsonObject.
     * @return the entire array object of the JsonValue (std::map semantics)
     */
    JsonObject* getObjectValue() const;

    /**
     * Adds a value to the array value.
     * @throw invalid argument if the type is not JsonArray.
     * @param value Value to add to the array.
     */
    void addToArray(JsonValue* value);

    /**
     * Adds a key and associated value to the JsonObject.
     * @throw invalid argument if the type is not JsonObject.
     * @throw invalid argument if the key already exists.
     * @param value Value to add to the object.
     * @param key Key to reference the value with.
     */
    void addToObject(JsonValue* value, const std::string& key);

    /**
     * Index operator which can be used if the ValueType is JsonArray.
     * @throw invalid argument if the type is not JsonArray.
     * @throw invalid argument if the index is out of bounds.
     * @param index Index in the array.
     * @return Reference to the JsonValue in the JsonArray.
     */
    JsonValue& operator[](int index);

    /**
     * Index operator which can be used if the ValueType is JsonObject
     * @throw invalid argument if the type is not JsonObject.
     * @throw invalid argument if the key cannot be found in the JsonObject.
     * @param key Key associated to the value we want to get.
     * @return Reference to the JsonValue associated with key in the JsonObject.
     */
    JsonValue& operator[](const std::string& key);

    /**
     * Check wheter a key exists if the ValueType is JsonObject.
     * @throw invalid argument if the type is not JsonObject
     * @param key Key to check
     * @return True if the key can be found
     */
    bool hasKey(const std::string& key);
};

/**
 * Simple error class for Parsing errors.
 */
class ParseError : public std::exception {
private:
    std::string message;    /**< Message to show*/
public:

    /**
     * Constructor for parse errors.
     * @param line Line of the file where the error happened.
     * @param content Contents of the line where the error happened.
     * @param message Additional message.
     */
    ParseError(int line, const std::string& content, const std::string& message)
            :ParseError(line, message)
    {
        if (content.empty())
            return;
        this->message = "Error at line "+std::to_string(line)+":\n|\n"+content+"\n"+message;
    }

    /**
     * Constructor for parse errors.
     * @param line Line of the file where the error happened.
     * @param message Additional message.
     */
    ParseError(int line, const std::string& message)
    {
        this->message = "Error at line "+std::to_string(line)+": "+message;
    }

    /**
     * Overridden what function. Displays the message.
     * @return Error message.
     */
    const char* what() const noexcept override
    {
        return message.c_str();
    }
};

/**
 * Class that parses a file and builds a Json structure which can be accessed
 * from within the code.
 */
class JsonParser {
public:

    /**
     * Default constructor for the JsonParser.
     * Will initialize the parse state as normal, and allows to create the first object.
     */
    JsonParser();

    /**
     * Creates a JsonParser and immediately parses a file.
     * @param file_name Name of the file to parse.
     */
    explicit JsonParser(const std::string& file_name);

    /**
     * Check whether a key exists.
     * @param key Key to check
     * @return True if the key exists
     */
    bool hasKey(const std::string& key);

    /**
     * Destructor for the JsonParser.
     * @related clear()
     */
    ~JsonParser();

    /**
     * Parses a json file and creates a data structure.
     * @param file_name Path to input file.
     */
    void parse(const std::string& file_name);

    /**
     * Index operator used to access the root JsonObject easily.
     * @param key Key to access.
     * @return Reference to JsonValue associated with the key.
     */
    JsonValue& operator[](const std::string& key);

    /**
     * Deleted copy constructor. Copying is not allowed.
     */
    JsonParser(const JsonParser&) = delete;

    /**
     * Deleted assignment operator. Assigning is not allowed.
     */
    JsonParser& operator=(const JsonParser&) = delete;

private:

    /**
     * Different states of the parser
     */
    enum PARSE_STATE {
        NORMAL,
        ARRAY,
        OBJECT
    };

    std::stack<PARSE_STATE> parseState;     /**< Stack of states to remember what we were doing*/

    std::stack<std::pair<std::string, JsonValue*>> unfinishedObjects;   /**< Stack of unfinished JsonObjects*/
    std::stack<std::pair<std::string, JsonValue*>> unfinishedArrays;    /**< Stack of unfinished JsonArrays*/

    JsonObject root;        /**< Root JsonObject*/
    int m_curlyCount;       /**< Count of curly brackets '{}'*/
    int m_straightCount;    /**< Count of straight brackets '[]'*/
    int currentLine;        /**< Current line in the file*/
    bool canCreateValue;    /**< Flag to determine wheter we can create a new JsonValue*/

    /**
     * Skip whitespaces in front of a line.
     * @param line Line where we need to skip the whitespaces in.
     */
    static void skipWhiteSpace(std::string& line);

    /**
     * Read the quoted string.
     * Also erases the quoted string from the line.
     * The first character of the line should be a quoteChar.
     * @param line String that contains a quoted substring.
     * @param quoteChar Determine what the quote character is (' or ")
     * @return The quoted substring. If there is none, an empty string will be returned.
     */
    static std::string getQuotedString(std::string& line, char quoteChar);

    /**
     * Check whether the next char in the line is c.
     * If the expected character is found, it will be removed.
     * @param line String wherein we need to check for the next char.
     * @param c Character we need to check for.
     * @return True if the first character of the string is c, else false.
     */
    static bool expectChar(std::string& line, char c);

    /**
     * Read a number from a string.
     * The first character of the input should be a digit.
     * @throw Parse error if the number is formatted incorrectly (ex. two dots)
     * @param line Line to read the number from.
     * @return std::string containing the number.
     */
    std::string readNumberValue(std::string& line);

    /**
     * Clears and resets the object.
     * Removes all JsonValues. This function is also used in @see parse()
     * A new file can be parsed with the same object, but older data will be destructed
     * and can not be used anymore. In case you want to parse multiple files at the same time, you should
     * use multiple JsonParsers.
     * Sequentially parsing is possible, but the previous objects will be freed from memory.
     */
    void clear();

};

#endif //JSONPARSER_JSONPARSER_H
