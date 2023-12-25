#include <gctest/core/test.hpp>

GCTEST_CASE(full_test_case_structure)
{
    gctest_case_config_priority(full_test_case_structure, 0);
    gctest_case_description("testing full_test_case_structure");
    gctest_case_requirement("gctest should implement all test case structure");

    // gctest_case_sleep_before_second(10);
    gctest_case_sleep_after_second(10);

    int *ptr = nullptr;

    gctest_case_before
    {
        ptr = new int{};
        *ptr = 5;
    }

    gctest_case_now
    {
        assert_equal(5, *ptr);
    }

    gctest_case_after
    {
        delete ptr;
    }
};