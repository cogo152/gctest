#ifndef GTEST_REGISTERY_HPP
#define GTEST_REGISTERY_HPP

#include <gctest/core/gctest_type.hpp>

#include <cstddef>
#include <string>

namespace gctest
{
    namespace registery
    {
        struct FunctionTestInfo
        {
            gctest::type::function_test_t functionTest;
            std::string functionTestName;
            std::string functionTestResult;
        };

        class FunctionTestRegistery final
        {
        private:
            const static std::size_t _capacityVector;
            std::size_t _capacity;
            std::size_t _size;

            FunctionTestInfo *_functionTestInfos;

        public:
            FunctionTestRegistery();
            ~FunctionTestRegistery();

            std::size_t size() const;
            void add_step(gctest::type::function_test_t functionTest, std::string functionName);
            void add_result(std::size_t index, std::string functionTestResult);

            const FunctionTestInfo &get(std::size_t index) const;
        };

        extern FunctionTestRegistery *functionTestRegistery;
    }

}

#endif