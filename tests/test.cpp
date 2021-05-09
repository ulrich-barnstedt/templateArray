#include "../templateArray.hpp"
#include <cassert>
#include <iostream>

void testLeaks();
void testLength();
void testOperations();

int main () {
    testLeaks();
    testLength();
    testOperations();
}

void testLeaks() {
    //run over this with valgrind

    Array<int> *testArray = new Array<int>(100);
    delete testArray;
}

void testLength() {
    Array<int> *testArray = new Array<int>(10);
    assert(testArray->length == 10);

    delete testArray;
}

void testOperations() {
    //assign/get

    Array<int> *testArray = new Array<int>(1);

    (*testArray)[0] = 400;
    assert((*testArray)[0] == 400);

    delete testArray;

    //equality
    Array<int> *test = new Array<int>(5);
    (*test)[1] = 5;

    Array<int> *test2 = new Array<int>(5);
    (*test2)[1] = 5;

    assert(*test == *test2);
}