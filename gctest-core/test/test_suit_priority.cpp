#include <gctest/core/test.hpp>

GCTEST_CASE(default_priority)
{
    gctest_case_config_default(default_priority);
    gctest_case_description("testing default_priority");
    gctest_case_requirement("testing default priority");

    gctest_case_now
    {
        assert_equal(5, 5);
    }
};