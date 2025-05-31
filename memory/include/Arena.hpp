#pragma once

#include <cstdlib> // std::malloc, std::free
#include <vector> 
#include <cstddef> // std::size_t
#include <stdexcept>// std::bad_alloc



//
// A simple “arena” (manual memory manager) that tracks all allocated blocks
// and frees them when the Arena is destroyed (or when release_all() is called).
//
class Arena {
public:
    // Constructor: nothing special to do.
    Arena() = default;

    // Disable copy (we don’t want shallow copies of allocations_).
    Arena(const Arena&) = delete;
    Arena& operator=(const Arena&) = delete;

    // Move operations: transfers ownership of the allocation list.
    Arena(Arena&& other) noexcept
        : allocations_{ std::move(other.allocations_) }
    {
        other.allocations_.clear();
    }

    Arena& operator=(Arena&& other) noexcept {
        if (this != &other) {
            release_all();
            allocations_ = std::move(other.allocations_);
            other.allocations_.clear();
        }
        return *this;
    }

    // Allocate `bytes` bytes on the heap. Throws std::bad_alloc on failure.
    // The returned pointer is stored internally and will be freed in ~Arena().
    void* allocate(std::size_t bytes) {
        void* ptr = std::malloc(bytes);
        if (!ptr) {
            throw std::bad_alloc();
        }
        allocations_.push_back(ptr);
        return ptr;
    }

    // Frees all previously allocated blocks and clears the internal list.
    void release_all() noexcept {
        for (void* p : allocations_) {
            std::free(p);
        }
        allocations_.clear();
    }

    // Destructor: free everything.
    ~Arena() {
        release_all();
    }

private:
    std::vector<void*> allocations_;
};
