using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;

namespace TerminalSender.winapi
{
    class WinApi
    {
        private const int WM_CHAR = 0x0102;
        private const int WM_KEYDOWN = 0x0100;
        private const int WM_KEYUP = 0x0101;
        private const int VK_RETURN = 0x0D;


        [DllImport("user32.dll")]
        public static extern IntPtr PostMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

        public static void PostMessage(IntPtr handle, string message)
        {
            foreach (char c in message)
            {
                PostMessage(handle, WM_CHAR, new IntPtr((int)c), IntPtr.Zero);
                Thread.Sleep(1); //Powershell skip some characters if post instantly
            }
            PostMessage(handle, WM_KEYDOWN, new IntPtr(VK_RETURN), IntPtr.Zero);
        }
    }
}
