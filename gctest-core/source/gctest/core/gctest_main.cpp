#include <gctest/core/gctest_type.hpp>
#include <gctest/core/gctest_exception.hpp>
#include <gctest/core/gctest_registery.hpp>

#include <csetjmp>
#include <signal.h>
#include <cstring>

#include <sstream>
#include <string>
#include <iostream> // maybe delete later

static void __attribute__((constructor(101))) ini_registery()
{
    gctest::registery::functionTestRegistery = new gctest::registery::FunctionTestRegistery();
}

static void __attribute__((destructor(101))) fini_registery()
{
    delete gctest::registery::functionTestRegistery;
}

static int totalSuccessfulTest;
static int totalFailedTest;

static std::jmp_buf jump_buffer;

static void signal_handler(int signalNumber)
{
    longjmp(jump_buffer, signalNumber);
}

#ifdef __NOT_MAIN__
int not_main(void)
#else
int main(void)
#endif
{
    struct sigaction act;
    struct sigaction oldact;
    std::memset(&act, 0, sizeof(act));
    act.sa_handler = signal_handler;
    act.sa_flags = SA_NODEFER | SA_NOMASK | SA_ONSTACK;
    sigaction(SIGSEGV, &act, &oldact);
    sigaction(SIGFPE, &act, &oldact);

    const std::size_t size = gctest::registery::functionTestRegistery->size();

    for (std::size_t i = 0; i < size; i++)
    {
        const gctest::registery::FunctionTestInfo &functionTestInfo = gctest::registery::functionTestRegistery->get(i);

        try
        {
            int signalNumber;
            if ((signalNumber = setjmp(jump_buffer)) == 0)
            {
                functionTestInfo.functionTest();

                gctest::registery::functionTestRegistery->add_result(i, "successfull");
                totalSuccessfulTest++;
            }
            else
            {
                std::stringstream stream;
                stream << "Error code = " << signalNumber;

                throw gctest::exception::TestException(std::move(stream.str()));
            }
        }
        catch (const gctest::exception::TestException &e)
        {
            std::stringstream stream;
            stream << "failed => "
                   << "( " << e.what() << " )";

            std::string message = stream.str();

            gctest::registery::functionTestRegistery->add_result(i, message);

            totalFailedTest++;
        }
        catch (const std::exception &e)
        {
            std::stringstream stream;
            stream << "failed => "
                   << "( " << e.what() << " )";

            std::string message = stream.str();

            gctest::registery::functionTestRegistery->add_result(i, message);

            totalFailedTest++;
        }
        catch (...)
        {
            std::stringstream stream;
            stream << "failed => "
                   << "( None standard exception )";

            std::string message = stream.str();

            gctest::registery::functionTestRegistery->add_result(i, message);

            totalFailedTest++;
        }
    }

    for (std::size_t i = 0; i < size; i++)
    {
        const gctest::registery::FunctionTestInfo &functionTestInfo = gctest::registery::functionTestRegistery->get(i);

        std::cout << "Test Name : " << functionTestInfo.functionTestName
                  << " , "
                  << "Test Result : " << functionTestInfo.functionTestResult
                  << std::endl;
    }

    std::cout << "TOTAL TEST : " << size << std::endl;
    std::cout << "TOTAL SUCCESSFUL TEST : " << totalSuccessfulTest << std::endl;
    std::cout << "TOTAL FAILED TEST : " << totalFailedTest << std::endl;

#ifdef __NOT_MAIN__
    return totalFailedTest;
#else
    if (totalFailedTest > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
#endif

}