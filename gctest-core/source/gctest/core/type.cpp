#include <gctest/core/type.hpp>

#include <string>
#include <sstream>
#include <chrono>
#include <thread>
#include <iostream>

namespace gctest
{
    namespace core
    {
        namespace type
        {
            TestCase::TestCase(std::string testCaseName) : __testCaseName(testCaseName),
                                                           __testCaseResult("not completed"),
                                                           __isTestCaseFailed(false)

            {
            }

            TestCase::~TestCase()
            {
            }

            std::string TestCase::_set_test_case_description()
            {
                return "not defined";
            }

            std::string TestCase::_set_test_case_requirement()
            {
                return "not defined";
            }

            std::uint64_t TestCase::_set_sleep_time_before_test_case_for_nanosecond()
            {
                return 0;
            }

            std::uint64_t TestCase::_set_sleep_time_after_test_case_for_nanosecond()
            {
                return 0;
            }

            void TestCase::_before_test_case()
            {
            }

            void TestCase::_after_test_case()
            {
            }

            void TestCase::setup_test_case()
            {
                __testCaseDescription = _set_test_case_description();
                __testCaseRequirement = _set_test_case_requirement();
                __sleepTimeBeforeTestCaseForNanoSecond = _set_sleep_time_before_test_case_for_nanosecond();
                __sleepTimeAfterTestCaseForNanoSecond = _set_sleep_time_after_test_case_for_nanosecond();
            }

            void TestCase::before_test_case()
            {
                _before_test_case();

                if (__sleepTimeBeforeTestCaseForNanoSecond > 0)
                {
                    std::this_thread::sleep_for(std::chrono::nanoseconds(__sleepTimeBeforeTestCaseForNanoSecond));
                }
            }

            void TestCase::test_case()
            {
                _test_case();
            }

            void TestCase::set_test_case_successful()
            {
                __isTestCaseFailed = false;
                __testCaseResult = "successful";
            }

            void TestCase::set_test_case_failed(std::string testCaseFailedDescription)
            {
                __isTestCaseFailed = true;
                __testCaseResult = "failed";
                __testCaseFailedDescription = testCaseFailedDescription;
            }

            void TestCase::after_test_case()
            {
                if (__sleepTimeAfterTestCaseForNanoSecond > 0)
                {
                    std::this_thread::sleep_for(std::chrono::nanoseconds(__sleepTimeAfterTestCaseForNanoSecond));
                }

                _after_test_case();
            }

            void TestCase::teardown_test_case()
            {
                std::stringstream testCaseReport;
                testCaseReport << "Test Case"
                               << std::endl
                               << "{"
                               << std::endl
                               << "\tName\t\t: " << __testCaseName << "," << std::endl
                               << "\tDescription\t: " << __testCaseDescription << "," << std::endl
                               << "\tRequirement\t: " << __testCaseRequirement << "," << std::endl
                               << "\tResult\t\t: " << __testCaseResult;

                if (__isTestCaseFailed)
                {
                    testCaseReport << std::endl
                                   << "\tFailed Description"
                                   << std::endl
                                   << "\t{"
                                   << std::endl
                                   << __testCaseFailedDescription
                                   << std::endl
                                   << "\t}";
                }

                testCaseReport << std::endl
                               << "}";

                __testCaseReport = testCaseReport.str();
            }

            void TestCase::print_test_case_report()
            {
                std::cout << __testCaseReport << std::endl;
            }

        }
    }

}