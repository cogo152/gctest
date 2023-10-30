#include <iostream>

extern int not_main(void);

int unsuccessfulTestCase;

int main()
{
    int returnValueFromNotMain = not_main();

    if (returnValueFromNotMain != unsuccessfulTestCase)
    {
        std::cout << "TEST IS UNSUCCESSFULL. RETURN VALUE FROM NOT MAIN IS  : " << returnValueFromNotMain << std::endl;
        return 1;
    }
    else
    {
        std::cout << "TEST IS SUCCESSFULL" << std::endl;
        return 0;
    }
}