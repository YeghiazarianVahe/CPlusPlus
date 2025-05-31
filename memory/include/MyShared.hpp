#pragma once

#include <cstddef>   // std::nullptr_t, std::size_t
#include <utility>   // std::exchange
#include <stdexcept> // std::runtime_error

//
// A very basic, non‐thread‐safe, reference‐counted smart pointer.
// Simplified mimic of std::shared_ptr<T>.
// All code is header‐only.
//
template <typename T>
class MyShared {
public:
    // Default constructor: empty (nullptr, no ref count).
    MyShared() noexcept
        : ptr_{ nullptr }, count_{ nullptr }
    {}

    // Construct from raw pointer. Initializes count to 1.
    explicit MyShared(T* raw_ptr)
        : ptr_{ raw_ptr }
    {
        if (ptr_) {
            count_ = new std::size_t(1);
        } else {
            count_ = nullptr;
        }
    }

    // Copy constructor: share ownership, increment count.
    MyShared(const MyShared& other) noexcept
        : ptr_{ other.ptr_ }, count_{ other.count_ }
    {
        if (count_) {
            ++(*count_);
        }
    }

    // Move constructor: steal pointers, leave other empty.
    MyShared(MyShared&& other) noexcept
        : ptr_{ other.ptr_ }, count_{ other.count_ }
    {
        other.ptr_   = nullptr;
        other.count_ = nullptr;
    }

    // Copy assignment: clean up current, then share/increment from other.
    MyShared& operator=(const MyShared& other) noexcept {
        if (this == &other) {
            return *this;
        }
        release_ownership();
        ptr_   = other.ptr_;
        count_ = other.count_;
        if (count_) {
            ++(*count_);
        }
        return *this;
    }

    // Move assignment: clean up current, then steal from other.
    MyShared& operator=(MyShared&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        release_ownership();
        ptr_   = other.ptr_;
        count_ = other.count_;
        other.ptr_   = nullptr;
        other.count_ = nullptr;
        return *this;
    }

    // Destructor: decrement count; if zero, delete managed object + count.
    ~MyShared() {
        release_ownership();
    }

    // Return the number of shared references (0 if empty).
    std::size_t use_count() const noexcept {
        return count_ ? *count_ : 0;
    }

    // Observers:
    T* get() const noexcept { return ptr_; }
    T& operator*() const noexcept { return *ptr_; }
    T* operator->() const noexcept { return ptr_; }
    explicit operator bool() const noexcept { return ptr_ != nullptr; }

private:
    T*           ptr_;
    std::size_t* count_;

    // Helper to decrement and delete if needed.
    void release_ownership() noexcept {
        if (count_) {
            if (--(*count_) == 0) {
                delete ptr_;
                delete count_;
            }
            ptr_   = nullptr;
            count_ = nullptr;
        }
    }
};


