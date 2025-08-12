using SearchDirectoryTool.processes;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Diagnostics;

namespace SearchDirectoryTool.terminal
{
    class TerminalDispatcher
    {
        private static Dictionary<string, IDirectoryChanger> parentProcessNameToDirectoryChanger = new Dictionary<string, IDirectoryChanger>();

        static TerminalDispatcher()
        {
            parentProcessNameToDirectoryChanger.Add("TOTALCMD64", new TotalCommanderChanger());
            parentProcessNameToDirectoryChanger.Add("cmd", new CmdDirectoryChanger());
            parentProcessNameToDirectoryChanger.Add("powershell", new PowershellDirectoryChanger());
            parentProcessNameToDirectoryChanger.Add("VsDebugConsole", new CmdDirectoryChanger());
            parentProcessNameToDirectoryChanger.Add("bash", new BashDirectoryChanger());
        }

        public static void ChangeDirectory(string fullPath)
        {
            Process parentProcess = ProcessHelper.GetParentProcess();

            IDirectoryChanger directoryChanger = null;
            if (parentProcessNameToDirectoryChanger.ContainsKey(parentProcess.ProcessName))
            {
                directoryChanger = parentProcessNameToDirectoryChanger[parentProcess.ProcessName];
            }
            else
            {
                return;
            }

            directoryChanger.ChangeDirectory(fullPath);
        }
    }
}
