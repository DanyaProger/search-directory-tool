using System.Diagnostics;
using WindowsInput;

namespace SD.Tests
{
    public class CmdTest
    {
        private string lastOutput = "";

        [SetUp]
        public void Setup()
        {

        }

        [Test]
        public void SdHome()
        {
            InputSimulator simulator = new InputSimulator();

            Console.WriteLine("Hello world!");
            using (Process process = new Process())
            {
                process.StartInfo.UseShellExecute = true;
                process.StartInfo.FileName = "cmd.exe";
                process.StartInfo.CreateNoWindow = false;

                process.Start();

                Thread.Sleep(2000);
                simulator.Keyboard.TextEntry("sd home");
                simulator.Keyboard.KeyDown(VirtualKeyCode.RETURN);

                Thread.Sleep(1000);

                simulator.Keyboard.TextEntry("sd-pwd");
                simulator.Keyboard.KeyDown(VirtualKeyCode.RETURN);

                Thread.Sleep(1000);

                simulator.Keyboard.TextEntry("exit");
                simulator.Keyboard.KeyDown(VirtualKeyCode.RETURN);

                process.WaitForExit();
            }

            string actualDir = File.ReadAllLines("c:\\Users\\Danila_Maiseyenkau\\work\\search-directory-tool\\bin\\pwd.txt")[0];
            Assert.AreEqual("C:\\Users\\Danila_Maiseyenkau", actualDir);
        }
    }
}