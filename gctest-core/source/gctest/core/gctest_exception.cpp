#include <gctest/core/gctest_exception.hpp>

namespace gctest
{
    namespace exception
    {

        TestException::TestException(std::string &&message) : __message(message)
        {
        }

        const char *TestException::what() const noexcept
        {
            return __message.c_str();
        }

    }
}