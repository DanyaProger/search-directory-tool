using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;

namespace TerminalSender.winapi
{
    class WinApi
    {
        private const int WM_CHAR = 0x0102;

        [DllImport("user32.dll")]
        public static extern IntPtr PostMessage(IntPtr hWnd, uint Msg, IntPtr wParam, IntPtr lParam);

        public static void PostMessage(IntPtr handle, string message)
        {
            foreach (char c in message)
            {
                PostMessage(handle, WM_CHAR, new IntPtr((int)c), IntPtr.Zero);
            }
        }
    }
}
