#ifndef GTEST_HELPER
#define GTEST_HELPER

#include <iostream>
#include <string>

#define ANSI_TXT_GRN "\033[0;32m"
#define ANSI_TXT_MGT "\033[0;35m" // Magenta
#define ANSI_TXT_DFT "\033[0;0m"  // Console default
#define GTEST_BOX "[     cout ] "
#define COUT_GTEST ANSI_TXT_GRN << GTEST_BOX // You could add the Default
#define COUT_GTEST_MGT COUT_GTEST << ANSI_TXT_MGT

class GTestHelper
{
  public:
    static void ConsoleWrite(std::string msg)
    {
        std::cout << COUT_GTEST_MGT << msg.c_str() << ANSI_TXT_MGT << std::endl;
    }
};

#endif // !GTEST_HELPER