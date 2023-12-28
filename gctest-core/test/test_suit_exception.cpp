#include <gctest/core/test.hpp>
#include <gctest/core/exception.hpp>

#include <atomic>
#include <exception>

extern std::atomic_uint32_t unsuccessfulTestCases;

GCTEST_CASE(test_exception_1)
{
    gctest_case_config_priority(test_exception_1, 101);
    gctest_case_description("testing test_exception_1");
    gctest_case_requirement("gctest should handle first test exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw gctest::core::exception::TestCaseException("test exception");
    }
};

GCTEST_CASE(test_exception_2)
{
    gctest_case_config_priority(test_exception_2, 102);
    gctest_case_description("testing test_exception_2");
    gctest_case_requirement("gctest should handle second test exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw gctest::core::exception::TestCaseException("test exception");
    }
};

GCTEST_CASE(standard_exception_1)
{
    gctest_case_config_priority(standard_exception_1, 103);
    gctest_case_description("testing standard_exception_1");
    gctest_case_requirement("gctest should handle first standard exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw std::invalid_argument("invalid argument");
    }
};

GCTEST_CASE(standard_exception_2)
{
    gctest_case_config_priority(standard_exception_2, 104);
    gctest_case_description("testing standard_exception_2");
    gctest_case_requirement("gctest should handle second standard exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw std::runtime_error("runtime error");
    }
};

GCTEST_CASE(generic_exception_1)
{
    gctest_case_config_priority(generic_exception_1, 105);
    gctest_case_description("testing generic_exception_1");
    gctest_case_requirement("gctest should handle first generic exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw 1;
    }
};

GCTEST_CASE(generic_exception_2)
{
    gctest_case_config_priority(generic_exception_2, 106);
    gctest_case_description("testing generic_exception_2");
    gctest_case_requirement("gctest should handle second generic exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        throw "hello world";
    }
};