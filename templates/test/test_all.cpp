#include <iostream>
#include <cassert>
#include <string>
#include <utility>        // for std::move
#include <stdexcept>      // for std::underflow_error

#include "../include/max_min.hpp"
#include "../include/Stack.hpp"
#include "../include/Pair.hpp"
#include "../include/bubble_sort.hpp"
#include "../include/char_ptr_compare.hpp"

void test_max_min() {
    // int
    assert(max(3, 5) == 5);
    assert(min(3, 5) == 3);
    // double
    assert(max(2.5, -1.0) == 2.5);
    assert(min(2.5, -1.0) == -1.0);
}

void test_stack() {
    Stack<int> s;
    assert(s.empty());
    s.push(10);
    assert(!s.empty() && s.size() == 1 && s.top() == 10);
    s.push(20);
    assert(s.size() == 2 && s.top() == 20);
    s.pop();
    assert(s.size() == 1 && s.top() == 10);
    s.pop();
    assert(s.empty());
    // popping empty should throw
    try {
        s.pop();
        assert(false && "Expected exception when popping empty stack");
    } catch (const std::underflow_error&) {
        // OK
    }
    // copy constructor
    s.push(1); s.push(2); s.push(3);
    Stack<int> s2 = s;
    assert(s2.size() == s.size() && s2.top() == s.top());
    // move constructor
    Stack<int> s3 = std::move(s2);
    assert(s3.size() == 3);
    assert(s2.empty());  // moved-from should be empty
}

void test_pair() {
    Pair<int, std::string> p(5, "test");
    assert(p.first == 5);
    assert(p.second == "test");
    Pair<int, std::string> q;
    q = p;
    assert(q == p);
    Pair<int, std::string> r(1, "x");
    assert(r != p);
}

void test_bubble_sort() {
    // ints
    int arr[] = {5, 1, 4, 2, 3};
    bubble_sort(arr, 5);
    for (int i = 0; i < 5; ++i)
        assert(arr[i] == i + 1);

    // doubles
    double darr[] = {2.2, -1.1, 0.0};
    bubble_sort(darr, 3);
    assert(darr[0] == -1.1 && darr[1] ==  0.0 && darr[2] == 2.2);
}

void test_char_ptr_compare() {
    const char* a = "apple";
    const char* b = "banana";
    // banana > apple lexicographically
    assert(max<const char*>(a, b) == b);

    // null handling
    const char* c = nullptr;
    assert(max<const char*>(c, a) == a);
    assert(max<const char*>(c, c) == c);
}

int main() {
    test_max_min();
    test_stack();
    test_pair();
    test_bubble_sort();
    test_char_ptr_compare();

    std::cout << "All tests passed!\n";
    return 0;
}

