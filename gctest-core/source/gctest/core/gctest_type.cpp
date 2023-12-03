#include <gctest/core/gctest_type.hpp>

#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <iostream>

namespace gctest
{
    namespace type
    {
        TestCase::TestCase() : __testCaseName(),
                               __testCaseDescription(),
                               __sleepBeforeTestInNanoSecond(0),
                               __sleepAfterTestInNanoSecond(0),
                               __testCaseResult("not completed"),
                               __isTestCaseFailed(false),
                               __testCaseFailedDescription(),
                               __testReport()

        {
        }

        TestCase::~TestCase()
        {
        }

        std::string TestCase::_set_test_case_name()
        {
            return "not defined";
        }

        std::string TestCase::_set_test_case_description()
        {
            return "not defined";
        }

        std::uint64_t TestCase::_set_sleep_time_before_test_in_nanosecond()
        {
            return 0;
        }

        std::uint64_t TestCase::_set_sleep_time_after_test_in_nanosecond()
        {
            return 0;
        }

        void TestCase::_before_test()
        {
        }

        void TestCase::_after_test()
        {
        }

        void TestCase::setup_test()
        {
            __testCaseName = _set_test_case_name();
            __testCaseDescription = _set_test_case_description();
            __sleepBeforeTestInNanoSecond = _set_sleep_time_before_test_in_nanosecond();
            __sleepAfterTestInNanoSecond = _set_sleep_time_after_test_in_nanosecond();
        }

        void TestCase::before_test()
        {
            _before_test();

            if (__sleepBeforeTestInNanoSecond > 0)
            {
                std::this_thread::sleep_for(std::chrono::nanoseconds(__sleepBeforeTestInNanoSecond));
            }
        }

        void TestCase::test()
        {
            _test();
        }

        void TestCase::set_test_successful()
        {
            __isTestCaseFailed = false;
            __testCaseResult = "successful";
        }

        void TestCase::set_test_failed(std::string testCaseFailedDescription)
        {
            __isTestCaseFailed = true;
            __testCaseResult = "failed";
            __testCaseFailedDescription = testCaseFailedDescription;
        }

        void TestCase::after_test()
        {
            if (__sleepAfterTestInNanoSecond > 0)
            {
                std::this_thread::sleep_for(std::chrono::nanoseconds(__sleepAfterTestInNanoSecond));
            }

            _after_test();
        }

        void TestCase::teardown_test()
        {
            std::stringstream testReport;
            testReport << "Test Case"
                       << " { "
                       << "Name : " << __testCaseName << " , "
                       << "Description : " << __testCaseDescription << " , "
                       << "Result : " << __testCaseResult;

            if (__isTestCaseFailed)
            {
                testReport << " , "
                           << "Failed Reason : " << __testCaseFailedDescription;
            }

            testReport << " } ";

            __testReport = testReport.str();
        }

        void TestCase::print_test_case()
        {
            std::cout << __testReport << std::endl;
        }

    }
}