using System;
using System.Diagnostics;
using System.Threading;
using TerminalSender.winapi;

namespace TerminalSender
{
    class TerminalSender
    {
        static void Main(string[] args)
        {
            if (args.Length == 3)
            {
                int sdProcessId = int.Parse(args[0]);
                int terminalWindowProcessId = int.Parse(args[1]);
                string fullPath = args[2];

                Process sdProcess = null;
                try
                {
                    sdProcess = Process.GetProcessById(sdProcessId);
                } catch (Exception e)
                {
                    sdProcess = null;
                }
                Process terminalWindowProcess = Process.GetProcessById(terminalWindowProcessId);

                if (sdProcess != null && !sdProcess.HasExited && sdProcess.ProcessName.Equals("sd"))
                {
                    sdProcess.WaitForExit();
                }

                if (terminalWindowProcess.ProcessName.Equals("mintty"))
                {
                    Thread.Sleep(100);
                    WinApi.PostMessage(terminalWindowProcess.MainWindowHandle, "cd " + "'" + fullPath + "'\n");
                }
                else
                {
                    WinApi.PostMessage(terminalWindowProcess.MainWindowHandle, "cd " + fullPath);
                }
            }
        }
    }
}
