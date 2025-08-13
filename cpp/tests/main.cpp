#include <iostream>
#include "src/CmdTests.h"

using namespace std;

int main()
{
    CmdTests tests;
    tests.before_all_tests();
    tests.test_sd_home();
    tests.after_all_tests();
    return 0;
}
