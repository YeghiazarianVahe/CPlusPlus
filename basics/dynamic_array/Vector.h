#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>


class Vector{
    public:
        Vector();
        ~Vector();
        void push_back(int value);
        void pop_back();
        int& operator[](std::size_t index);
        std::size_t get_size() const;
        std::size_t get_capacity() const; 

    private:
        void resize(std::size_t new_capacity);
        
    private:
        std::size_t size;
        std::size_t capacity;
        int* data;
};


#endif