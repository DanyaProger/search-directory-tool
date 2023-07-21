using System;
using System.Collections.Generic;
using System.Text;

namespace SearchDirectoryTool
{
    class SDTool
    {
        public static void Main(string[] args)
        {
            Arguments arguments = ArgumentParser.splitArguments(args);
            Executor executor = new Executor(arguments);
            executor.run();
        }
    }
}
