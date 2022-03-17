// smart_pointers.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cassert>
#include <iostream>
#include "smart_pointers.h"


class TestSmartPointer
{
public:
    // test a few types
    static void testTypes()
    {
        {
            SmartPointer<int> sp{};
            assert(!sp);  // default nullptr
        }

        { // int
            SmartPointer<int> sp{ new int(5) };
            assert(*sp == 5);
        }

        { // std::string
            SmartPointer<std::string> sp{ new std::string{ "Hello World!"} };
            assert(*sp == "Hello World!");
        }

        { // char
            SmartPointer<char> sp{ new char { 'a' } };
            assert(*sp == 'a');
        }
    }

    // test uniqueness property
    static void testUnique()
    {
        SmartPointer<int> sp1{ new int(5) };
        assert(*sp1 == 5);

        SmartPointer<int> sp2 = std::move(sp1);  // transfer ownership
        assert(!sp1);  // sp1 set to nullptr
        assert(*sp2 == 5);
    }

};


int main()
{

    TestSmartPointer::testTypes();
    TestSmartPointer::testUnique();

	int* temp = new int(5);
	{
		SmartPointer<int> sp{ temp };
		std::cout << *temp << '\n';
		std::cout << sp << '\n';
	}
	std::cout << *temp << '\n';


 
    return 0;
}

