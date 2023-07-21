using System;
using TerminalSender.processes;

namespace TerminalSender
{
    class TerminalSender
    {
        static void Main(string[] args)
        {
            ProcessHelper.printParentProcesses();
        }
    }
}
