#include <gctest/core/gctest.hpp>

#include <csignal>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

GCTEST_CASE(test_sigabort_1)
{
    gctest_case_priority(test_sigabort_1, 1);
    gctest_case_name("catching SIGABORT 1");
    gctest_case_description("gctest should handle SIGABORT without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGABRT);
    }
};

GCTEST_CASE(test_sigabort_2)
{
    gctest_case_priority(test_sigabort_2, 2);
    gctest_case_name("catching SIGABORT 2");
    gctest_case_description("gctest should handle SIGABORT without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGABRT);
    }
};

GCTEST_CASE(test_sigbus_1)
{
    gctest_case_priority(test_sigbus_1, 3);
    gctest_case_name("catching SIGBUS 1");
    gctest_case_description("gctest should handle SIGBUS without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGBUS);
    }
};

GCTEST_CASE(test_sigbus_2)
{
    gctest_case_priority(test_sigbus_2, 4);
    gctest_case_name("catching SIGBUS 2");
    gctest_case_description("gctest should handle SIGBUS without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGBUS);
    }
};

GCTEST_CASE(test_sigfpe_1)
{
    gctest_case_priority(test_sigfpe_1, 5);
    gctest_case_name("catching SIGFPE 1");
    gctest_case_description("gctest should handle SIGFPE without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGFPE);
    }
};

GCTEST_CASE(test_sigfpe_2)
{
    gctest_case_priority(test_sigfpe_2, 6);
    gctest_case_name("catching SIGFPE 2");
    gctest_case_description("gctest should handle SIGFPE without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        int a = 1 / 0;
    }
};

GCTEST_CASE(test_sigill_1)
{
    gctest_case_priority(test_sigill_1, 7);
    gctest_case_name("catching SIGILL 1");
    gctest_case_description("gctest should handle SIGILL without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGILL);
    }
};

GCTEST_CASE(test_sigill_2)
{
    gctest_case_priority(test_sigill_2, 8);
    gctest_case_name("catching SIGILL 2");
    gctest_case_description("gctest should handle SIGILL without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGILL);
    }
};

GCTEST_CASE(test_sigquit_1)
{
    gctest_case_priority(test_sigquit_1, 9);
    gctest_case_name("catching SIGQUIT 1");
    gctest_case_description("gctest should handle SIGQUIT without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(test_sigquit_2)
{
    gctest_case_priority(test_sigquit_2, 10);
    gctest_case_name("catching SIGQUIT 2");
    gctest_case_description("gctest should handle SIGQUIT without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(test_sigsev_1)
{
    gctest_case_priority(test_sigsev_1, 11);
    gctest_case_name("catching SIGSEGV 1");
    gctest_case_description("gctest should handle SIGSEGV without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSEGV);
    }
};

GCTEST_CASE(test_sigsev_2)
{
    gctest_case_priority(test_sigsev_2, 12);
    gctest_case_name("catching SIGSEGV 2");
    gctest_case_description("gctest should handle SIGSEGV without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        int *ptr = nullptr;
        *ptr = 5;
    }
};

GCTEST_CASE(test_sigsys_1)
{
    gctest_case_priority(test_sigsys_1, 13);
    gctest_case_name("catching SIGSYS 1");
    gctest_case_description("gctest should handle SIGSYS without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSYS);
    }
};

GCTEST_CASE(test_sigsys_2)
{
    gctest_case_priority(test_sigsys_2, 14);
    gctest_case_name("catching SIGSYS 2");
    gctest_case_description("gctest should handle SIGSYS without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSYS);
    }
};

GCTEST_CASE(test_sigtrap_1)
{
    gctest_case_priority(test_sigtrap_1, 15);
    gctest_case_name("catching SIGTRAP 1");
    gctest_case_description("gctest should handle SIGTRAP without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(test_sigtrap_2)
{
    gctest_case_priority(test_sigtrap_2, 16);
    gctest_case_name("catching SIGTRAP 1");
    gctest_case_description("gctest should handle SIGTRAP without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(test_sigxcpu_1)
{
    gctest_case_priority(test_sigxcpu_1, 17);
    gctest_case_name("catching SIGXCPU 1");
    gctest_case_description("gctest should handle SIGXCPU without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGXCPU);
    }
};

GCTEST_CASE(test_sigxcpu_2)
{
    gctest_case_priority(test_sigxcpu_2, 18);
    gctest_case_name("catching SIGXCPU 2");
    gctest_case_description("gctest should handle SIGXCPU without crashing");

    gctest_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGXCPU);
    }
};
