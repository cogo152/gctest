#ifndef GCTEST_CORE_ASSERTION_HPP
#define GCTEST_CORE_ASSERTION_HPP

#include <gctest/core/exception.hpp>

#include <sstream>

#ifndef __SOURCE_LOCATION_IMPL__
#include <source_location>
#else
#include <gctest/core/source_location.hpp>
#endif

namespace gctest
{
    namespace core
    {
        namespace assertion
        {
            template <typename Type>
            void assert_true(const std::source_location &sourceLocation, Type actualValue)
            {
                if (actualValue == false)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "false"
                           << " <assert_true> "
                           << "Expected value = "
                           << "true"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_false(const std::source_location &sourceLocation, Type actualValue)
            {
                if (actualValue == true)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "true"
                           << " <assert_false> "
                           << "Expected value = "
                           << "false"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_equal(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if constexpr (std::is_same_v<const char *, Type>)
                {
                    std::string _actualValue(actualValue);
                    std::string _expectedValue(expectedValue);

                    if (_actualValue != _expectedValue)
                    {
                        std::stringstream stream;
                        stream << "Assertion\t: Actual value = " << _actualValue
                               << " <assert_equal> "
                               << "Expected value = " << _expectedValue
                               << "," << std::endl
                               << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                               << "\t\tLine\t\t: " << sourceLocation.line();

                        throw gctest::core::exception::TestException(stream.str());
                    }
                }
                else if (actualValue != expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_equal> "
                           << "Expected value = " << expectedValue
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_not_equal(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if constexpr (std::is_same_v<const char *, Type>)
                {
                    std::string _actualValue(actualValue);
                    std::string _expectedValue(expectedValue);

                    if (_actualValue == _expectedValue)
                    {
                        std::stringstream stream;
                        stream << "Assertion\t: Actual value = " << _actualValue
                               << " <assert_not_equal> "
                               << "Expected value = " << _expectedValue << "," << std::endl
                               << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                               << "\t\tLine\t\t: " << sourceLocation.line();

                        throw gctest::core::exception::TestException(stream.str());
                    }
                }
                else if (actualValue == expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_not_equal> "
                           << "Expected value = " << expectedValue << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_greater(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if (actualValue <= expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_greater> "
                           << "Expected value = " << expectedValue << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_greater_or_equal(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if (actualValue < expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_greater_or_equal> "
                           << "Expected value = " << expectedValue << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_lesser(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if (actualValue >= expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_lesser> "
                           << "Expected value = " << expectedValue << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Type>
            void assert_lesser_or_equal(const std::source_location &sourceLocation, Type actualValue, Type expectedValue)
            {
                if (actualValue > expectedValue)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = " << actualValue
                           << " <assert_lesser_or_equal> "
                           << "Expected value = " << expectedValue << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Function, typename... FunctionParameters>
            void assert_nonmember_throws(const std::source_location &sourceLocation, Function function, FunctionParameters... functionParameters)
            {
                bool exceptionNotOccurred = true;

                try
                {
                    function(functionParameters...);
                }
                catch (...)
                {
                    exceptionNotOccurred = false;
                }

                if (exceptionNotOccurred)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "Exception not occurred"
                           << " <assert_nonmember_throws> "
                           << "Expected value = "
                           << "Exception occurred"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Function, typename... FunctionParameters>
            void assert_nonmember_not_throws(const std::source_location &sourceLocation, Function function, FunctionParameters... functionParameters)
            {
                bool exceptionOccurred = false;

                try
                {
                    function(functionParameters...);
                }
                catch (...)
                {
                    exceptionOccurred = true;
                }

                if (exceptionOccurred)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "Exception occurred"
                           << " <assert_nonmember_not_throws> "
                           << "Expected value = "
                           << "Exception not occurred"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Instance, typename Function, typename... FunctionParameters>
            void assert_member_throws(const std::source_location &sourceLocation, Instance instance, Function function, FunctionParameters... functionParameters)
            {
                bool exceptionNotOccured = true;

                try
                {
                    (instance->*function)(functionParameters...);
                }
                catch (...)
                {
                    exceptionNotOccured = false;
                }

                if (exceptionNotOccured)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "Exception not ocurred"
                           << " <assert_member_throws> "
                           << "Expected value = "
                           << "Exception ocurred"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

            template <typename Instance, typename Function, typename... FunctionParameters>
            void assert_member_not_throws(const std::source_location &sourceLocation, Instance instance, Function function, FunctionParameters... functionParameters)
            {
                bool exceptionOccurred = false;

                try
                {
                    (instance->*function)(functionParameters...);
                }
                catch (...)
                {
                    exceptionOccurred = true;
                }

                if (exceptionOccurred)
                {
                    std::stringstream stream;
                    stream << "Assertion\t: Actual value = "
                           << "Exception ocurred"
                           << " <assert_member_not_throws> "
                           << "Expected value = "
                           << "Exception not ocurred"
                           << "," << std::endl
                           << "\t\tFile\t\t: " << sourceLocation.file_name() << "," << std::endl
                           << "\t\tLine\t\t: " << sourceLocation.line();

                    throw gctest::core::exception::TestException(stream.str());
                }
            }

        }

    }

}

#endif