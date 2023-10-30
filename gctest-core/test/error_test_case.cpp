#include <gctest/core/gctest.hpp>

#include <csignal>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

FUNCTION_TEST(function_test_1, 1)
{
    unsuccessfulTestCase++;

    std::raise(SIGSEGV);
}

FUNCTION_TEST(function_test_2, 2)
{
    unsuccessfulTestCase++;

    int *ptr = nullptr;
    *ptr = 1;
}

FUNCTION_TEST(function_test_3, 3)
{
    unsuccessfulTestCase++;

    std::raise(SIGFPE);
}

FUNCTION_TEST(function_test_4, 4)
{
    unsuccessfulTestCase++;

    int a = 1 / 0;
}
