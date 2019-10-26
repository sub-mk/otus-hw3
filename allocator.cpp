#include <iostream>

#include "lib.h"

// http://www.cyberforum.ru/cpp-beginners/thread439133.html

int main()
{
    auto map_basic = lib::create_map<lib::MapBasic>(10);
    lib::print_map(map_basic, "Basic map with factorial values");

    auto map_allocator = lib::create_map<lib::MapWithAlloc>(10);
    lib::print_map(map_allocator, "Map with custom allocator with factorial values");

    return 0;
}