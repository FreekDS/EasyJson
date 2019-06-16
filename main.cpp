#include <iostream>
#include "jsonParser.h"
#include <chrono>

int main()
{
    auto start = std::chrono::system_clock::now();
    JsonParser parser;
//    std::cout << "--Case 1: String-----------------------------" << std::endl;
//    parser.parse("../test/string.json");
//    std::cout << parser["string"].getStringValue() << std::endl;
//    std::cout << "--Case 2: 2 Strings--------------------------" << std::endl;
//    parser.parse("../test/multiple.json");
//    std::cout << parser["string1"].getStringValue() << std::endl;
//    std::cout << parser["string2"].getStringValue() << std::endl;
//    std::cout << "--Case 3: Bool-------------------------------" << std::endl;
//    parser.parse("../test/bool.json");
//    std::cout << parser["bool"].getBoolValue() << std::endl;
//    std::cout << parser["bool2"].getBoolValue() << std::endl;
//    std::cout << "--Case 4: number-------------------------------" << std::endl;
//    parser.parse("../test/number.json");
//    std::cout << parser["number"].getNumberValue() << std::endl;
//    std::cout << parser["number2"].getNumberValue() << std::endl;
//
//
//    parser.parse("../test/nested_object.json");
//    std::cout << parser["object"]["object"]["test"].getBoolValue() << std::endl;


    parser.parse("../test/objectarray.json");
    auto test = parser["array"];


    auto end = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "runtime: " << duration.count() << std::endl;
    return 0;
}