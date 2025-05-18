#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "sorting.h"

#define TEST_SIZE 10

static Student test_students[TEST_SIZE];

static void setup_test_data(void** state) {
    test_students[0] = create_student("Alice", 85, 90, 95);
    test_students[1] = create_student("Bob", 75, 80, 85);
    test_students[2] = create_student("Charlie", 95, 85, 90);
    test_students[3] = create_student("David", 65, 70, 75);
    test_students[4] = create_student("Eve", 90, 95, 85);
    test_students[5] = create_student("Frank", 80, 75, 70);
    test_students[6] = create_student("Grace", 70, 65, 80);
    test_students[7] = create_student("Hank", 60, 70, 65);
    test_students[8] = create_student("Ivy", 55, 60, 65);
    test_students[9] = create_student("Jack", 50, 55, 60);
}

static void test_insertion_sort_by_total(void** state) {
    Student copy[TEST_SIZE];
    memcpy(copy, test_students, sizeof(test_students));
    
    insertion_sort(copy, TEST_SIZE, compare_by_total);
    
    for (size_t i = 1; i < TEST_SIZE; i++) {
        assert_true(copy[i-1].total_score >= copy[i].total_score);
    }
}

static void test_quick_sort_by_physics(void** state) {
    Student copy[TEST_SIZE];
    memcpy(copy, test_students, sizeof(test_students));
    
    quick_sort(copy, TEST_SIZE, compare_by_physics);
    
    for (size_t i = 1; i < TEST_SIZE; i++) {
        assert_true(copy[i-1].phys_score >= copy[i].phys_score);
    }
}

static void test_counting_sort(void** state) {
    Student copy[TEST_SIZE];
    memcpy(copy, test_students, sizeof(test_students));
    
    counting_sort(copy, TEST_SIZE);
    
    for (size_t i = 1; i < TEST_SIZE; i++) {
        assert_true(copy[i-1].total_score >= copy[i].total_score);
    }
}

static void test_bogo_sort_small(void** state) {
    Student small_copy[3];
    memcpy(small_copy, test_students, sizeof(Student) * 3);
    
    bogo_sort(small_copy, 3, compare_by_total);
    
    for (size_t i = 1; i < 3; i++) {
        assert_true(small_copy[i-1].total_score >= small_copy[i].total_score);
    }
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup(test_insertion_sort_by_total, setup_test_data),
        cmocka_unit_test_setup(test_quick_sort_by_physics, setup_test_data),
        cmocka_unit_test_setup(test_counting_sort, setup_test_data),
        cmocka_unit_test_setup(test_bogo_sort_small, setup_test_data),
    };
    
    return cmocka_run_group_tests(tests, NULL, NULL);
}