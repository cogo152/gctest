#ifndef GTEST_EXECUTOR_HPP
#define GTEST_EXECUTOR_HPP

#include <gctest/core/gctest_type.hpp>

// resolve include problems
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

#include <vector>
#include <map>

#include <csetjmp>
#include <signal.h>
#include <thread>

#include <cmath>

namespace gctest
{
    namespace executor
    {
        class TestCaseExecutor final
        {
        private:
            static std::map<std::thread::id, std::jmp_buf *> __jumpBuffers;
            static void __signal_handler(int signalNumber);

            bool __isMultithreaded;

            const static std::size_t __capacityVector;
            std::vector<gctest::type::TestCase *> __testCases;
            std::size_t __totalFailedTests;
            std::size_t __totalSuccessfulTests;

            std::vector<std::thread> __executors;
            void __execute_test_case(const std::size_t begin, const std::size_t end);

        public:
            TestCaseExecutor();
            ~TestCaseExecutor();

            void set_multithreaded(std::uint32_t isMultiThreaded);

            void add_test_case(gctest::type::TestCase *testCase);
            void execute_test_cases();

            std::size_t get_total_tests() const;
            std::size_t get_total_failed_tests() const;
            std::size_t get_total_successful_tests() const;

            void print_test_report();
        };

        extern TestCaseExecutor *testCaseExecutor;
    }

}

#endif