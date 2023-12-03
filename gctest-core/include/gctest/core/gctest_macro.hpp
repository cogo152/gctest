#ifndef GCTEST_MACRO_HPP
#define GCTEST_MACRO_HPP

#include <gctest/core/gctest_type.hpp>
#include <gctest/core/gctest_executor.hpp>

#include <string>

#define GCTEST_TRUE (1)
#define GCTEST_FALSE (0)

#define GCTEST_CONFIG_SET_MULTITHREADED(isMultiThreaded)                        \
    void __attribute__((constructor(102))) set_multithreaded()                  \
    {                                                                           \
        gctest::executor::testCaseExecutor->set_multithreaded(isMultiThreaded); \
    }

#define GCTEST_CASE(testCase) \
    class testCase final : public gctest::type::TestCase

#define gctest_case_priority(testCase, testPriority)                                           \
    static void __attribute__((constructor(200 + testPriority))) testCase_##testPriority(void) \
    {                                                                                          \
        gctest::executor::testCaseExecutor->add_test_case(new testCase());                     \
    }                                                                                          \
    testCase()                                                                                 \
    {                                                                                          \
    }                                                                                          \
    ~testCase()                                                                                \
    {                                                                                          \
    }

#define gctest_case_name(testCaseName)                 \
    virtual std::string _set_test_case_name() override \
    {                                                  \
        return #testCaseName;                          \
    }

#define gctest_case_description(testCaseDescription)          \
    virtual std::string _set_test_case_description() override \
    {                                                         \
        return #testCaseDescription;                          \
    }

#define gctest_before_sleep_in_nanosecond(sleepTime)                           \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return sleepTime;                                                      \
    }

#define gctest_after_sleep_in_nanosecond(sleepTime)                           \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return sleepTime;                                                     \
    }

#define gctest_before_sleep_in_microsecond(sleepTime)                          \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                 \
    }

#define gctest_after_sleep_in_microsecond(sleepTime)                          \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                \
    }

#define gctest_before_sleep_in_millisecond(sleepTime)                          \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);              \
    }

#define gctest_after_sleep_in_millisecond(sleepTime)                          \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);             \
    }

#define gctest_before_sleep_in_second(sleepTime)                               \
    virtual std::uint64_t _set_sleep_time_before_test_in_nanosecond() override \
    {                                                                          \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);           \
    }

#define gctest_after_sleep_in_second(sleepTime)                               \
    virtual std::uint64_t _set_sleep_time_after_test_in_nanosecond() override \
    {                                                                         \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);          \
    }

#define gctest_before \
    virtual void _before_test() override

#define gctest_now \
    virtual void _test() override

#define gctest_after \
    virtual void _after_test() override

#endif
