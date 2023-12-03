#include <gctest/core/gctest.hpp>

#include <exception>

extern int unsuccessfulTestCase;

GCTEST_CASE(test_standard_exception)
{
    gctest_case_priority(test_standard_exception, 100);
    gctest_case_name("catching standard exception");
    gctest_case_description("gctest should handle standart exception without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;

        throw std::invalid_argument("std exception");
    }
};

GCTEST_CASE(test_generic_exception_1)
{
    gctest_case_priority(test_generic_exception_1, 101);
    gctest_case_name("catching generic exception");
    gctest_case_description("gctest should handle generic exception without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;

        throw 1;
    }
};

GCTEST_CASE(test_generic_exception_2)
{
    gctest_case_priority(test_generic_exception_2, 102);
    gctest_case_name("catching generic exception");
    gctest_case_description("gctest should handle generic exception without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;

        throw "hello world";
    }
};