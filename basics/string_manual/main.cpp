#include <iostream>
#include <cstring>
#include "string_utils.h"

int main() {
    const char* test1 = "hello";
    const char* test2 = "world";

    std::cout << "|-----------------------------|\n";
    std::cout << "|---------  Basic   ----------|\n";
    std::cout << "|-----------------------------|\n";

    
    // Basic strlen test
    std::cout << "my_strlen: " << my_strlen(test1) << ", std::strlen: " << std::strlen(test1) << "\n";

    // strcpy test
    char dest1[100];
    char dest2[100];
    my_strcpy(dest1, test1);
    std::strcpy(dest2, test1);
    std::cout << "my_strcpy: " << dest1 << ", std::strcpy: " << dest2 << "\n";

    // strcmp test
    int cmp1 = my_strcmp(test1, test2);
    int cmp2 = std::strcmp(test1, test2);
    std::cout << "my_strcmp: " << cmp1 << ", std::strcmp: " << cmp2 << "\n";


    std::cout << "|-----------------------------|\n";
    std::cout << "|---------  Empty   ----------|\n";
    std::cout << "|-----------------------------|\n";
    // 🔸 Empty string tests
    const char* empty = "";
    std::cout << "my_strlen (empty): " << my_strlen(empty) << ", std::strlen: " << std::strlen(empty) << "\n";

    my_strcpy(dest1, empty);
    std::strcpy(dest2, empty);
    std::cout << "my_strcpy (empty): " << dest1 << ", std::strcpy: " << dest2 << "\n";

    std::cout << "my_strcmp (empty vs test1): " << my_strcmp(empty, test1) 
              << ", std::strcmp: " << std::strcmp(empty, test1) << "\n";

    
    std::cout << "|-----------------------------|\n";
    std::cout << "|---------  Equal   ----------|\n";
    std::cout << "|-----------------------------|\n";

    // 🔸 Equal strings
    const char* equal1 = "same";
    const char* equal2 = "same";

    std::cout << "my_strcmp (equal): " << my_strcmp(equal1, equal2) 
              << ", std::strcmp: " << std::strcmp(equal1, equal2) << "\n";


    std::cout << "|------------------------------|\n";
    std::cout << "|-------  Whitespace   --------|\n";
    std::cout << "|------------------------------|\n";
    // 🔸 Strings with whitespace and special characters
    const char* spaced = "hello world!";
    const char* punctuated = "hello, world!";

    std::cout << "my_strlen (spaced): " << my_strlen(spaced) 
              << ", std::strlen: " << std::strlen(spaced) << "\n";

    my_strcpy(dest1, spaced);
    std::cout << "my_strcpy (spaced): " << dest1 << "\n";

    std::cout << "my_strcmp (spaced vs punctuated): " 
              << my_strcmp(spaced, punctuated)
              << ", std::strcmp: " << std::strcmp(spaced, punctuated) << "\n";

    std::cout << "|-----------------------------|\n";
    std::cout << "|---------  Case   ----------|\n";
    std::cout << "|-----------------------------|\n";
    // 🔸 Case sensitivity
    const char* upper = "HELLO";
    const char* lower = "hello";

    std::cout << "my_strcmp (case): " << my_strcmp(upper, lower) 
              << ", std::strcmp: " << std::strcmp(upper, lower) << "\n";

    std::cout << "|-------------------------------|\n";
    std::cout << "|---------  Partial   ----------|\n";
    std::cout << "|-------------------------------|\n";
    // 🔸 Partial match
    const char* prefix1 = "hello";
    const char* prefix2 = "hell";

    std::cout << "my_strcmp (prefix): " << my_strcmp(prefix1, prefix2) 
              << ", std::strcmp: " << std::strcmp(prefix1, prefix2) << "\n";

    return 0;
}
