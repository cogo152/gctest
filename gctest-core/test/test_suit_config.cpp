#include <gctest/core/test.hpp>

#include <iostream>

GCTEST_SUIT_NAME(gctest internal test);
GCTEST_SUIT_MULTITHREADED(GCTEST_FALSE);

GCTEST_SUIT_ADD_START_COMMAND(startCommand1, 1)
{
    std::cout << " startCommand1 " << std::endl;
}

GCTEST_SUIT_ADD_START_COMMAND(startCommand2, 2)
{
    std::cout << " startCommand2 " << std::endl;
}

GCTEST_SUIT_ADD_STOP_COMMAND(stopCommand1, 1)
{
    std::cout << " stopCommand1 " << std::endl;
}

GCTEST_SUIT_ADD_STOP_COMMAND(stopCommand2, 2)
{
    std::cout << " stopCommand2 " << std::endl;
}
