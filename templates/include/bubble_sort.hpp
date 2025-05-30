#pragma once

#include <iostream>

template<typename T>
inline void swap(T& a, T& b) {
	T tmp = static_cast<T&&>(a);
	a = static_cast<T&&>(b);
	b = static_cast<T&&>(tmp);
}



template<typename T>
void bubble_sort(T* arr, size_t n) {
	for(size_t i = 0; i < n; ++i){
		for(size_t j = 1; j + i < n; ++j){
			if(arr[j] < arr[j-1]) {
				swap(arr[j], arr[j-1]);
			}
		}
	}
}
