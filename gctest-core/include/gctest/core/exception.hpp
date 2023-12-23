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
            class TestException final : public std::exception
            {
            private:
                std::string __message;

            public:
                TestException(std::string &&message);
                ~TestException() = default;

                virtual const char *what() const noexcept override;
            };
        }
    }

}

#endif