#include <gctest/core/gctest.hpp>

#include <csignal>
#include <exception>
#include <stdexcept>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

FUNCTION_TEST(function_test_101, 101)
{
    unsuccessfulTestCase++;

    throw std::invalid_argument("std exception");
}

FUNCTION_TEST(function_test_102, 102)
{
    unsuccessfulTestCase++;

    throw 1;
}