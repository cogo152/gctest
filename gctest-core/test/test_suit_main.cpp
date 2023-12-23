#include <iostream>
#include <atomic>

extern int not_main(void);

std::atomic_uint32_t unsuccessfulTestCases{0};

int main()
{
    std::atomic_uint32_t returnValueFromNotMain = not_main();

    if (returnValueFromNotMain != unsuccessfulTestCases)
    {
        std::cout << "TEST IS UNSUCCESSFULL. RETURN VALUE FROM NOT MAIN IS  : " << returnValueFromNotMain << "MUST BE : " << unsuccessfulTestCases << std::endl;
        return 1;
    }
    else
    {
        std::cout << "TEST IS SUCCESSFULL" << std::endl;
        return 0;
    }
}