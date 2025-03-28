#include "string_utils.h"

int my_strlen(const char* str){
    int length = 0;
    while(str[length] != 0){
        length++;
    }
    return length;
};

char* my_strcpy(char* dest, const char* src){
    int i = 0;
    while(src[i] != 0){
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
};

int my_strcmp(const char* a, const char* b){
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0'){
        if (a[i] != b[i]){
            return a[i] - b[i];
        }
    i++;
    }
    return a[i] - b[i];
};