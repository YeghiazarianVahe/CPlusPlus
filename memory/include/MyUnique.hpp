#pragma once


#include <cstddef> // std::nullptr_t
#include <utility> // std::exchange

//
// A minimal std::unique_ptr–like template (exclusive ownership).
// Header‐only (all functions inline/templated).
//
template <typename T>
class MyUnique {
public:
    // Construct from raw pointer (default nullptr).
    explicit MyUnique(T* ptr = nullptr) noexcept
        : ptr_{ ptr }
    {}

    // Delete copy operations (exclusive ownership).
    MyUnique(const MyUnique&) = delete;
    MyUnique& operator=(const MyUnique&) = delete;

    // Move constructor: take ownership, leave other null.
    MyUnique(MyUnique&& other) noexcept
        : ptr_{ other.ptr_ }
    {
        other.ptr_ = nullptr;
    }

    // Move assignment: free current, take ownership, leave other null.
    MyUnique& operator=(MyUnique&& other) noexcept {
        if (this != &other) {
            reset();             // delete current ptr_
            ptr_ = other.ptr_;   // steal
            other.ptr_ = nullptr;
        }
        return *this;
    }

    // Destructor: delete owned pointer.
    ~MyUnique() {
        delete ptr_;
    }

    // Release ownership and return raw pointer. This MyUnique becomes null.
    T* release() noexcept {
        return std::exchange(ptr_, nullptr);
    }

    // Delete current pointer (if any) and take ownership of new_ptr.
    void reset(T* new_ptr = nullptr) noexcept {
        if (ptr_ != new_ptr) {
            delete ptr_;
            ptr_ = new_ptr;
        }
    }

    // Observers:
    T* get() const noexcept { return ptr_; }
    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T* ptr_;
};


