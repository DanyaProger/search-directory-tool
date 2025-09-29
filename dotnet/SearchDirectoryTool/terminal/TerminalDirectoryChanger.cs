using System.Diagnostics;
using System.IO;
using System.Text;

namespace SearchDirectoryTool.terminal
{
    public abstract class TerminalDirectoryChanger : ITerminalDirectoryChanger
    {
        int delay;
        public TerminalDirectoryChanger(int delay)
        {
            this.delay = delay;
        }

        public int Delay()
        {
            return delay;
        }

        public abstract string PathToCdCommand(string path);

        public virtual void ChangeDirectory(string path)
        {
            int currentProcessId = Process.GetCurrentProcess().Id;

            string EXE_PATH = System.Reflection.Assembly.GetExecutingAssembly().Location;
            string EXE_DIR = Path.GetDirectoryName(EXE_PATH);
            ProcessStartInfo startInfo = new ProcessStartInfo($"{EXE_DIR}\\TerminalSender\\TerminalSender.exe");
            StringBuilder arguments = new StringBuilder();
            arguments.Append(currentProcessId.ToString());
            arguments.Append(" " + Delay().ToString());
            arguments.Append(" \"" + PathToCdCommand(path) + "\"");
            startInfo.Arguments = arguments.ToString();
            Process terminalSenderProcess = Process.Start(startInfo);
        }
    }
}
