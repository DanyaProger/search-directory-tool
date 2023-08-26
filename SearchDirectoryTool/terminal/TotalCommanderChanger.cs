using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchDirectoryTool.terminal
{
    internal class TotalCommanderChanger : IDirectoryChanger
    {
        public void ChangeDirectory(string path)
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
