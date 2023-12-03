#include <gctest/core/gctest_executor.hpp>
#include <gctest/core/gctest_type.hpp>
#include <gctest/core/gctest_exception.hpp>

namespace gctest
{
    namespace executor
    {
        std::map<std::thread::id, std::jmp_buf *> TestCaseExecutor::__jumpBuffers;

        void TestCaseExecutor::__signal_handler(int signalNumber)
        {
            std::thread::id thisThreadId = std::this_thread::get_id();

            for (auto &x : __jumpBuffers)
            {
                if (x.first == thisThreadId)
                {
                    longjmp(*x.second, signalNumber);
                }
            }
        }

        const std::size_t TestCaseExecutor::__capacityVector = 50;

        TestCaseExecutor::TestCaseExecutor() : __isMultithreaded(false),
                                               __testCases(),
                                               __totalSuccessfulTests(0),
                                               __executors()
        {
            __testCases.reserve(__capacityVector);
        }

        TestCaseExecutor::~TestCaseExecutor()
        {
        }

        void TestCaseExecutor::set_multithreaded(std::uint32_t isMultiThreaded)
        {
            __isMultithreaded = isMultiThreaded > 0 ? true : false;
        }

        void TestCaseExecutor::add_test_case(gctest::type::TestCase *testCase)
        {
            __testCases.push_back(testCase);
        }

        void TestCaseExecutor::__execute_test_case(const std::size_t begin, const std::size_t end)
        {
            // implement actions
            struct sigaction newAction;
            struct sigaction oldAction;
            std::memset(&newAction, 0, sizeof(newAction));
            std::memset(&oldAction, 0, sizeof(oldAction));
            newAction.sa_handler = TestCaseExecutor::__signal_handler;
            newAction.sa_flags = SA_NODEFER | SA_NOMASK | SA_ONSTACK;

            // Core group
            sigaction(SIGABRT, &newAction, &oldAction);
            sigaction(SIGBUS, &newAction, &oldAction);
            sigaction(SIGFPE, &newAction, &oldAction);
            sigaction(SIGILL, &newAction, &oldAction);
            sigaction(SIGQUIT, &newAction, &oldAction);
            sigaction(SIGSEGV, &newAction, &oldAction);
            sigaction(SIGSYS, &newAction, &oldAction);
            sigaction(SIGTRAP, &newAction, &oldAction);
            sigaction(SIGXCPU, &newAction, &oldAction);

            std::jmp_buf jumpBuffer;
            std::thread::id thisThreadId = std::this_thread::get_id();

            __jumpBuffers[thisThreadId] = &jumpBuffer;

            for (std::size_t i = begin; i < end; i++)
            {
                gctest::type::TestCase *testCase = __testCases.at(i);

                testCase->setup_test();

                try
                {
                    int signalNumber = 0;

                    if ((signalNumber = setjmp(jumpBuffer)) == 0)
                    {
                        testCase->before_test();
                        testCase->test();
                        testCase->after_test();

                        testCase->set_test_successful();

                        __totalSuccessfulTests++;
                    }
                    else
                    {
                        std::stringstream stream;

                        stream << "Error code = " << signalNumber << " , "
                               << " Error name = ";

                        switch (signalNumber)
                        {
                        case SIGABRT:
                        {
                            stream << " SIGABRT ";
                            break;
                        }
                        case SIGBUS:
                        {
                            stream << " SIGBUS ";
                            break;
                        }
                        case SIGFPE:
                        {
                            stream << " SIGFPE ";
                            break;
                        }
                        case SIGILL:
                        {
                            stream << " SIGILL ";
                            break;
                        }
                        case SIGQUIT:
                        {
                            stream << " SIGQUIT ";
                            break;
                        }
                        case SIGSEGV:
                        {
                            stream << " SIGSEGV ";
                            break;
                        }
                        case SIGSYS:
                        {
                            stream << " SIGSYS ";
                            break;
                        }
                        case SIGTRAP:
                        {
                            stream << " SIGTRAP ";
                            break;
                        }
                        case SIGXCPU:
                        {
                            stream << " SIGXCPU ";
                            break;
                        }

                        default:
                        {
                            stream << " NOT IMPLEMENTED ERROR ";
                            break;
                        }
                        }

                        throw gctest::exception::TestException(std::move(stream.str()));
                    }
                }
                catch (const gctest::exception::TestException &e)
                {
                    std::stringstream stream;
                    stream << "( " << e.what() << " )";

                    std::string message = stream.str();

                    testCase->set_test_failed(message);

                    __totalFailedTests++;
                }
                catch (const std::exception &e)
                {
                    std::stringstream stream;
                    stream << "( " << e.what() << " )";

                    std::string message = stream.str();

                    testCase->set_test_failed(message);

                    __totalFailedTests++;
                }
                catch (...)
                {
                    std::stringstream stream;
                    stream << "( None standard exception )";

                    std::string message = stream.str();

                    testCase->set_test_failed(message);

                    __totalFailedTests++;
                }

                testCase->teardown_test();
            }
        }

        void TestCaseExecutor::execute_test_cases()
        {
            const double totalTestCases = static_cast<double>(__testCases.size());
            const double totalCpuCores = static_cast<double>(std::thread::hardware_concurrency());

            __executors.reserve(static_cast<std::size_t>(totalCpuCores));

            if (!__isMultithreaded)
            {
                std::thread executor(&TestCaseExecutor::__execute_test_case, this, 0, totalTestCases);
                __executors.push_back(std::move(executor));
            }
            else
            {
                const double testCasesPerCore = std::round(totalTestCases / totalCpuCores);

                std::size_t allocatedThreads{0};

                if (testCasesPerCore == 0)
                {
                    allocatedThreads = 1;
                }
                else if (testCasesPerCore <= totalCpuCores)
                {
                    allocatedThreads = testCasesPerCore;
                }
                else
                {
                    allocatedThreads = totalCpuCores;
                }

                const double testCasesPerThread = std::round(totalTestCases / allocatedThreads);

                std::size_t begin{0};
                std::size_t end{0};

                for (std::size_t i = 0; i < allocatedThreads; i++)
                {
                    begin = i * testCasesPerThread;

                    if (i == allocatedThreads - 1)
                    {
                        end = totalTestCases;
                    }
                    else
                    {
                        end = begin + testCasesPerThread;
                    }

                    std::thread executor(&TestCaseExecutor::__execute_test_case, this, begin, end);
                    __executors.push_back(std::move(executor));
                }
            }

            for (std::size_t i = 0; i < __executors.size(); i++)
            {
                __executors.at(i).join();
            }
        }

        std::size_t TestCaseExecutor::get_total_tests() const
        {
            return __testCases.size();
        }

        std::size_t TestCaseExecutor::get_total_failed_tests() const
        {
            return __totalFailedTests;
        }

        std::size_t TestCaseExecutor::get_total_successful_tests() const
        {
            return __totalSuccessfulTests;
        }

        void TestCaseExecutor::print_test_report()
        {
            for (gctest::type::TestCase *testCase : __testCases)
            {
                testCase->print_test_case();
            }

            std::cout << "TOTAL THREADS : " << __executors.size() << std::endl;
            std::cout << "TOTAL TEST : " << __testCases.size() << std::endl;
            std::cout << "TOTAL FAILED TEST : " << __totalFailedTests << std::endl;
            std::cout << "TOTAL SUCCESSFUL TEST : " << __totalSuccessfulTests << std::endl;
        }

        TestCaseExecutor *testCaseExecutor;
    }

}
