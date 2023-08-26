using System;
using System.Diagnostics;
using System.IO;
using System.Threading;
using WindowsInput;

namespace TerminalSender
{
    class TerminalSender
    {
        static void Main(string[] args)
        {
            if (args.Length == 3)
            {
                int sdProcessId = int.Parse(args[0]);
                int delay = int.Parse(args[1]);
                string cdCommand = args[2];

                Process sdProcess = null;
                try
                {
                    sdProcess = Process.GetProcessById(sdProcessId);
                } catch (Exception e)
                {
                    sdProcess = null;
                }

                if (sdProcess != null && !sdProcess.HasExited && sdProcess.ProcessName.Equals("sd"))
                {
                    sdProcess.WaitForExit();
                }

                Thread.Sleep(delay);

                InputSimulator sim = new InputSimulator();
                sim.Keyboard.TextEntry(cdCommand);
                sim.Keyboard.KeyDown(VirtualKeyCode.RETURN);
            }
        }
    }
}
