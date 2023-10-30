#ifndef GCTEST_EXCEPTION_HPP
#define GCTEST_EXCEPTION_HPP

#include <exception>
#include <string>

namespace gctest
{
    namespace exception
    {
        class TestException final : public std::exception
        {
        private:
            std::string _message;

        public:
            TestException(std::string &&message);
            
            virtual const char *what() const noexcept override;
        };
    }
}

#endif