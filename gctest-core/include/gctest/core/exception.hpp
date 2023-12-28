#ifndef GCTEST_CORE_EXCEPTION_HPP
#define GCTEST_CORE_EXCEPTION_HPP

#include <exception>
#include <string>

namespace gctest
{
    namespace core
    {
        namespace exception
        {
            class TestCaseException final : public std::exception
            {
            private:
                std::string __message;

            public:
                TestCaseException(std::string &&message) : __message(std::move(message))
                {
                }
                ~TestCaseException() = default;

                const char *what() const noexcept override
                {
                    return __message.c_str();
                }
            };

            class TestSuitException final : public std::exception
            {
            private:
                std::string __message;

            public:
                TestSuitException(std::string &&message) : __message(std::move(message))
                {
                }
                ~TestSuitException() = default;

                const char *what() const noexcept override
                {
                    return __message.c_str();
                }
            };
        }

    }

}

#endif