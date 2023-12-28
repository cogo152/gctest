#ifndef GCTEST_CORE_TYPE_HPP
#define GCTEST_CORE_TYPE_HPP

#include <string>

namespace gctest
{
    namespace core
    {
        namespace type
        {
            class TestCase
            {
            private:
                std::string __testCaseName;
                std::string __testCaseDescription;
                std::string __testCaseRequirement;

                std::uint64_t __sleepTimeBeforeTestCaseForNanoSecond;
                std::uint64_t __sleepTimeAfterTestCaseForNanoSecond;

                std::string __testCaseResult;
                bool __isTestCaseExecuted;
                bool __isTestCaseFailed;
                std::string __testCaseFailedDescription;

                std::string __testCaseReport;

            protected:
                virtual std::string _set_test_case_description();
                virtual std::string _set_test_case_requirement();
                virtual std::uint64_t _set_sleep_time_before_test_case_for_nanosecond();
                virtual std::uint64_t _set_sleep_time_after_test_case_for_nanosecond();
                virtual void _before_test_case();
                virtual void _test_case() = 0;
                virtual void _after_test_case();

            public:
                TestCase(std::string testCaseName);
                virtual ~TestCase();

                void setup_test_case();
                void before_test_case();
                void test_case();
                void set_test_case_successful();
                void set_test_case_failed(std::string testCaseFailedDescription);
                void after_test_case();
                void teardown_test_case();
                void print_test_case_report();
            };

        }

    }

}
#endif