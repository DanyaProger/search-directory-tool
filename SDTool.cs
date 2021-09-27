using System;
using System.Collections.Generic;
using System.Text;

namespace SearchDirectoryTool
{
    class SDTool
    {
        private Arguments arguments;
        
        public void pipeline(string[] args)
        {
            arguments = ArgumentParser.splitArguments(args);
            Executor executor = new Executor(arguments);
            executor.run();
        }
    }
}
