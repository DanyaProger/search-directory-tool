using System.Diagnostics;
using WindowsInput;

namespace SD.Tests
{
    public class CmdTest
    {
        private const string TEST_BIN_DIR = "test-bin";
        private string oldPath;
        private string sdDir;

        [SetUp]
        public void Setup()
        {
            DirectoryInfo directory = new DirectoryInfo(Directory.GetCurrentDirectory());
            while (!directory.GetFiles("*.sln").Any())
            {
                directory = directory.Parent;
            }

            sdDir = Path.Combine(directory.FullName, TEST_BIN_DIR);
            Console.WriteLine(sdDir);
            if (!Directory.Exists(sdDir))
            {
                throw new DirectoryNotFoundException();
            }

            File.WriteAllLines(Path.Combine(sdDir, "sd-pwd.bat"), new string[] { "@echo off", "echo %cd%> " + Path.Combine(sdDir, "pwd.txt") });

            oldPath = Environment.GetEnvironmentVariable("PATH");
            string newPath = sdDir + ";" + oldPath;
            Environment.SetEnvironmentVariable("PATH", newPath);
        }

        [Test]
        public void testCmdSdHome()
        {
            InputSimulator simulator = new InputSimulator();

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

            string actualDir = File.ReadAllLines(Path.Combine(sdDir, "pwd.txt"))[0];
            Assert.AreEqual("C:\\Users\\Danila_Maiseyenkau\\work", actualDir);
        }

        [Test]
        public void testPowershellSdHome()
        {
            InputSimulator simulator = new InputSimulator();

            using (Process process = new Process())
            {
                process.StartInfo.UseShellExecute = true;
                process.StartInfo.FileName = "powershell.exe";
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

            string actualDir = File.ReadAllLines(Path.Combine(sdDir, "pwd.txt"))[0];
            Assert.AreEqual("C:\\Users\\Danila_Maiseyenkau\\work", actualDir);
        }

        [Test]
        public void testBashSdHome()
        {
            InputSimulator simulator = new InputSimulator();

            using (Process process = new Process())
            {
                process.StartInfo.UseShellExecute = true;
                process.StartInfo.FileName = "C:\\Program Files\\Git\\git-bash.exe";
                process.StartInfo.CreateNoWindow = false;

                process.Start();

                Thread.Sleep(5000);
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

            string actualDir = File.ReadAllLines(Path.Combine(sdDir, "pwd.txt"))[0];
            Assert.AreEqual("C:\\Users\\Danila_Maiseyenkau\\work", actualDir);
        }

        [TearDown]
        public void Teardown()
        {
            Environment.SetEnvironmentVariable("PATH", oldPath);
        }
    }
}