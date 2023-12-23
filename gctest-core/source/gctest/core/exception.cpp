#include <gctest/core/exception.hpp>

#include <utility>

namespace gctest
{
    namespace core
    {
        namespace exception
        {
            TestException::TestException(std::string &&message) : __message(std::move(message))
            {
            }

            const char *TestException::what() const noexcept
            {
                return __message.c_str();
            }

        }
    }

}