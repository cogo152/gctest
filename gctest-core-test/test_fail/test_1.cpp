#include <gctest/core/gctest.hpp>

using namespace gctest::assertion;

FUNCTION_TEST(function_test_10, 10)
{
    int *ptr = nullptr;
    *ptr = 1;
}

FUNCTION_TEST(function_test_11, 11)
{
    assert_equal(0, 1);
}

FUNCTION_TEST(function_test_12, 12)
{
    throw std::invalid_argument("std exception");
}

FUNCTION_TEST(function_test_13, 13)
{
    throw 1;
}
