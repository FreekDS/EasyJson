# EasyJson | [![Build Status](https://travis-ci.com/FreekDS/EasyJson.svg?token=oRQDqQmpkBiWswbK3qg5&branch=master)](https://travis-ci.com/FreekDS/EasyJson)
A simple JsonParser. Read only.

## Readme content
1. [Basic usage](#basic-usage)
2. [New types](#new-object-types)
3. [Notes](#notes)

## Basic Usage
Create and parse files
```c++
JsonParser parser;
parser.parse("cool_file.json");
// or
JsonParser parser("cool_file.json");
```
Access members
```c++
// Simple access methods
parser["bool key"].getBoolValue();
parser["string key"].getStringValue();
parser["Cool json object"].getObjectValue();

// Array and sub objects
parser["array"][2].getNumberValue();
parser["object"]["subobject"]["subobject name"].getStringValue();
```
## New object types
This little library creates some extra types:
```
JsonValue: can contain all possible json values (number, bool, object, array, string)
JsonObject: special case of JsonValue. An alias for std::map<std::string, JsonValue*>
JsonArray: Special case of JsonValue. An alias for std::vector<JsonValue*>
```

## Notes
* Assumption I made: when defining json values, the comma needs to follow the value in the same line. ex
```json
can be parsed
{
  "value1": true,
  "value2": false
}
cannot be parsed
{
  "value1": true
  ,
  "value2": false
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;all other possible json formats should work (ex. everything in one line).
* This project has not been tested thoroughly and will contain bugs.
