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
                else if (terminalProcessName.Equals("cmd"))
                {
                    string message;
                    if (Path.GetPathRoot(Directory.GetCurrentDirectory()).ToLower().Equals(Path.GetPathRoot(fullPath).ToLower()))
                    {
                        message = "cd " + fullPath;
                    } else
                    {
                        message = "cd /D " + fullPath;
                    }
                    sim.Keyboard.TextEntry(message);
                    sim.Keyboard.KeyDown(VirtualKeyCode.RETURN);
                } else
                {
                    sim.Keyboard.TextEntry("cd " + fullPath);
                    sim.Keyboard.KeyDown(VirtualKeyCode.RETURN);
                }
            }
        }
    }
}
