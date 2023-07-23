using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Diagnostics;
using SearchDirectoryTool.terminal;

namespace SearchDirectoryTool
{
    class Executor
    {
        Arguments arguments;
        PathDispatcher pathHelper;

        public Executor(Arguments arguments)
        {
            this.arguments = arguments;
            pathHelper = new PathDispatcher();
            
        }

        public void run()
        {
            pathHelper.LoadDirs();

            string path;
            bool isOptional = !arguments.optionalArgument.Equals(new KeyValuePair<string, string>());

            if (arguments.args.Length == 0)
            {
                path = Directory.GetCurrentDirectory();
            }
            else if (arguments.args.Length == 1)
            {
                path = arguments.args[0];
            } else
            {
                Console.WriteLine("Wrong number of parameters: " + arguments.args.Length);
                return;
            }

            if (isOptional && !arguments.optionalArgument.Key.Equals("alias"))
            {
                Console.WriteLine("Unknown optional parameter");
                return;
            }
            string fullPath = pathHelper.UpdateMostSuitablePath(path);
            if (fullPath != null)
            {
                if (isOptional)
                {
                    pathHelper.UpdateAlias(fullPath, arguments.optionalArgument.Value);
                }
                TerminalDispatcher.ChangeDirectory(fullPath);
            }

            pathHelper.SaveDirs();
        }

        private void AddToPath(string path)
        {
            
        }
    }
}
