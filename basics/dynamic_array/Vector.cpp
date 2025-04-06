#include "Vector.h"

Vector::Vector() : data(nullptr), size(0), capacity(0){};

Vector::~Vector(){ delete[] data; };


int& Vector::operator[](std::size_t index){
    if(index >= size){
        throw std::out_of_range("Index out of range!");
    }
    return data[index];
}

void Vector::resize(std::size_t new_capacity){
    int* new_data = new int[new_capacity];
    for (size_t i = 0; i < size; i++){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;    
};

void Vector::push_back(int value){
    if(size == capacity){
        int new_capacity = capacity == 0 ? 1 : capacity * 2;
        resize(new_capacity);
    }
    data[size++] = value;
}

void Vector::pop_back(){
    if(size > 0){
        size--;
    }
}

std::size_t Vector::get_size() const { return size; };
std::size_t Vector::get_capacity() const { return capacity; };