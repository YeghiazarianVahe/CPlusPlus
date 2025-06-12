#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP

#include <cstddef>      // for size_t
#include <stdexcept>    // for std::out_of_range
#include <iterator>     // for std::random_access_iterator_tag
#include <utility>      // for std::swap

template<typename T>
class MyVector {
public:
    // ─────────────── Public types ───────────────
    using value_type             = T;
    using size_type              = size_t;
    using difference_type        = std::ptrdiff_t;
    using reference              = T&;
    using const_reference        = const T&;
    using pointer                = T*;
    using const_pointer          = const T*;

    // Custom iterator (random-access)
    struct iterator {
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = T*;
        using reference         = T&;

        iterator() : _ptr(nullptr) {}
        explicit iterator(T* p) : _ptr(p) {}

        reference operator*() const { return *_ptr; }
        pointer   operator->() const { return _ptr; }

        iterator& operator++()    { ++_ptr; return *this; }
        iterator  operator++(int) { iterator tmp = *this; ++_ptr; return tmp; }

        iterator& operator--()    { --_ptr; return *this; }
        iterator  operator--(int) { iterator tmp = *this; --_ptr; return tmp; }

        iterator& operator+=(difference_type n) { _ptr += n; return *this; }
        iterator  operator+(difference_type n) const { return iterator(_ptr + n); }
        friend iterator operator+(difference_type n, const iterator& it) { return iterator(it._ptr + n); }

        iterator& operator-=(difference_type n) { _ptr -= n; return *this; }
        iterator  operator-(difference_type n) const { return iterator(_ptr - n); }
        difference_type operator-(const iterator& other) const { return _ptr - other._ptr; }

        reference operator[](difference_type n) const { return *(_ptr + n); }

        bool operator==(const iterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const iterator& other) const { return _ptr != other._ptr; }
        bool operator< (const iterator& other) const { return _ptr <  other._ptr; }
        bool operator<=(const iterator& other) const { return _ptr <= other._ptr; }
        bool operator> (const iterator& other) const { return _ptr >  other._ptr; }
        bool operator>=(const iterator& other) const { return _ptr >= other._ptr; }

    private:
        T* _ptr;
        friend class MyVector;
    };

    // Const iterator
    struct const_iterator {
        using iterator_category = std::random_access_iterator_tag;
        using value_type        = T;
        using difference_type   = std::ptrdiff_t;
        using pointer           = const T*;
        using reference         = const T&;

        const_iterator() : _ptr(nullptr) {}
        explicit const_iterator(const T* p) : _ptr(p) {}
        const_iterator(const iterator& it) : _ptr(it._ptr) {} // allow conversion from iterator

        reference operator*() const { return *_ptr; }
        pointer   operator->() const { return _ptr; }

        const_iterator& operator++()    { ++_ptr; return *this; }
        const_iterator  operator++(int) { const_iterator tmp = *this; ++_ptr; return tmp; }

        const_iterator& operator--()    { --_ptr; return *this; }
        const_iterator  operator--(int) { const_iterator tmp = *this; --_ptr; return tmp; }

        const_iterator& operator+=(difference_type n) { _ptr += n; return *this; }
        const_iterator  operator+(difference_type n) const { return const_iterator(_ptr + n); }
        friend const_iterator operator+(difference_type n, const const_iterator& it) { return const_iterator(it._ptr + n); }

        const_iterator& operator-=(difference_type n) { _ptr -= n; return *this; }
        const_iterator  operator-(difference_type n) const { return const_iterator(_ptr - n); }
        difference_type operator-(const const_iterator& other) const { return _ptr - other._ptr; }

        reference operator[](difference_type n) const { return *(_ptr + n); }

        bool operator==(const const_iterator& other) const { return _ptr == other._ptr; }
        bool operator!=(const const_iterator& other) const { return _ptr != other._ptr; }
        bool operator< (const const_iterator& other) const { return _ptr <  other._ptr; }
        bool operator<=(const const_iterator& other) const { return _ptr <= other._ptr; }
        bool operator> (const const_iterator& other) const { return _ptr >  other._ptr; }
        bool operator>=(const const_iterator& other) const { return _ptr >= other._ptr; }

    private:
        const T* _ptr;
        friend class MyVector;
    };

    // ─────────────── Constructors / Destructor ───────────────
    MyVector() noexcept
        : _data(nullptr), _size(0), _capacity(0)
    {}

    explicit MyVector(size_type initialCapacity)
        : _data(nullptr), _size(0), _capacity(0)
    {
        if (initialCapacity > 0) {
            _data     = static_cast<T*>(::operator new(sizeof(T) * initialCapacity));
            _capacity = initialCapacity;
        }
    }

    ~MyVector() noexcept {
        clear();                    // destroy constructed elements
        ::operator delete(_data);   // free raw memory
    }

