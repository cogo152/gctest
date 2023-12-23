#include <gctest/core/executor.hpp>

#include <iostream>

static void __attribute__((constructor(101))) ini_registery()
{
    gctest::core::executor::testSuitExecutor = new gctest::core::executor::TestSuitExecutor();
}

static void __attribute__((destructor(101))) fini_registery()
{
    delete gctest::core::executor::testSuitExecutor;
}

#ifdef __OWN_TEST__
int not_main(void)
#else
int main(void)
#endif
{
    gctest::core::executor::testSuitExecutor->execute_test_suit();

#ifdef __OWN_TEST__
    return gctest::core::executor::testSuitExecutor->get_total_failed_test_cases();
#else
    if (gctest::core::executor::testSuitExecutor->get_total_failed_test_cases() > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
#endif
}