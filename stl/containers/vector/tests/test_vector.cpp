#include "../include/MyVector.hpp"
#include <cassert>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <memory>
#include <iterator>

static void test_default_constructor() {
    MyVector<int> v;
    assert(v.empty());
    assert(v.size() == 0);
    assert(v.capacity() == 0);
    assert(v.begin() == v.end());
}

static void test_initial_capacity_constructor() {
    MyVector<int> v(10);
    assert(v.empty());
    assert(v.size() == 0);
    assert(v.capacity() >= 10);
    // push within capacity shouldn't reallocate
    size_t oldCap = v.capacity();
    for (int i = 0; i < 10; ++i) v.push_back(i);
    assert(v.capacity() == oldCap);
    assert(v.size() == 10);
    for (int i = 0; i < 10; ++i) assert(v[i] == i);
}

static void test_push_back_and_operator_index() {
    MyVector<int> v;
    for (int i = 0; i < 100; ++i) {
        v.push_back(i * 2);
        assert(v.back() == i * 2);
        assert(v.size() == static_cast<size_t>(i + 1));
        assert(v[i] == i * 2);
    }
}

static void test_at_and_out_of_range() {
    MyVector<int> v;
    v.push_back(1);
    v.push_back(2);
    assert(v.at(0) == 1);
    assert(v.at(1) == 2);
    bool caught = false;
    try {
        (void)v.at(2);
    } catch (const std::out_of_range&) {
        caught = true;
    }
    assert(caught);
}

static void test_front_back() {
    MyVector<std::string> v;
    v.push_back("first");
    v.push_back("second");
    assert(v.front() == "first");
    assert(v.back()  == "second");
}

static void test_pop_back_and_clear() {
    MyVector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.pop_back();
    assert(v.size() == 1 && v.back() == 10);
    v.pop_back();
    assert(v.empty());
    // pop on empty should do nothing
    v.pop_back();
    assert(v.empty());
    // test clear
    for (int i = 0; i < 5; ++i) v.push_back(i);
    assert(!v.empty());
    size_t cap = v.capacity();
    v.clear();
    assert(v.empty());
    // clear does not change capacity
    assert(v.capacity() == cap);
}

static void test_reserve_and_shrink_to_fit() {
    MyVector<int> v;
    v.reserve(50);
    assert(v.capacity() >= 50);
    size_t afterReserve = v.capacity();
    for (int i = 0; i < 30; ++i) v.push_back(i);
    assert(v.capacity() == afterReserve);
    v.shrink_to_fit();
    assert(v.capacity() == v.size());
    // shrink when empty
    v.clear();
    v.shrink_to_fit();
    assert(v.capacity() == 0 && v.empty());
}

static void test_copy_and_move_constructors_and_assignments() {
    MyVector<std::unique_ptr<int>> a;
    a.push_back(std::make_unique<int>(5));
    a.push_back(std::make_unique<int>(42));

    // Copy constructor (should deep-copy values)
    MyVector<std::unique_ptr<int>> b; 
    // Note: unique_ptr is non-copyable — so this actually tests that copy assignment is deleted.
    // Instead, test copy with copyable type:
    MyVector<std::string> s1;
    s1.push_back("A"); s1.push_back("B");
    MyVector<std::string> s2(s1);
    assert(s2.size() == s1.size());
    assert(s2[0] == "A" && s2[1] == "B");
    // modifying s2 does not affect s1
    s2[1] = "C";
    assert(s1[1] == "B" && s2[1] == "C");

    // Move constructor
    MyVector<std::string> s3(std::move(s2));
    assert(s3.size() == 2);
    assert(s2.size() == 0);

    // Copy assignment
    MyVector<std::string> s4;
    s4 = s1;
    assert(s4.size() == s1.size());
    assert(s4[0] == "A");

    // Move assignment
    MyVector<std::string> s5;
    s5 = std::move(s4);
    assert(s5.size() == 2);
    assert(s4.size() == 0);
}

static void test_swap() {
    MyVector<int> a, b;
    for (int i = 0; i < 5; ++i) a.push_back(i);
    for (int i = 100; i < 103; ++i) b.push_back(i);
    size_t capA = a.capacity(), capB = b.capacity();
    a.swap(b);
    assert(a.size() == 3 && b.size() == 5);
    assert(a.capacity() == capB && b.capacity() == capA);
    assert(a[0] == 100 && b[0] == 0);
}

static void test_iterators_and_algorithm_compatibility() {
    MyVector<int> v;
    for (int i = 10; i > 0; --i) v.push_back(i);
    // std::sort works on our random-access iterators
    std::sort(v.begin(), v.end());
    for (int i = 0; i < 10; ++i) assert(v[i] == i+1);

    // std::copy and std::distance
    MyVector<int> v2;
    std::copy(v.begin(), v.end(), std::back_inserter(v2));
    assert(v2.size() == v.size());
    assert(std::equal(v.begin(), v.end(), v2.begin()));
    assert(std::distance(v2.begin(), v2.end()) == static_cast<std::ptrdiff_t>(v2.size()));

    // random-access iterator arithmetic
    auto it = v.begin() + 5;
    assert(*it == 6);
    it -= 3;
    assert(*it == 3);
}

static void test_move_only_types() {
    MyVector<std::unique_ptr<int>> v;
    v.push_back(std::make_unique<int>(7));
    v.push_back(std::make_unique<int>(14));
    assert(*v[0] == 7 && *v[1] == 14);
    // test move push_back
    std::unique_ptr<int> p = std::make_unique<int>(99);
    v.push_back(std::move(p));
    assert(*v.back() == 99);
    assert(p == nullptr);
}

int main() {
    test_default_constructor();
    test_initial_capacity_constructor();
    test_push_back_and_operator_index();
    test_at_and_out_of_range();
    test_front_back();
    test_pop_back_and_clear();
    test_reserve_and_shrink_to_fit();
    test_copy_and_move_constructors_and_assignments();
    test_swap();
    test_iterators_and_algorithm_compatibility();
    test_move_only_types();

    std::cout << "All MyVector tests passed successfully!\n";
    return 0;
}