    MyVector(const MyVector& other)
        : _data(nullptr), _size(0), _capacity(0)
    {
        if (other._size > 0) {
            _data     = static_cast<T*>(::operator new(sizeof(T) * other._size));
            _capacity = other._size;
            _size     = other._size;
            for (size_type i = 0; i < _size; ++i) {
                new (_data + i) T(other._data[i]);
            }
        }
    }

    MyVector(MyVector&& other) noexcept
        : _data(other._data),
          _size(other._size),
          _capacity(other._capacity)
    {
        other._data     = nullptr;
        other._size     = 0;
        other._capacity = 0;
    }

    MyVector& operator=(const MyVector& other) {
        if (this != &other) {
            MyVector temp(other);
            swap(temp);
        }
        return *this;
    }

    MyVector& operator=(MyVector&& other) noexcept {
        if (this != &other) {
            clear();
            ::operator delete(_data);

            _data     = other._data;
            _size     = other._size;
            _capacity = other._capacity;

            other._data     = nullptr;
            other._size     = 0;
            other._capacity = 0;
        }
        return *this;
    }

    // ─────────────── Element Access ───────────────
    reference       operator[](size_type index) {
        return _data[index];
    }
    const_reference operator[](size_type index) const {
        return _data[index];
    }

    reference at(size_type index) {
        if (index >= _size) {
            throw std::out_of_range("MyVector::at() index out of range");
        }
        return _data[index];
    }
    const_reference at(size_type index) const {
        if (index >= _size) {
            throw std::out_of_range("MyVector::at() index out of range");
        }
        return _data[index];
    }

    reference front() {
        return _data[0];
    }
    const_reference front() const {
        return _data[0];
    }

    reference back() {
        return _data[_size - 1];
    }
    const_reference back() const {
        return _data[_size - 1];
    }

    pointer       data() noexcept       { return _data; }
    const_pointer data() const noexcept { return _data; }

    // ─────────────── Iterators ───────────────
    iterator       begin()       noexcept { return iterator(_data); }
    iterator       end()         noexcept { return iterator(_data + _size); }
    const_iterator begin() const noexcept { return const_iterator(_data); }
    const_iterator end()   const noexcept { return const_iterator(_data + _size); }

    const_iterator cbegin() const noexcept { return const_iterator(_data); }
    const_iterator cend()   const noexcept { return const_iterator(_data + _size); }

    // ─────────────── Capacity ───────────────
    bool      empty()    const noexcept { return (_size == 0); }
    size_type size()     const noexcept { return _size; }
    size_type capacity() const noexcept { return _capacity; }

    void reserve(size_type newCapacity) {
        if (newCapacity <= _capacity) 
            return;

        T* newBlock = static_cast<T*>(::operator new(sizeof(T) * newCapacity));
        // Move‐construct existing elements into newBlock
        for (size_type i = 0; i < _size; ++i) {
            new (newBlock + i) T(std::move(_data[i]));
            _data[i].~T();
        }
        ::operator delete(_data);
        _data     = newBlock;
        _capacity = newCapacity;
    }

    void shrink_to_fit() {
        if (_size < _capacity) {
            if (_size == 0) {
                clear();
                ::operator delete(_data);
                _data     = nullptr;
                _capacity = 0;
            } else {
                T* newBlock = static_cast<T*>(::operator new(sizeof(T) * _size));
                for (size_type i = 0; i < _size; ++i) {
                    new (newBlock + i) T(std::move(_data[i]));
                    _data[i].~T();
                }
                ::operator delete(_data);
                _data     = newBlock;
                _capacity = _size;
            }
        }
    }

    // ─────────────── Modifiers ───────────────
    void clear() noexcept {
        for (size_type i = 0; i < _size; ++i) {
            _data[i].~T();
        }
        _size = 0;
    }

    void push_back(const T& value) {
        if (_size == _capacity) {
            // grow: if capacity == 0, make it 1; else double
            size_type newCap = (_capacity == 0) ? 1 : (_capacity * 2);
            reserve(newCap);
        }
        new (_data + _size) T(value);
        ++_size;
    }

    void push_back(T&& value) {
        if (_size == _capacity) {
            size_type newCap = (_capacity == 0) ? 1 : (_capacity * 2);
            reserve(newCap);
        }
        new (_data + _size) T(std::move(value));
        ++_size;
    }

    void pop_back() {
        if (_size == 0) 
            return;
        --_size;
        _data[_size].~T();
    }

    // ─────────────── Utilities ───────────────
    void swap(MyVector& other) noexcept {
        std::swap(_data, other._data);
        std::swap(_size, other._size);
        std::swap(_capacity, other._capacity);
    }

private:
    T*      _data;
    size_t  _size;
    size_t  _capacity;
};

#endif // MYVECTOR_HPP

