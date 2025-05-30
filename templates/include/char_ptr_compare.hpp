#pragma once

#include "max_min.hpp"
#include <cstring>  // for strcmp

template<>
inline const char* max<const char*>(const char* a, const char* b) {
    if (!a) return b;
    if (!b) return a;
    return std::strcmp(a, b) > 0 ? a : b;
}

