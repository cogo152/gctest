#include <gctest/core/gctest.hpp>

#include <string>

using namespace gctest::assertion;

FUNCTION_TEST(function_test_301, 301)
{
    assert_true(true);
}

FUNCTION_TEST(function_test_302, 302)
{
    assert_false(false);
}

FUNCTION_TEST(function_test_303, 303)
{
    assert_true(1 + 1 == 2);
}

FUNCTION_TEST(function_test_304, 304)
{
    assert_false(1 + 1 == 3);
}

FUNCTION_TEST(function_test_305, 305)
{
    assert_equal(0, 0);
}

FUNCTION_TEST(function_test_306, 306)
{
    assert_equal(std::string("ab"), std::string("ab"));
}

FUNCTION_TEST(function_test_307, 307)
{
    assert_equal("ab", "ab");
}

FUNCTION_TEST(function_test_308, 308)
{
    assert_not_equal(0, 1);
}

FUNCTION_TEST(function_test_309, 309)
{
    assert_not_equal(std::string("ab"), std::string("ac"));
}

FUNCTION_TEST(function_test_310, 310)
{
    assert_not_equal("ac", "ad");
}

FUNCTION_TEST(function_test_311, 311)
{
    assert_greater(3, 2);
}

FUNCTION_TEST(function_test_312, 312)
{
    assert_greater_or_equal(2, 2);
}

FUNCTION_TEST(function_test_313, 313)
{
    assert_lesser(2, 3);
}

FUNCTION_TEST(function_test_314, 314)
{
    assert_lesser_or_equal(2, 2);
}