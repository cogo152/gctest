#include <iostream>
#include <atomic>

extern int not_main(void);

std::atomic_uint32_t unsuccessfulTestCases{0};
std::atomic_uint32_t incompleteTestCases{1};

int main()
{
    std::atomic_uint32_t returnValueFromNotMain = not_main();

    if ((returnValueFromNotMain != unsuccessfulTestCases) || (incompleteTestCases != 1))
    {
        std::cout << "TEST SUIT IS\t\t==>\tUNSUCCESSFULL" << std::endl
                  << "FAILED TEST CASES\t==>\t" << returnValueFromNotMain << " MUST BE " << unsuccessfulTestCases << std::endl
                  << "INCOMPLETE TEST CASES\t==>\t" << incompleteTestCases << " MUST BE 1"
                  << std::endl;

        return 1;
    }
    else
    {
        std::cout << "TEST SUIT IS\t\t==>\tSUCCESSFULL" << std::endl;
        return 0;
    }
}