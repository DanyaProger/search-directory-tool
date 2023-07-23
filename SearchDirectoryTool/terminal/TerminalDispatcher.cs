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
            } else if (parentProcess.ProcessName.Equals("bash"))
            {
                ChangeMinTTYDirectory(fullPath, parentProcess);
            } else
            {
                ChangeUsualTerminalDirectory(fullPath, parentProcess);
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

        public static void ChangeUsualTerminalDirectory(string fullPath, Process parentProcess)
        {
            SendToTerminal(parentProcess.Id, fullPath);
        }

        public static void ChangeMinTTYDirectory(string fullPath, Process parentProcess)
        {

        }

        public static void SendToTerminal(int terminalWindowProcessId, string fullPath)
        {
            int currentProcessId = Process.GetCurrentProcess().Id;
            Process terminalSenderProcess = Process.Start("TerminalSender\\TerminalSender.exe", currentProcessId + " " + terminalWindowProcessId + " \"" + fullPath + "\"");
        }
    }
}
