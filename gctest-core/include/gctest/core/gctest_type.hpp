#ifndef GCTEST_TYPE_HPP
#define GCTEST_TYPE_HPP

#include <string>

namespace gctest
{
    namespace type
    {

        class TestCase
        {
        private:
            std::string __testCaseName;
            std::string __testCaseDescription;

            std::uint64_t __sleepBeforeTestInNanoSecond;
            std::uint64_t __sleepAfterTestInNanoSecond;

            std::string __testCaseResult;
            bool __isTestCaseFailed;
            std::string __testCaseFailedDescription;

            std::string __testReport;

        protected:
            virtual std::string _set_test_case_name();
            virtual std::string _set_test_case_description();
            virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond();
            virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond();
            virtual void _before_test();
            virtual void _test() = 0;
            virtual void _after_test();

        public:
            TestCase();
            virtual ~TestCase();

            void setup_test();
            void before_test();
            void test();
            void set_test_successful();
            void set_test_failed(std::string testCaseFailedDescription);
            void after_test();
            void teardown_test();
            void print_test_case();
        };

    }

}

#endif