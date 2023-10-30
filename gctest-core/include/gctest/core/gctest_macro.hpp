#ifndef GCTEST_MACRO_HPP
#define GCTEST_MACRO_HPP

#include <gctest/core/gctest_registery.hpp>

#define FUNCTION_TEST(functionTest, testPriority)                                           \
    void functionTest(void);                                                                \
    void __attribute__((constructor(200 + testPriority))) functionTest_##testPriority(void) \
    {                                                                                       \
        gctest::registery::functionTestRegistery->add_step(functionTest, #functionTest);    \
    }                                                                                       \
    void functionTest(void)

#endif