#include <gctest/core/gctest_executor.hpp>

#include <iostream>

static void __attribute__((constructor(101))) ini_registery()
{
    gctest::executor::testCaseExecutor = new gctest::executor::TestCaseExecutor();
}

static void __attribute__((destructor(101))) fini_registery()
{
    delete gctest::executor::testCaseExecutor;
}

extern int totalFailedTest;

#ifdef __NOT_MAIN__
int not_main(void)
#else
int main(void)
#endif
{
    gctest::executor::testCaseExecutor->execute_test_cases();
    gctest::executor::testCaseExecutor->print_test_report();

#ifdef __NOT_MAIN__
    return gctest::executor::testCaseExecutor->get_total_failed_tests();
#else
    if (gctest::executor::testCaseExecutor->get_total_failed_tests() > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
#endif
}