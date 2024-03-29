using System.Diagnostics;

namespace SearchDirectoryTool.terminal
{
    internal abstract class TerminalDirectoryChanger : ITerminalDirectoryChanger
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

        public void ChangeDirectory(string path)
        {
            int currentProcessId = Process.GetCurrentProcess().Id;

            ProcessStartInfo startInfo = new ProcessStartInfo("TerminalSender\\TerminalSender.exe");
            startInfo.ArgumentList.Add(currentProcessId.ToString());
            startInfo.ArgumentList.Add(Delay().ToString());
            startInfo.ArgumentList.Add(PathToCdCommand(path));
            Process terminalSenderProcess = Process.Start(startInfo);
        }
    }
}
