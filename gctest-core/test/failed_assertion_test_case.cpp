#include <gctest/core/gctest.hpp>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

FUNCTION_TEST(function_test_201, 201)
{
    unsuccessfulTestCase++;

    assert_true(false);
}

FUNCTION_TEST(function_test_202, 202)
{
    unsuccessfulTestCase++;

    assert_false(true);
}

FUNCTION_TEST(function_test_203, 203)
{
    unsuccessfulTestCase++;

    assert_true(1 + 1 == 3);
}

FUNCTION_TEST(function_test_204, 204)
{
    unsuccessfulTestCase++;

    assert_false(1 + 1 == 2);
}

FUNCTION_TEST(function_test_205, 205)
{
    unsuccessfulTestCase++;

    assert_equal(0, 1);
}

FUNCTION_TEST(function_test_206, 206)
{
    unsuccessfulTestCase++;

    assert_equal(std::string("ab"), std::string("ac"));
}

FUNCTION_TEST(function_test_207, 207)
{
    unsuccessfulTestCase++;

    assert_equal("ab", "ac");
}

FUNCTION_TEST(function_test_208, 208)
{
    unsuccessfulTestCase++;

    assert_not_equal(0, 0);
}

FUNCTION_TEST(function_test_209, 209)
{
    unsuccessfulTestCase++;

    assert_not_equal(std::string("ab"), std::string("ab"));
}

FUNCTION_TEST(function_test_210, 210)
{
    unsuccessfulTestCase++;

    assert_not_equal("ac", "ac");
}

FUNCTION_TEST(function_test_211, 211)
{
    unsuccessfulTestCase++;

    assert_greater(2, 3);
}

FUNCTION_TEST(function_test_212, 212)
{
    unsuccessfulTestCase++;

    assert_greater_or_equal(2, 3);
}

FUNCTION_TEST(function_test_213, 213)
{
    unsuccessfulTestCase++;

    assert_lesser(3, 2);
}

FUNCTION_TEST(function_test_214, 214)
{
    unsuccessfulTestCase++;

    assert_lesser_or_equal(3, 2);
}
