#ifndef GCTEST_ASSERTION_HPP
#define GCTEST_ASSERTION_HPP

#include <gctest/core/gctest_exception.hpp>

#include <sstream>

#include <iostream>

namespace gctest
{
    namespace assertion
    {
        template <typename Type>
        void assert_true(Type actual)
        {
            if (actual == false)
            {
                std::stringstream stream;
                stream << "Actual value = "
                       << "false"
                       << " <assert_true> "
                       << "Expected value = "
                       << "true";

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_false(Type actual)
        {
            if (actual == true)
            {
                std::stringstream stream;
                stream << "Actual value = "
                       << "true"
                       << " <assert_false> "
                       << "Expected value = "
                       << "false";

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_equal(Type actual, Type expected)
        {
            if constexpr (std::is_same_v<const char *, Type>)
            {
                std::string _actual(actual);
                std::string _expected(expected);

                if (_actual != _expected)
                {
                    std::stringstream stream;
                    stream << "Actual value = " << _actual
                           << " <assert_equal> "
                           << "Expected value = " << _expected;

                    throw gctest::exception::TestException(std::move(stream.str()));
                }
            }
            else if (actual != expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_equal> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_not_equal(Type actual, Type expected)
        {
            if constexpr (std::is_same_v<const char *, Type>)
            {
                std::string _actual(actual);
                std::string _expected(expected);

                if (_actual == _expected)
                {
                    std::stringstream stream;
                    stream << "Actual value = " << _actual
                           << " <assert_not_equal> "
                           << "Expected value = " << _expected;

                    throw gctest::exception::TestException(std::move(stream.str()));
                }
            }
            else if (actual == expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_not_equal> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_greater(Type actual, Type expected)
        {
            if (actual <= expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_greater> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_greater_or_equal(Type actual, Type expected)
        {
            if (actual < expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_greater_or_equal> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_lesser(Type actual, Type expected)
        {
            if (actual >= expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_lesser> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

        template <typename Type>
        void assert_lesser_or_equal(Type actual, Type expected)
        {
            if (actual > expected)
            {
                std::stringstream stream;
                stream << "Actual value = " << actual
                       << " <assert_lesser_or_equal> "
                       << "Expected value = " << expected;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }

    }

}

#endif