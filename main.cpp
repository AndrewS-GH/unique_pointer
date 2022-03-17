// smart_pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <iostream>
#include "uniquePointer.h"


class TestUniquePointer
{
public:
    // test a few types
    static void testTypes()
    {
        {
            UniquePointer<int> up{};
            assert(up==nullptr);  // default nullptr
        }

        { // int
            UniquePointer<int> up{ new int(5) };
            assert(*up == 5);
        }

        { // std::string
            UniquePointer<std::string> up{ new std::string{ "Hello World!"} };
            assert(*up == "Hello World!");
        }

        { // char
            UniquePointer<char> up{ new char { 'a' } };
            assert(*up == 'a');
        }
    }


	static void testAssignment()
	{
        // deleted assignment with L-Value UniquePointer reference, test R-Value reference
		UniquePointer<int> up1{ new int(5) };
		UniquePointer<int> up2 = std::move(up1);
        assert(*up2 == 5);
	}

    static void testMoveConstructor()
    {
        // deleted Constructor with L-Value UniquePointer reference, test R-Value reference
        UniquePointer<int> up1{ new int(5) };
        UniquePointer<int> up2{ std::move(up1) };
        assert(*up2 == 5);
    }

    // test uniqueness property
    static void testUnique()
    {
        UniquePointer<int> up1{ new int(5) };
        assert(*up1 == 5);

        UniquePointer<int> up2{ std::move(up1) };  // transfer ownership
        assert(up1 == nullptr);  // up1 set to nullptr
        assert(*up2 == 5);
    }

    static void testOverloadedOps()
    {
        UniquePointer<int> up1{ new int(5) };
        UniquePointer<int> up2{ new int(5) };

        assert(up1 != up2); // not pointing to same memory location
        assert(up1 == up1); // same memory location

        // bool
        assert(up1);  // non nullptr evaluates as True

        up2 = std::move(up1);
        assert(!up1); // nullptr evaluates as false
    }
    
    static void testRelease()
    {
        UniquePointer<int> up{ new int(5) };
        int* memLocation = up.get();

        int* data = up.release();

        assert(*data == 5);
        assert(data == memLocation);
        assert(!up);
    }

    static void testReset()
    {
        UniquePointer<int> up{ new int(5) };
        int* memLocation = up.get();

        up.reset(new int(10));
        assert(up.get() != memLocation);
        assert(*up != 5);
    }

    static void testSwap()
    {
        UniquePointer<int> up1{ new int(5) };
        int* up1_OldLocation = up1.get();

        UniquePointer<int> up2{ new int(5) };
        int* up2_OldLocation = up2.get();

        up1.swap(up2);
        assert(up2.get() == up1_OldLocation);
        assert(up1.get() == up2_OldLocation);
    }

    static void testMakeUnique()
    {
        //auto up1 = make_unique(new int(5));
    }

};


int main()
{

    TestUniquePointer::testTypes();
    TestUniquePointer::testAssignment();
    TestUniquePointer::testMoveConstructor();
    TestUniquePointer::testUnique();
    TestUniquePointer::testOverloadedOps();
    TestUniquePointer::testRelease();
    TestUniquePointer::testReset();
    TestUniquePointer::testSwap();

    

 
    return 0;
}

