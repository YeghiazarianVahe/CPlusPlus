#include "string_toolbox.h"
#include "utils.h"

namespace strutils {

    std::string reverse(const std::string& input) {
        std::string result = input;
        size_t n = result.length();

        for (size_t i = 0; i < n / 2; ++i) {
            swap_ref(result[i], result[n - 1 - i]);
        }
        
        return result;
    }

    std::string to_upper(const std::string& input) {
        std::string result = input;

        for (size_t i = 0; result[i] != '\0'; ++i) {
            if (result[i] >= 'a' && result[i] <= 'z') {
                result[i] = result[i] - 32;
            }
        }

        return result;
    }

    bool is_palindrome(const std::string& input) {
        if (input.empty())    return true;

        size_t left = 0;
        size_t right = input.length() - 1;

        while(left < right){
            if(input[left++] != input[right--])
                return false;
        }

        return true;
    }

}
