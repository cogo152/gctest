#include <gctest/core/executor.hpp>
#include <gctest/core/type.hpp>
#include <gctest/core/exception.hpp>

namespace gctest
{
    namespace core
    {
        namespace executor
        {
            std::map<std::thread::id, std::jmp_buf *> TestSuitExecutor::__jumpBuffers;

            void TestSuitExecutor::__signal_handler(int signalNumber)
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

            const std::size_t TestSuitExecutor::__testCasesCapacity = 50;

            TestSuitExecutor::TestSuitExecutor() : __testSuitName(),
                                                   __isTestSuitExecutionMultithreaded(false),
                                                   __testSuitStartCommands(),
                                                   __testSuitStopCommands(),
                                                   __testCases(),
                                                   __totalSuccessfulTestCases(0),
                                                   __totalFailedTestCases(0),
                                                   __testCaseExecutors(),
                                                   __isSuitFailCalled(false)
            {
                __testSuitStartCommands.reserve(__testCasesCapacity);
                __testSuitStopCommands.reserve(__testCasesCapacity);
                __testCases.reserve(__testCasesCapacity);
            }

            TestSuitExecutor::~TestSuitExecutor()
            {
            }

            void TestSuitExecutor::set_test_suit_name(std::string testSuitName)
            {
                __testSuitName = testSuitName;
            }

            void TestSuitExecutor::set_test_suit_execution_multithreaded(std::uint32_t isTestSuitExecutionMultiThreaded)
            {
                __isTestSuitExecutionMultithreaded = isTestSuitExecutionMultiThreaded > 0 ? true : false;
            }

            void TestSuitExecutor::add_test_suit_start_command(command_t command)
            {
                __testSuitStartCommands.push_back(command);
            }

            void TestSuitExecutor::add_test_suit_stop_command(command_t command)
            {
                __testSuitStopCommands.push_back(command);
            }

            void TestSuitExecutor::add_test_case(gctest::core::type::TestCase *testCase)
            {
                __testCases.push_back(testCase);
            }

            void TestSuitExecutor::__execute_test_case(const std::size_t begin, const std::size_t end)
            {
                // implement actions
                struct sigaction newAction;
                struct sigaction oldAction;
                std::memset(&newAction, 0, sizeof(newAction));
                std::memset(&oldAction, 0, sizeof(oldAction));
                newAction.sa_handler = TestSuitExecutor::__signal_handler;
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
                    if (__isSuitFailCalled)
                    {
                        break;
                    }

                    gctest::core::type::TestCase *testCase = __testCases.at(i);

                    try
                    {
                        int signalNumber = 0;

                        if ((signalNumber = setjmp(jumpBuffer)) == 0)
                        {
                            testCase->before_test_case();
                            testCase->test_case();
                            testCase->after_test_case();

                            testCase->set_test_case_successful();

                            __totalSuccessfulTestCases++;
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

                            throw std::runtime_error(stream.str());
                        }
                    }
                    catch (const gctest::core::exception::TestCaseException &e)
                    {
                        std::stringstream stream;
                        stream << "\t\t" << e.what();

                        std::string message = stream.str();

                        testCase->set_test_case_failed(message);

                        __totalFailedTestCases++;
                    }
                    catch (const gctest::core::exception::TestSuitException &e)
                    {
                        std::stringstream stream;
                        stream << "\t\t" << e.what();

                        std::string message = stream.str();

                        testCase->set_test_case_failed(message);

                        __totalFailedTestCases++;

                        __isSuitFailCalled = true;
                    }
                    catch (const std::exception &e)
                    {
                        std::stringstream stream;
                        stream << "\t\t" << e.what();

                        std::string message = stream.str();

                        testCase->set_test_case_failed(message);

                        __totalFailedTestCases++;
                    }
                    catch (...)
                    {
                        std::stringstream stream;
                        stream << "\t\tnone standard exception";

                        std::string message = stream.str();

                        testCase->set_test_case_failed(message);

                        __totalFailedTestCases++;
                    }
                }
            }

            void TestSuitExecutor::__execute_test_cases(void)
            {

                const double totalTestCases = static_cast<double>(__testCases.size());
                const double totalCpuCores = static_cast<double>(std::thread::hardware_concurrency());

                __testCaseExecutors.reserve(static_cast<std::size_t>(totalCpuCores));

                if (!__isTestSuitExecutionMultithreaded)
                {
                    __execute_test_case(0, totalTestCases); // must be on main thread. JNI error
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

                        std::thread executor(&TestSuitExecutor::__execute_test_case, this, begin, end);
                        __testCaseExecutors.push_back(std::move(executor));
                    }
                }

                for (std::size_t i = 0; i < __testCaseExecutors.size(); i++)
                {
                    __testCaseExecutors.at(i).join();
                }
            }

            void TestSuitExecutor::__print_test_suit_report()
            {
                for (gctest::core::type::TestCase *testCase : __testCases)
                {
                    testCase->print_test_case_report();
                }

                std::cout << "TEST SUIT NAME \t\t\t: " << __testSuitName << std::endl;
                std::cout << "TOTAL THREADS \t\t\t: " << (__testCaseExecutors.size() == 0 ? 1 : __testCaseExecutors.size()) << std::endl;
                std::cout << "TOTAL TEST CASES \t\t: " << __testCases.size() << std::endl;
                std::cout << "TOTAL FAILED TEST CASES\t\t: " << __totalFailedTestCases << std::endl;
                std::cout << "TOTAL SUCCESSFUL TEST CASES\t: " << __totalSuccessfulTestCases << std::endl;
                std::cout << "TOTAL INCOMPLETE TEST CASES\t: " << __testCases.size() - (__totalFailedTestCases + __totalSuccessfulTestCases) << std::endl;
                std::cout << "TEST SUIT RESULT \t\t: " << (__testCases.size() == __totalSuccessfulTestCases ? "SUCCESSFULL" : "FAILED") << std::endl;
            }

            void TestSuitExecutor::execute_test_suit()
            {

                for (auto &command : __testSuitStartCommands)
                {
                    command();
                }

                for (auto &testCase : __testCases)
                {
                    testCase->setup_test_case();
                }

                __execute_test_cases();

                for (auto &testCase : __testCases)
                {
                    testCase->teardown_test_case();
                }

                __print_test_suit_report();

                for (auto &command : __testSuitStopCommands)
                {
                    command();
                }
            }

            std::size_t TestSuitExecutor::get_total_test_cases() const
            {
                return __testCases.size();
            }

            std::size_t TestSuitExecutor::get_total_failed_test_cases() const
            {
                return __totalFailedTestCases;
            }

            std::size_t TestSuitExecutor::get_total_successful_test_cases() const
            {
                return __totalSuccessfulTestCases;
            }

            TestSuitExecutor *testSuitExecutor;
        }

    }

}
