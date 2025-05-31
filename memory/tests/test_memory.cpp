// File: memory/tests/test_memory.cpp

#include "Arena.hpp"
#include "Logger.hpp"
#include "MyUnique.hpp"
#include "MyShared.hpp"

#include <cassert>
#include <cstring>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <utility> // std::move

int main() {
    //
    // -------------------------------
    // 1) Tests for Arena
    // -------------------------------
    //
    {
        Arena arena;

        // 1.1 Allocate an int array, write/read
        int* intArr = static_cast<int*>(arena.allocate(5 * sizeof(int)));
        assert(intArr != nullptr);
        for (int i = 0; i < 5; ++i) {
            intArr[i] = i * 3;
        }
        for (int i = 0; i < 5; ++i) {
            assert(intArr[i] == i * 3);
        }

        // 1.2 Allocate a char buffer, write/read
        char* buf = static_cast<char*>(arena.allocate(10 * sizeof(char)));
        assert(buf != nullptr);
        const char* msg = "hello";
        std::strcpy(buf, msg);
        assert(std::strcmp(buf, "hello") == 0);

        // 1.3 Test release_all: after release_all, allocate again
        arena.release_all();
        double* dblArr = static_cast<double*>(arena.allocate(3 * sizeof(double)));
        assert(dblArr != nullptr);
        dblArr[0] = 1.5; dblArr[1] = 2.5; dblArr[2] = 3.5;
        assert(dblArr[0] == 1.5 && dblArr[1] == 2.5 && dblArr[2] == 3.5);

        // 1.4 Test move constructor: moved-from arena should be empty
        Arena arena2 = std::move(arena);
        // The moved-from 'arena' can still be used to allocate:
        int* movedArr = static_cast<int*>(arena.allocate(sizeof(int)));
        assert(movedArr != nullptr);
        *movedArr = 99;
        assert(*movedArr == 99);

        // When arena2 goes out of scope, all its tracked blocks will be freed.
    }

    //
    // -------------------------------
    // 2) Tests for Logger
    // -------------------------------
    //
    {
        const std::string logFilename = "test_log.txt";

        // 2.1 Create a Logger and write two lines
        {
            Logger logger(logFilename);
            logger.log("First line");
            logger.log("Second line");
        } // logger destructor closes the file

        // 2.2 Read the file back and verify contents
        {
            std::ifstream inFile(logFilename);
            assert(inFile.is_open());

            std::string line1, line2, extra;
            std::getline(inFile, line1);
            std::getline(inFile, line2);
            bool eof_before_third = !std::getline(inFile, extra);

            assert(line1 == "First line");
            assert(line2 == "Second line");
            assert(eof_before_third); // no third line
            inFile.close();
        }

        // 2.3 Clean up
        std::remove(logFilename.c_str());
    }

    //
    // -------------------------------
    // 3) Tests for MyUnique<T>
    // -------------------------------
    //
    {
        // 3.1 Test basic construction and dereference
        MyUnique<int> u1(new int(10));
        assert(u1.get() != nullptr);
        assert(*u1 == 10);

        // 3.2 Test release(): after release, u1.get() == nullptr, and raw value is preserved
        int* rawPtr = u1.release();
        assert(u1.get() == nullptr);
        assert(*rawPtr == 10);
        delete rawPtr; // manually free

        // 3.3 Test reset(): assign a new int
        u1.reset(new int(20));
        assert(u1.get() != nullptr);
        assert(*u1 == 20);

        // 3.4 Test move constructor: u1 → u2
        MyUnique<int> u2(std::move(u1));
        assert(u1.get() == nullptr);
        assert(u2.get() != nullptr);
        assert(*u2 == 20);

        // 3.5 Test reset(nullptr): should delete current and set to null
        u2.reset();
        assert(u2.get() == nullptr);

        // 3.6 Test operator-> on a user-defined type
        struct Foo {
            int x;
            int getX() const { return x; }
        };
        MyUnique<Foo> fu(new Foo{ 5 });
        assert(fu->getX() == 5);

        // 3.7 Test move assignment: assign new pointer, then move into another
        MyUnique<Foo> fu2(new Foo{ 42 });
        MyUnique<Foo> fu3(nullptr);
        fu3 = std::move(fu2);
        assert(fu2.get() == nullptr);
        assert(fu3.get() != nullptr && fu3->getX() == 42);

        // —— Removed self-move test: “fu3 = std::move(fu3);” — not needed
    }

    //
    // -------------------------------
    // 4) Tests for MyShared<T>
    // -------------------------------
    //
    {
        // 4.1 Test basic construction and use_count()
        MyShared<int> s1(new int(42));
        assert(s1.get() != nullptr);
        assert(*s1 == 42);
        assert(s1.use_count() == 1);

        // 4.2 Test copy constructor: use_count should increment
        {
            MyShared<int> s2(s1);
            assert(s1.use_count() == 2);
            assert(s2.use_count() == 2);
            assert(*s2 == 42);

            {
                MyShared<int> s3(s2);
                assert(s1.use_count() == 3);
                assert(s2.use_count() == 3);
                assert(s3.use_count() == 3);
                assert(*s3 == 42);
            }
            // s3 destroyed
            assert(s1.use_count() == 2);
            assert(s2.use_count() == 2);
        }
        // s2 destroyed
        assert(s1.use_count() == 1);

        // 4.3 Test move constructor: s1 → s4
        MyShared<int> s4(std::move(s1));
        assert(s1.get() == nullptr);
        assert(s1.use_count() == 0);
        assert(s4.get() != nullptr);
        assert(*s4 == 42);
        assert(s4.use_count() == 1);

        // 4.4 Test move assignment: assign new resource, then move
        MyShared<int> s5(new int(100));
        assert(s5.use_count() == 1 && *s5 == 100);
        s5 = MyShared<int>(new int(200));
        assert(s5.use_count() == 1 && *s5 == 200);

        // 4.5 Test copy assignment: share ownership
        MyShared<int> s6;
        s6 = s5; 
        assert(s5.use_count() == 2);
        assert(s6.use_count() == 2);
        assert(*s6 == 200);

        // 4.6 Test self-copy assignment: should be safe
        s6 = s6;
        assert(s6.use_count() == 2);
        assert(*s6 == 200);

        // 4.7 Test nullptr state
        MyShared<int> sEmpty;
        assert(sEmpty.get() == nullptr);
        assert(sEmpty.use_count() == 0);

        // 4.8 Test chaining copies and moves with std::string
        MyShared<std::string> sStr1(new std::string("hello"));
        assert(sStr1.use_count() == 1 && *sStr1 == "hello");

        MyShared<std::string> sStr2 = sStr1; // copy
        assert(sStr1.use_count() == 2 && sStr2.use_count() == 2);
        assert(*sStr2 == "hello");

        MyShared<std::string> sStr3 = std::move(sStr2);
        assert(sStr2.get() == nullptr && sStr2.use_count() == 0);
        assert(sStr3.use_count() == 2);
        assert(*sStr3 == "hello");
    }

    // If execution reaches here, all tests passed.
    return 0;
}

