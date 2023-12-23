#include <gctest/core/test.hpp>

#include <atomic>
#include <csignal>

extern std::atomic_uint32_t unsuccessfulTestCases;

GCTEST_CASE(sigabort_1)
{
    gctest_case_config_priority(sigabort_1, 1);
    gctest_case_description("testing sigabort_1");
    gctest_case_requirement("gctest should handle first SIGABORT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGABRT);
    }
};

GCTEST_CASE(sigabort_2)
{
    gctest_case_config_priority(sigabort_2, 2);
    gctest_case_description("testing sigabort_2");
    gctest_case_requirement("gctest should handle second SIGABORT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGABRT);
    }
};

GCTEST_CASE(sigbus_1)
{
    gctest_case_config_priority(sigbus_1, 3);
    gctest_case_description("testing sigbus_1");
    gctest_case_requirement("gctest should handle fist SIGBUS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGBUS);
    }
};

GCTEST_CASE(sigbus_2)
{
    gctest_case_config_priority(sigbus_2, 4);
    gctest_case_description("testing sigbus_2");
    gctest_case_requirement("gctest should handle second SIGBUS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGBUS);
    }
};

GCTEST_CASE(sigfpe_1)
{
    gctest_case_config_priority(sigfpe_1, 5);
    gctest_case_description("testing sigfpe_1");
    gctest_case_requirement("gctest should handle first SIGFPE without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGFPE);
    }
};

GCTEST_CASE(sigfpe_2)
{
    gctest_case_config_priority(sigfpe_2, 6);
    gctest_case_description("testing sigfpe_2");
    gctest_case_requirement("gctest should handle second SIGFPE without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        int a = 1 / 0;
    }
};

GCTEST_CASE(sigill_1)
{
    gctest_case_config_priority(sigill_1, 7);
    gctest_case_description("testing sigill_1");
    gctest_case_requirement("gctest should handle first SIGILL without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGILL);
    }
};

GCTEST_CASE(sigill_2)
{
    gctest_case_config_priority(sigill_2, 8);
    gctest_case_description("testing sigill_2");
    gctest_case_requirement("gctest should handle second SIGILL without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGILL);
    }
};

GCTEST_CASE(sigquit_1)
{
    gctest_case_config_priority(sigquit_1, 9);
    gctest_case_description("testing sigquit_1");
    gctest_case_requirement("gctest should handle first SIGQUIT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(sigquit_2)
{
    gctest_case_config_priority(sigquit_2, 10);
    gctest_case_description("testing sigquit_2");
    gctest_case_requirement("gctest should handle second SIGQUIT without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGQUIT);
    }
};

GCTEST_CASE(sigsev_1)
{
    gctest_case_config_priority(sigsev_1, 11);
    gctest_case_description("testing sigsev_1");
    gctest_case_requirement("gctest should handle first SIGSEGV without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGSEGV);
    }
};

GCTEST_CASE(sigsev_2)
{
    gctest_case_config_priority(sigsev_2, 12);
    gctest_case_description("testing sigsev_2");
    gctest_case_requirement("gctest should handle second SIGSEGV without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        int *ptr = nullptr;
        *ptr = 5;
    }
};

GCTEST_CASE(sigsys_1)
{
    gctest_case_config_priority(sigsys_1, 13);
    gctest_case_description("testing sigsys_1");
    gctest_case_requirement("gctest should handle first SIGSYS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGSYS);
    }
};

GCTEST_CASE(sigsys_2)
{
    gctest_case_config_priority(sigsys_2, 14);
    gctest_case_description("testing sigsys_2");
    gctest_case_requirement("gctest should handle second SIGSYS without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGSYS);
    }
};

GCTEST_CASE(sigtrap_1)
{
    gctest_case_config_priority(sigtrap_1, 15);
    gctest_case_description("testing sigtrap_1");
    gctest_case_requirement("gctest should handle first SIGTRAP without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(sigtrap_2)
{
    gctest_case_config_priority(sigtrap_2, 16);
    gctest_case_description("testing sigtrap_2");
    gctest_case_requirement("gctest should handle second SIGTRAP without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGTRAP);
    }
};

GCTEST_CASE(sigxcpu_1)
{
    gctest_case_config_priority(sigxcpu_1, 17);
    gctest_case_description("testing sigxcpu_1");
    gctest_case_requirement("gctest should handle first SIGXCPU without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGXCPU);
    }
};

GCTEST_CASE(sigxcpu_2)
{
    gctest_case_config_priority(sigxcpu_2, 18);
    gctest_case_description("testing sigxcpu_2");
    gctest_case_requirement("gctest should handle second SIGXCPU without crashing");

    gctest_case_now
    {
        unsuccessfulTestCases++;

        std::raise(SIGXCPU);
    }
};
