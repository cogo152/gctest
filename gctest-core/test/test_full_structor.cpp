#include <gctest/core/gctest.hpp>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

GCTEST_CASE(full_case_structor)
{
    gctest_case_config(full_case_structor, 0);
    gctest_case_description("testing full test case structor");

    gctest_case_sleep_before_second(1);
    gctest_case_sleep_after_second(1);

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