#include "argsparser.h"
#include "Executor.h"

using namespace std;

int wmain(int argc, wchar_t** argv)
{
    SdArgs sd_args = SdArgsParser().parse(argc, argv);
    Executor().run(sd_args);
    return 0;
}
