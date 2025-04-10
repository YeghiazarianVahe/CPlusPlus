#pragma once

class Vector{
    public:
        Vector();
        Vector(size_t );
        Vector(const Vector& );             // Copy constructor
        Vector& operator=(const Vector& );  // Copy assignment
        ~Vector();

        // Accessors
        size_t getSize() const;
        void set(size_t , double );
        double& operator[](size_t );

        // Operations
        double dot(const Vector&) const;
        double magnitude() const;
        void normalize();
        void print() const;
        
        void push_back(double value);
        double pop_back();

    private:
        void resize(size_t);
        
    private:
        size_t size;
        size_t capacity;
        double* data;
};