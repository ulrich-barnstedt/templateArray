#include "../templateArray.h"
#include <cassert>

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
    assert(testArray->getLength() == 10);

    delete testArray;
}

void testOperations() {
    Array<int> *testArray = new Array<int>(1);

    (*testArray)[0] = 400;
    assert((*testArray)[0] == 400);

    delete testArray;
}