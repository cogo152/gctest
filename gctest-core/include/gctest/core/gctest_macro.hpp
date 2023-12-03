#ifndef GCTEST_MACRO_HPP
#define GCTEST_MACRO_HPP

#include <gctest/core/gctest_type.hpp>
#include <gctest/core/gctest_executor.hpp>

#include <string>

#define GCTEST_TRUE (1)
#define GCTEST_FALSE (0)

#define GCTEST_SUIT_NAME(suitName)                                    \
    void __attribute__((constructor(102))) set_suit_name()            \
    {                                                                 \
        gctest::executor::testCaseExecutor->set_suit_name(#suitName); \
    }

#define GCTEST_SUIT_MULTITHREADED(isMultiThreaded)                              \
    void __attribute__((constructor(103))) set_multithreaded()                  \
    {                                                                           \
        gctest::executor::testCaseExecutor->set_multithreaded(isMultiThreaded); \
    }

#define GCTEST_CASE(testCaseName) \
    class testCaseName final : public gctest::type::TestCase

#define gctest_case_config(testCaseName, testCasePriority)                                                 \
    static void __attribute__((constructor(200 + testCasePriority))) testCaseName_##testCasePriority(void) \
    {                                                                                                      \
        gctest::executor::testCaseExecutor->add_test_case(new testCaseName(#testCaseName));                \
    }                                                                                                      \
    testCaseName(std::string testCaseName) : gctest::type::TestCase(testCaseName)                          \
    {                                                                                                      \
    }                                                                                                      \
    ~testCaseName()                                                                                        \
    {                                                                                                      \
    }

#define gctest_case_description(testCaseDescription)          \
    virtual std::string _set_test_case_description() override \
    {                                                         \
        return #testCaseDescription;                          \
    }

#define gctest_case_sleep_before_nanosecond(sleepTime)                         \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return sleepTime;                                                      \
    }

#define gctest_case_sleep_after_nanosecond(sleepTime)                         \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return sleepTime;                                                     \
    }

#define gctest_case_sleep_before_microsecond(sleepTime)                        \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                 \
    }

#define gctest_case_sleep_after_microsecond(sleepTime)                        \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                \
    }

#define gctest_case_sleep_before_millisecond(sleepTime)                        \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);              \
    }

#define gctest_case_sleep_after_millisecond(sleepTime)                        \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);             \
    }

#define gctest_case_sleep_before_second(sleepTime)                             \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);           \
    }

#define gctest_case_sleep_after_second(sleepTime)                             \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);          \
    }

#define gctest_case_before \
    virtual void _before_test() override

#define gctest_case_now \
    virtual void _test() override

#define gctest_case_after \
    virtual void _after_test() override

#endif
