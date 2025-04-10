#include "vector_toolbox.h"
#include <iostream>
#include <stdexcept>
#include <cmath>


Vector::Vector() : data(nullptr), size(0), capacity(0) {};
Vector::Vector(size_t size) : size(size), capacity(size), data(new double[capacity] {}) {};
Vector::Vector(const Vector& other) : size(other.size), capacity(other.capacity), data(new double[other.capacity]) { // Copy constructor
    for (size_t i = 0; i < size; ++i){
        data[i] = other.data[i];
    }
};   

Vector& Vector::operator=(const Vector& other){ // Copy assignment
    if(this == &other)  return *this;

    delete[] data;

    size = other.size;
    capacity = other.capacity;
    data = new double[capacity];
    for (size_t i = 0; i < capacity; ++i){
        data[i] = other.data[i];
    }

    return *this;
    
};  

Vector::~Vector() {
    delete[] data;
};

void Vector::resize(size_t new_capacity){
    double* new_data = new double[new_capacity];
    for (size_t i = 0; i < size; i++){
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = new_capacity;    
};

size_t Vector::getSize() const { return size; };

double& Vector::operator[](size_t index){
    if(index >= size){
        throw std::out_of_range("Index out of range!");
    }
    return data[index];
}

void Vector::push_back(double value){
    if(size == capacity){
        size_t new_capacity = capacity == 0 ? 1 : capacity * 2;
        resize(new_capacity);
    }
    data[size++] = value;
}

double Vector::pop_back() {
    if (size > 0) {
        double res = data[size - 1];
        size--;
        return res;
    } else {
        throw std::underflow_error("Cannot pop from an empty vector");
    }
}

void Vector::set(size_t index, double value) {
    if (index >= size)    throw std::out_of_range("Index out of range!");
    data[index] = value;
};

double Vector::dot(const Vector& other) const {
    if (size != other.size) throw std::invalid_argument("Vector sizes do not match");

    double result = 0.0;
    for (size_t i = 0; i < size; ++i){
        result += data[i] * other.data[i];
    }
    return result;
};

double Vector::magnitude() const {
    double result = 0.0;
    for (size_t i = 0; i < size; ++i) {
        result += data[i] * data[i];
    }
    return std::sqrt(result);
    
};
void Vector::normalize() {
    double mag = magnitude();
    if (mag == 0.0) throw std::runtime_error("Cannot normalize a zero vector");

    for (size_t i = 0; i < size; ++i) {
        data[i] /= mag;
    }
};
void Vector::print() const {
    std::cout << "Vector(";
    for (size_t i = 0; i < size; ++i) {
        std::cout << data[i];
        if (i < size - 1) std::cout << ", ";
    }
    std::cout << ")" << std::endl;
};
