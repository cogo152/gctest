#include <gctest/core/gctest.hpp>
#include <gctest/core/gctest_exception.hpp>

#include <exception>

extern int unsuccessfulTestCase;

GCTEST_CASE(test_exception_1)
{
    gctest_case_config(test_exception_1, 101);
    gctest_case_description("gctest should handle first test exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw gctest::exception::TestException("test exception");
    }
};

GCTEST_CASE(test_exception_2)
{
    gctest_case_config(test_exception_2, 102);
    gctest_case_description("gctest should handle second test exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw gctest::exception::TestException("test exception");
    }
};

GCTEST_CASE(standard_exception_1)
{
    gctest_case_config(standard_exception_1, 103);
    gctest_case_description("gctest should handle first standard exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw std::invalid_argument("invalid argument");
    }
};

GCTEST_CASE(standard_exception_2)
{
    gctest_case_config(standard_exception_2, 104);
    gctest_case_description("gctest should handle second standard exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw std::runtime_error("runtime error");
    }
};

GCTEST_CASE(generic_exception_1)
{
    gctest_case_config(generic_exception_1, 105);
    gctest_case_description("gctest should handle first generic exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw 1;
    }
};

GCTEST_CASE(generic_exception_2)
{
    gctest_case_config(generic_exception_2, 106);
    gctest_case_description("gctest should handle second generic exception without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;

        throw "hello world";
    }
};