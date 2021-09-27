using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using System.Diagnostics;

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
            if (arguments.args.Length == 1)
            {
                if (!arguments.optionalArgument.Equals(new KeyValuePair<string, string>()))
                {
                    if (arguments.optionalArgument.Key == "alias")
                    {
                        ChangeDirectory(arguments.args[0], arguments.optionalArgument.Value);
                    } else
                    {
                        Console.WriteLine("Wrong name or position of parameter: " + arguments.optionalArgument.Key);
                    }
                } else
                {
                    ChangeDirectory(arguments.args[0]);
                }
            } else if (arguments.args.Length == 0)
            {
                if (!arguments.optionalArgument.Equals(new KeyValuePair<string, string>()))
                {
                    if (arguments.optionalArgument.Key == "alias")
                    {
                        ChangeDirectory("", arguments.optionalArgument.Value);
                    } else if (arguments.optionalArgument.Key == "path")
                    {
                        AddToPath(arguments.args[0]);
                    } else
                    {
                        Console.WriteLine("Wrong name of parameter: " + arguments.optionalArgument.Key);
                    }
                }
            } else
            {
                Console.WriteLine("Wrong set of arguments");
            }
        }

        private void ChangeDirectory(string path, string alias="")
        {
            pathHelper.LoadDirs();

            string fullPath;
            string checkedPath;
            if (!alias.Equals(""))
            {
                checkedPath = alias;
            } else
            {
                checkedPath = path;
            }

            fullPath = pathHelper.UpdateMostSuitablePath(checkedPath);
            if (fullPath == null)
            {
                if (path.Equals(""))
                    path = Directory.GetCurrentDirectory();
                if (pathHelper.IsFullPath(path))
                    fullPath = pathHelper.AddPath(path, alias);
            }
            if (fullPath != null)
            {
                if (Environment.GetEnvironmentVariable("COMMANDER_EXE") == null)
                {
                    Directory.SetCurrentDirectory(fullPath);
                } else
                {
                    string commanderEXE = Environment.GetEnvironmentVariable("COMMANDER_EXE");
                    Process process = Process.Start(commanderEXE, "/S /O " + fullPath);
                    process.WaitForExit();
                }

            }
            
            pathHelper.SaveDirs();
        }

        private void AddToPath(string path)
        {
            
        }
    }
}
