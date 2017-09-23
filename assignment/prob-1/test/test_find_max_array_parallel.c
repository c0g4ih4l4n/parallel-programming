#include <stddef.h>
#include "../src/find_max_array_parallel.h"
#include "vendor/unity.h"
#include <stdlib.h>

void test_find_max_array_size_100(void)
{
    int * a, size;
    size = 100;
    a = (int *) malloc (size * sizeof(int));

    init (a, size);
    int expected = find_max_sequence (a, size);
    int actual = find_max_parallel(a, size);
    TEST_ASSERT_EQUAL_INT (expected, actual);
}

void test_find_max_array_size_1M (void)
{
    int * a, size;
    size = 1000000;
    a = (int *) malloc (size * sizeof(int));

    init (a, size);
    int expected = find_max_sequence(a, size);
    int actual = find_max_parallel(a, size);
    TEST_ASSERT_EQUAL_INT (expected, actual);
}

int main(void) 
{
    UnityBegin("test/test_find_max_array_parallel.c");

    RUN_TEST(test_find_max_array_size_100);
    RUN_TEST(test_find_max_array_size_1M);
    
    UnityEnd();
    return 0;
}
