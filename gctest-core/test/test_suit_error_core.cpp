#include <gctest/core/gctest.hpp>

#include <csignal>

extern int unsuccessfulTestCase;

using namespace gctest::assertion;

GCTEST_CASE(sigabort_1)
{
    gctest_case_config(sigabort_1, 1);
    gctest_case_description("gctest should handle first SIGABORT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGABRT);
    }
};

GCTEST_CASE(sigabort_2)
{
    gctest_case_config(sigabort_2, 2);
    gctest_case_description("gctest should handle second SIGABORT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGABRT);
    }
};

GCTEST_CASE(sigbus_1)
{
    gctest_case_config(sigbus_1, 3);
    gctest_case_description("gctest should handle fist SIGBUS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGBUS);
    }
};

GCTEST_CASE(sigbus_2)
{
    gctest_case_config(sigbus_2, 4);
    gctest_case_description("gctest should handle second SIGBUS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGBUS);
    }
};

GCTEST_CASE(sigfpe_1)
{
    gctest_case_config(sigfpe_1, 5);
    gctest_case_description("gctest should handle first SIGFPE without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGFPE);
    }
};

GCTEST_CASE(sigfpe_2)
{
    gctest_case_config(sigfpe_2, 6);
    gctest_case_description("gctest should handle second SIGFPE without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        int a = 1 / 0;
    }
};

GCTEST_CASE(sigill_1)
{
    gctest_case_config(sigill_1, 7);
    gctest_case_description("gctest should handle first SIGILL without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGILL);
    }
};

GCTEST_CASE(sigill_2)
{
    gctest_case_config(sigill_2, 8);
    gctest_case_description("gctest should handle second SIGILL without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGILL);
    }
};

GCTEST_CASE(sigquit_1)
{
    gctest_case_config(sigquit_1, 9);
    gctest_case_description("gctest should handle first SIGQUIT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(sigquit_2)
{
    gctest_case_config(sigquit_2, 10);
    gctest_case_description("gctest should handle second SIGQUIT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(sigsev_1)
{
    gctest_case_config(sigsev_1, 11);
    gctest_case_description("gctest should handle first SIGSEGV without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSEGV);
    }
};

GCTEST_CASE(sigsev_2)
{
    gctest_case_config(sigsev_2, 12);
    gctest_case_description("gctest should handle second SIGSEGV without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        int *ptr = nullptr;
        *ptr = 5;
    }
};

GCTEST_CASE(sigsys_1)
{
    gctest_case_config(sigsys_1, 13);
    gctest_case_description("gctest should handle first SIGSYS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSYS);
    }
};

GCTEST_CASE(sigsys_2)
{
    gctest_case_config(sigsys_2, 14);
    gctest_case_description("gctest should handle second SIGSYS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGSYS);
    }
};

GCTEST_CASE(sigtrap_1)
{
    gctest_case_config(sigtrap_1, 15);
    gctest_case_description("gctest should handle first SIGTRAP without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(sigtrap_2)
{
    gctest_case_config(sigtrap_2, 16);
    gctest_case_description("gctest should handle second SIGTRAP without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(sigxcpu_1)
{
    gctest_case_config(sigxcpu_1, 17);
    gctest_case_description("gctest should handle first SIGXCPU without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGXCPU);
    }
};

GCTEST_CASE(sigxcpu_2)
{
    gctest_case_config(sigxcpu_2, 18);
    gctest_case_description("gctest should handle second SIGXCPU without crashing");

    gctest_case_now
    {
        unsuccessfulTestCase++;
        std::raise(SIGXCPU);
    }
};
