using System;
using System.Diagnostics;
using System.Threading;
using WindowsInput;
using WindowsInput.Native;

namespace TerminalSender
{
    class TerminalSender
    {
        static void Main(string[] args)
        {
            if (args.Length == 3)
            {
                int sdProcessId = int.Parse(args[0]);
                string terminalProcessName = args[1];
                string fullPath = args[2];

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

                InputSimulator sim = new InputSimulator();

                if (terminalProcessName.Equals("bash"))
                {
                    Thread.Sleep(100);
                    sim.Keyboard.TextEntry("cd \'" + fullPath + "\'");
                    sim.Keyboard.KeyDown(VirtualKeyCode.RETURN);
                }
                else
                {
                    sim.Keyboard.TextEntry("cd " + fullPath);
                    sim.Keyboard.KeyDown(VirtualKeyCode.RETURN);
                }
            }
        }
    }
}
