#include "utils.h"

template<typename T>
void swap_ref(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

template<typename T>
void swap_ptr(T* a, T* b) {
    if (!a || !b) return;
    T temp = *a;
    *a = *b;
    *b = temp;
}

