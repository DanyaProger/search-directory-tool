using System;
using System.Collections.Generic;
using System.Text;
using System.Text.RegularExpressions;

namespace SearchDirectoryTool
{
    class ArgumentParser
    {
        public static Arguments splitArguments(string[] args)
        {
            Arguments arguments = new Arguments();
            arguments.argsCount = args.Length;

            List<string> clearedArgs = new List<string>();
            for (int i = 0; i < args.Length; i++)
            {
                if (Regex.IsMatch(args[i], @"^--\w+$"))
                {
                    string key = args[i].Substring(2), value = "";
                    if (i + 1 < args.Length)
                    {
                        value = args[i + 1];
                    }

                    arguments.optionalArgument = new KeyValuePair<string, string>(key, value);

                    i += 1;
                    continue;
                }
                clearedArgs.Add(args[i]);
            }
            arguments.args = clearedArgs.ToArray();
            return arguments;
        }
    }
}
