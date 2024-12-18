using System;
using System.Diagnostics;

namespace SearchDirectoryTool.terminal
{
    public class TotalCommanderChanger : TerminalDirectoryChanger
    {
        public TotalCommanderChanger() : base(0) {}

        public override string PathToCdCommand(string path)
        {
            return "cd \"" + path + "\"";
        }

        public override void ChangeDirectory(string path)
        {
            if (Environment.GetEnvironmentVariable("COMMANDER_EXE") != null)
            {
                string commanderEXE = Environment.GetEnvironmentVariable("COMMANDER_EXE");
                Process process = Process.Start(commanderEXE, "/S /O " + "\"" + path + "\"");
                process.WaitForExit();
            }
        }
    }
}
