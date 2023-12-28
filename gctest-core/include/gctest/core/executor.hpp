#ifndef GTEST_CORE_EXECUTOR_HPP
#define GTEST_CORE_EXECUTOR_HPP

#include <gctest/core/type.hpp>

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

#include <stdio.h>
#include <chrono>

namespace gctest
{
    namespace core
    {

        namespace executor
        {
            typedef void (*command_t)(void);

            class TestSuitExecutor final
            {
            private:
                static std::map<std::thread::id, std::jmp_buf *> __jumpBuffers;
                static void __signal_handler(int signalNumber);

                std::string __testSuitName;
                bool __isTestSuitExecutionMultithreaded;

                std::vector<command_t> __testSuitStartCommands;
                std::vector<command_t> __testSuitStopCommands;

                const static std::size_t __testCasesCapacity;
                std::vector<gctest::core::type::TestCase *> __testCases;
                std::size_t __totalSuccessfulTestCases;
                std::size_t __totalFailedTestCases;

                std::vector<std::thread> __testCaseExecutors;
                void __execute_test_case(const std::size_t begin, const std::size_t end);
                void __execute_test_cases(void);

                volatile bool __isSuitFailCalled;

                void __print_test_suit_report();

            public:
                TestSuitExecutor();
                ~TestSuitExecutor();

                void set_test_suit_name(std::string testSuitName);
                void set_test_suit_execution_multithreaded(std::uint32_t isTestSuitExecutionMultiThreaded);

                void add_test_suit_start_command(command_t command);
                void add_test_suit_stop_command(command_t command);

                void add_test_case(gctest::core::type::TestCase *testCase);

                std::size_t get_total_test_cases() const;
                std::size_t get_total_failed_test_cases() const;
                std::size_t get_total_successful_test_cases() const;

                void execute_test_suit();
            };

            extern TestSuitExecutor *testSuitExecutor;
        }

    }

}

#endif