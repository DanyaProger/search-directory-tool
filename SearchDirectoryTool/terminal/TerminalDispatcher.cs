using SearchDirectoryTool.processes;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;

namespace SearchDirectoryTool.terminal
{
    class TerminalDispatcher
    {
        public static void ChangeDirectory(string fullPath)
        {
            Process parentProcess = ProcessHelper.GetParentProcess();
            if (parentProcess.ProcessName.Equals("TOTALCMD64"))
            {
                ChangeTotalCommanderDirectory(fullPath);
            } else if (parentProcess.ProcessName.Equals("bash") ||
                parentProcess.ProcessName.Equals("cmd") ||
                parentProcess.ProcessName.Equals("powershell"))
            {
                ChangeTerminalDirectory(fullPath, parentProcess);
            }
        }

        public static void ChangeTotalCommanderDirectory(string fullPath)
        {
            if (Environment.GetEnvironmentVariable("COMMANDER_EXE") != null)
            {
                string commanderEXE = Environment.GetEnvironmentVariable("COMMANDER_EXE");
                Process process = Process.Start(commanderEXE, "/S /O " + "\"" + fullPath + "\"");
                process.WaitForExit();
            }
        }

        public static void ChangeTerminalDirectory(string fullPath, Process parentProcess)
        {
            SendToTerminal(parentProcess, fullPath);
        }

        public static void SendToTerminal(Process terminalProcess, string fullPath)
        {
            int currentProcessId = Process.GetCurrentProcess().Id;

            ProcessStartInfo startInfo = new ProcessStartInfo("TerminalSender\\TerminalSender.exe");
            startInfo.ArgumentList.Add(currentProcessId.ToString());
            startInfo.ArgumentList.Add(terminalProcess.ProcessName);
            startInfo.ArgumentList.Add(fullPath);
            Process terminalSenderProcess = Process.Start(startInfo);
        }
    }
}
