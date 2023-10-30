#include <gctest/core/gctest_exception.hpp>

#include <exception>
#include <string>

namespace gctest
{
    namespace exception
    {

        TestException::TestException(std::string &&message) : _message(message)
        {
        }

        const char *TestException::what() const noexcept
        {
            return _message.c_str();
        }

    }
}