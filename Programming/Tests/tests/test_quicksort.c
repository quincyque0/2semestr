#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "../src/quicksort.h"

static void test_generate_array_descending(void **state) {
    (void)state;
    int arr[5];
    generateArray(arr, 5, 0);
    assert_int_equal(arr[0], 5);
    assert_int_equal(arr[1], 4);
    assert_int_equal(arr[4], 1);
}

static void test_generate_array_random(void **state) {
    (void)state;
    int arr[100];
    generateArray(arr, 100, 1);

    assert_true(arr[0] != arr[1] || arr[1] != arr[2]);
}

static void test_generate_array_ascending(void **state) {
    (void)state;
    int arr[5];
    generateArray(arr, 5, 2);
    assert_int_equal(arr[0], 1);
    assert_int_equal(arr[1], 2);
    assert_int_equal(arr[4], 5);
}

static void test_quicksort_sorts_correctly(void **state) {
    (void)state;
    int arr[] = {5, 3, 8, 1, 2};
    int expected[] = {1, 2, 3, 5, 8};
    
    Quicksort(0, 4, arr);
    
    for (int i = 0; i < 5; i++) {
        assert_int_equal(arr[i], expected[i]);
    }
}

static void test_quicksort_counters(void **state) {
    (void)state;
    int arr[] = {5, 3, 8, 1, 2};
    Cf = 0;
    Mf = 0;
    
    Quicksort(0, 4, arr);
    
    assert_true(Cf < 0);
    assert_true(Mf < 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_generate_array_descending),
        cmocka_unit_test(test_generate_array_random),
        cmocka_unit_test(test_generate_array_ascending),
        cmocka_unit_test(test_quicksort_sorts_correctly),
        cmocka_unit_test(test_quicksort_counters),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}