#include <gctest/core/test.hpp>

#include <atomic>

extern std::atomic_uint32_t unsuccessfulTestCases;
extern std::atomic_uint32_t incompleteTestCases;

GCTEST_CASE(fail_when_case_fail)
{
    gctest_case_config_default(fail_when_case_fail);
    gctest_case_description("testing fail_when_case_fail)");
    gctest_case_requirement("gctest should fail in case_fail status");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        case_fail;
    }
};

GCTEST_CASE(fail_when_suit_fail)
{
    gctest_case_config_default(fail_when_suit_fail); // must be before last
    gctest_case_description("testing fail_when_suit_fail)");
    gctest_case_requirement("gctest suit should fail in suit_fail status");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        suit_fail;
    }
};

GCTEST_CASE(default_priority)
{
    gctest_case_config_default(default_priority); // must be the last and not completed
    gctest_case_description("testing default_priority");
    gctest_case_requirement("testing default priority");

    gctest_case_now
    {
        incompleteTestCases--;

        assert_equal(5, 5);
    }
};