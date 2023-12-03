#include <gctest/core/gctest.hpp>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

GCTEST_CASE(test_full_structor)
{
    gctest_case_priority(test_full_structor, 0);
    gctest_case_name("full test structor");
    gctest_case_description("all macros and functions implemented");

    gctest_before_sleep_in_second(1);
    gctest_after_sleep_in_second(1);

    int *ptr = nullptr;

    gctest_before
    {
        ptr = new int{};
        *ptr = 5;
    }

    gctest_now
    {
        assert_equal(5, *ptr);
    }

    gctest_after
    {
        delete ptr;
    }
    
};