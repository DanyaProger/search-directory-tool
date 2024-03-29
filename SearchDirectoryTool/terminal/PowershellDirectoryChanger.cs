using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SearchDirectoryTool.terminal
{
    internal class PowershellDirectoryChanger : TerminalDirectoryChanger
    {
        public PowershellDirectoryChanger() : base(0) { }

        public override string PathToCdCommand(string path)
        {
            return "cd " + path;
        }
    }
}
