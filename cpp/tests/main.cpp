#include <iostream>
#include <vector>
#include <fcntl.h>

#include "src/CmdTests.h"
#include "src/PowerShellTests.h"
#include "src/BashTests.h"
#include "src/TotalCommanderTests.h"
#include "src/ExplorerTests.h"

using namespace std;

void test_all_programs()
{
    CmdTests cmdTests;
    PowerShellTests powershellTests;
    BashTests bashTests;
    TotalCommanderTests totalCommanderTests;
    ExplorerTests explorerTests;
    vector<AbstractChangerTests*> terminals_tests = {&cmdTests, &powershellTests, &bashTests, &totalCommanderTests, &explorerTests};
    for (AbstractChangerTests* terminal_tests : terminals_tests) {
        terminal_tests->before_all_tests();
        terminal_tests->test_sd_home();
        terminal_tests->test_several_aliases();
        terminal_tests->test_replace_alias();
        terminal_tests->test_create_current_directory_alias();
        terminal_tests->test_change_directory_between_drives();
        terminal_tests->after_all_tests();
    }
}

void test_program() {
    ExplorerTests tests;
    tests.before_all_tests();
    tests.test_sd_home();
    //tests.test_several_aliases();
    //tests.test_replace_alias();
    //tests.test_create_current_directory_alias();
    //tests.test_change_directory_between_drives();
    tests.after_all_tests();
}

void one_test_all_programs()
{
    CmdTests cmdTests;
    PowerShellTests powershellTests;
    BashTests bashTests;
    TotalCommanderTests totalCommanderTests;
    vector<AbstractChangerTests*> terminals_tests = {&cmdTests, &powershellTests, &bashTests, &totalCommanderTests};
    for (AbstractChangerTests* terminal_tests : terminals_tests) {
        terminal_tests->before_all_tests();

        //terminal_tests->test_several_aliases();
        terminal_tests->test_replace_alias();
        //terminal_tests->test_create_current_directory_alias();
        //terminal_tests->test_change_directory_between_drives();

        terminal_tests->after_all_tests();
    }
}

int main()
{
    _setmode(_fileno(stdout), _O_WTEXT);

    //test_all_programs();
    test_program();
    //one_test_all_programs();
    return 0;
}
