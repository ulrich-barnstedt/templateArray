#include <gtest/gtest.h>
#include "../templateArray.hpp"

TEST(Basic, Length) {
    Array<int> testArray(10);
    EXPECT_EQ(testArray.length, 10);
}

TEST(Basic, SetterGetter) {
    Array<int> testArray(10);

    testArray[5] = 5;
    EXPECT_EQ(testArray[5], 5);
}

TEST(Basic, Equality) {
    Array<int> test(5);
    test[1] = 5;

    Array<int> test2(5);
    test2[1] = 5;

    EXPECT_TRUE(test == test2);
}



TEST(Functions, ForEach) {
    Array<int> test(2);
    test[0] = 5;
    test[1] = 10;

    test.forEach([&test] (int data, int index) {
        EXPECT_EQ(data, test[index]);
    });
}

TEST(Functions, MapSelf) {
    Array<int> test(2);
    test.mapSelf([] (int value, int index) {return 2;});

    Array<int> expected(2);
    expected.fill(2);

    EXPECT_TRUE(expected == test);
}

TEST(Functions, Map) {
    Array<int> test(2);
    Array<int> mapped = test.map([] (int value, int index) {return 2;});

    Array<int> expected(2);
    expected.fill(2);

    EXPECT_TRUE(expected == mapped);
}

TEST(Functions, Reduce) {
    Array<int> test(5);
    test.fill(1);

    int total = test.reduce<int>([] (int acc, int value, int idx) {
        return acc + value;
    }, 0);

    EXPECT_EQ(total, 5);
}

TEST(Functions, Some) {
    Array<int> test(5);
    test[3] = 70;

    EXPECT_TRUE(test.some([] (int value, int idx) {
        return value == 70;
    }));
}

TEST(Functions, Every) {
    Array<int> test(5);
    test.fill(70);

    EXPECT_TRUE(test.every([] (int value, int idx) {
        return value == 70;
    }));
}

TEST(Functions, Includes) {
    Array<int> test(5);
    test[3] = 70;

    EXPECT_TRUE(test.includes(70));
}

TEST(Functions, IndexOf) {
    Array<int> test(5);
    test[3] = 70;

    EXPECT_EQ(test.indexOf(70), 3);
}

TEST(Functions, FillStandard) {
    Array<int> expected(2);
    expected[0] = 10;
    expected[1] = 10;

    Array<int> test(2);
    test.fill(10);

    EXPECT_TRUE(test == expected);
}

TEST(Functions, FillFunction) {
    Array<int>expected(2);
    expected[0] = 1;
    expected[1] = 2;

    Array<int> generated(2);
    generated.fill([] (int idx) {return idx + 1;});

    EXPECT_TRUE(generated == expected);
}

TEST(Functions, Copy) {
    Array<int> expected(2);
    expected[0] = 10;
    expected[1] = 10;

    auto test = expected.copy();
    EXPECT_TRUE(test == expected);
}

//Functionality not implemented yet
/*
 TEST(Functions, SortSelf) {
    Array<int> expected(3);
    expected.fill([&expected] (int idx) {return expected.length - idx;});

    Array<int> generated(3);
    generated.fill([] (int idx) {return idx + 1;});
    generated.sortSelf([] (const int value, const int idx) {return -1;});

    EXPECT_TRUE(generated == expected);
}

TEST(Functions, Sort) {
    Array<int> expected(3);
    expected.fill([&expected] (int idx) {return expected.length - idx;});

    Array<int> source(3);
    source.fill([] (int idx) {return idx + 1;});
    auto sorted = source.sort([] (int value, int idx) {return -1;});

    EXPECT_TRUE(expected == sorted);
}
 */