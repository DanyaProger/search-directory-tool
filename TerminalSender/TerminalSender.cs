using System;
using TerminalSender.processes;

namespace TerminalSender
{
    class TerminalSender
    {
        static void Main(string[] args)
        {
            if (args.Length == 1)
            {
                ProcessHelper.printParentProcesses();
                ProcessHelper.WaitProcessEnd(int.Parse(args[0]));
                Console.WriteLine("TotalCommander exited");
                Console.ReadKey();
            }

        }
    }
}
