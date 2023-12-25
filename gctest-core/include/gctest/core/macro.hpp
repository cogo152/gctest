#ifndef GCTEST_CORE_MACRO_HPP
#define GCTEST_CORE_MACRO_HPP

#include <gctest/core/type.hpp>
#include <gctest/core/assertion.hpp>
#include <gctest/core/executor.hpp>

#include <string>
#ifndef __SOURCE_LOCATION__
#include <source_location>
#else
#include <gctest/core/source_location.hpp>
#endif

#define GCTEST_TRUE (1)
#define GCTEST_FALSE (0)

#define GCTEST_SUIT_NAME(suitName)                                               \
    void __attribute__((constructor(102))) set_test_suit_name()                  \
    {                                                                            \
        gctest::core::executor::testSuitExecutor->set_test_suit_name(#suitName); \
    }

#define GCTEST_SUIT_MULTITHREADED(isMultiThreaded)                                                        \
    void __attribute__((constructor(103))) set_test_suit_execution_multithreaded()                        \
    {                                                                                                     \
        gctest::core::executor::testSuitExecutor->set_test_suit_execution_multithreaded(isMultiThreaded); \
    }

#define GCTEST_SUIT_ADD_START_COMMAND(commandName, commandPriority)                             \
    void commandName(void);                                                                     \
    void __attribute__((constructor(200 + commandPriority))) commandName##commandPriority(void) \
    {                                                                                           \
        gctest::core::executor::testSuitExecutor->add_test_suit_start_command(commandName);     \
    }                                                                                           \
    void commandName(void)

#define GCTEST_SUIT_ADD_STOP_COMMAND(commandName, commandPriority)                              \
    void commandName(void);                                                                     \
    void __attribute__((constructor(200 + commandPriority))) commandName##commandPriority(void) \
    {                                                                                           \
        gctest::core::executor::testSuitExecutor->add_test_suit_stop_command(commandName);      \
    }                                                                                           \
    void commandName(void)

#define GCTEST_CASE(testCaseName) \
    class testCaseName final : public gctest::core::type::TestCase

#define gctest_case_config_default(testCaseName)                                                  \
    static void __attribute__((constructor)) testCaseName_default(void)                           \
    {                                                                                             \
        gctest::core::executor::testSuitExecutor->add_test_case(new testCaseName(#testCaseName)); \
    }                                                                                             \
    testCaseName(std::string testCaseName) : gctest::core::type::TestCase(testCaseName)           \
    {                                                                                             \
    }                                                                                             \
    ~testCaseName()                                                                               \
    {                                                                                             \
    }

#define gctest_case_config_priority(testCaseName, testCasePriority)                                       \
    static void __attribute__((constructor(300 + testCasePriority))) testCaseName##testCasePriority(void) \
    {                                                                                                     \
        gctest::core::executor::testSuitExecutor->add_test_case(new testCaseName(#testCaseName));         \
    }                                                                                                     \
    testCaseName(std::string testCaseName) : gctest::core::type::TestCase(testCaseName)                   \
    {                                                                                                     \
    }                                                                                                     \
    ~testCaseName()                                                                                       \
    {                                                                                                     \
    }

#define gctest_case_description(testCaseDescription)          \
    virtual std::string _set_test_case_description() override \
    {                                                         \
        return #testCaseDescription;                          \
    }

#define gctest_case_requirement(testCaseRequirement)          \
    virtual std::string _set_test_case_requirement() override \
    {                                                         \
        return #testCaseRequirement;                          \
    }

#define gctest_case_sleep_before_nanosecond(sleepTime)                               \
    virtual std::uint64_t _set_sleep_time_before_test_case_for_nanosecond() override \
    {                                                                                \
        return sleepTime;                                                            \
    }

#define gctest_case_sleep_after_nanosecond(sleepTime)                               \
    virtual std::uint64_t _set_sleep_time_after_test_case_for_nanosecond() override \
    {                                                                               \
        return sleepTime;                                                           \
    }

#define gctest_case_sleep_before_microsecond(sleepTime)                              \
    virtual std::uint64_t _set_sleep_time_before_test_case_for_nanosecond() override \
    {                                                                                \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                       \
    }

#define gctest_case_sleep_after_microsecond(sleepTime)                              \
    virtual std::uint64_t _set_sleep_time_after_test_case_for_nanosecond() override \
    {                                                                               \
        return static_cast<std::uint64_t>(sleepTime * 1000UL);                      \
    }

#define gctest_case_sleep_before_millisecond(sleepTime)                              \
    virtual std::uint64_t _set_sleep_time_before_test_case_for_nanosecond() override \
    {                                                                                \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);                    \
    }

#define gctest_case_sleep_after_millisecond(sleepTime)                              \
    virtual std::uint64_t _set_sleep_time_after_test_case_for_nanosecond() override \
    {                                                                               \
        return static_cast<std::uint64_t>(sleepTime * 1000000UL);                   \
    }

#define gctest_case_sleep_before_second(sleepTime)                                   \
    virtual std::uint64_t _set_sleep_time_before_test_case_for_nanosecond() override \
    {                                                                                \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);                 \
    }

#define gctest_case_sleep_after_second(sleepTime)                                   \
    virtual std::uint64_t _set_sleep_time_after_test_case_for_nanosecond() override \
    {                                                                               \
        return static_cast<std::uint64_t>(sleepTime * 1000000000UL);                \
    }

#define gctest_case_before \
    virtual void _before_test_case() override

#define gctest_case_now \
    virtual void _test_case() override

#define gctest_case_after \
    virtual void _after_test_case() override

#define assert_true(parameter) \
    gctest::core::assertion::assert_true(std::source_location::current(), parameter);

#define assert_false(parameter) \
    gctest::core::assertion::assert_false(std::source_location::current(), parameter);

#define assert_equal(parameter1, parameter2) \
    gctest::core::assertion::assert_equal(std::source_location::current(), parameter1, parameter2);

#define assert_not_equal(parameter1, parameter2) \
    gctest::core::assertion::assert_not_equal(std::source_location::current(), parameter1, parameter2);

#define assert_greater(parameter1, parameter2) \
    gctest::core::assertion::assert_greater(std::source_location::current(), parameter1, parameter2);

#define assert_greater_or_equal(parameter1, parameter2) \
    gctest::core::assertion::assert_greater_or_equal(std::source_location::current(), parameter1, parameter2);

#define assert_lesser(parameter1, parameter2) \
    gctest::core::assertion::assert_lesser(std::source_location::current(), parameter1, parameter2);

#define assert_lesser_or_equal(parameter1, parameter2) \
    gctest::core::assertion::assert_lesser_or_equal(std::source_location::current(), parameter1, parameter2);

#define assert_lesser_or_equal(parameter1, parameter2) \
    gctest::core::assertion::assert_lesser_or_equal(std::source_location::current(), parameter1, parameter2);

#define assert_nonmember_throws(function, ...) \
    gctest::core::assertion::assert_nonmember_throws(std::source_location::current(), function, ##__VA_ARGS__);

#define assert_nonmember_not_throws(function, ...) \
    gctest::core::assertion::assert_nonmember_not_throws(std::source_location::current(), function, ##__VA_ARGS__);

#define assert_member_throws(instance, function, ...) \
    gctest::core::assertion::assert_member_throws(std::source_location::current(), instance, function, ##__VA_ARGS__);

#define assert_member_not_throws(instance, function, ...) \
    gctest::core::assertion::assert_member_not_throws(std::source_location::current(), instance, function, ##__VA_ARGS__);

#endif