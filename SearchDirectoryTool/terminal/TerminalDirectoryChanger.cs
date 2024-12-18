using System.Diagnostics;
using System.IO;

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
            File.AppendAllText("c:\\Users\\Danila_Maiseyenkau\\work\\search-directory-tool\\test-bin\\sd.log", $"Change directory: ${path}");
            int currentProcessId = Process.GetCurrentProcess().Id;

            ProcessStartInfo startInfo = new ProcessStartInfo("TerminalSender\\TerminalSender.exe");
            startInfo.ArgumentList.Add(currentProcessId.ToString());
            startInfo.ArgumentList.Add(Delay().ToString());
            startInfo.ArgumentList.Add(PathToCdCommand(path));
            Process terminalSenderProcess = Process.Start(startInfo);
        }
    }
}
