using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Transactions;
using WindowsInput;

namespace SD.Tests
{
    internal abstract class AbstractChangerTests
    {
        private const string TEST_BIN_DIR = "test-bin";
        private string oldPath;
        private string sdDir;
        private Process process;
        protected InputSimulator inputSimulator = new InputSimulator();
        protected abstract string GetChangerExe();
        protected virtual string[] GetChangerExeArgs()
        {
            return new string[0];
        }
        protected abstract int GetInitSleep();
        protected abstract void Enter(string command);
        protected abstract void EnterExit();


        protected void BeforeAllTests()
        {
            DirectoryInfo directory = new DirectoryInfo(Directory.GetCurrentDirectory());
            while (!directory.GetFiles("*.sln").Any())
            {
                directory = directory.Parent;
            }

            sdDir = Path.Combine(directory.FullName, TEST_BIN_DIR);
            if (!Directory.Exists(sdDir))
            {
                throw new DirectoryNotFoundException();
            }

            File.WriteAllLines(Path.Combine(sdDir, "sd-pwd.bat"), new string[] { "@echo off", "echo %cd%> " + Path.Combine(sdDir, "pwd.txt") });

            oldPath = Environment.GetEnvironmentVariable("PATH");
            string newPath = sdDir + ";" + oldPath;
            Environment.SetEnvironmentVariable("PATH", newPath);

            process = new Process();
            process.StartInfo.UseShellExecute = true;
            process.StartInfo.FileName = GetChangerExe();
            process.StartInfo.CreateNoWindow = false;
            foreach (string arg in GetChangerExeArgs())
                process.StartInfo.ArgumentList.Add(arg);

            process.Start();

            Thread.Sleep(GetInitSleep());
        }

        protected void TestSdHome()
        {
            File.Delete(Path.Combine(sdDir, "pwd.txt"));
            Enter("sd home");

            Thread.Sleep(1000);

            Enter("sd-pwd.bat");

            Thread.Sleep(500);

            string actualDir = File.ReadAllLines(Path.Combine(sdDir, "pwd.txt"))[0];
            Assert.AreEqual("C:\\Users\\Danila_Maiseyenkau\\work", actualDir);
        }

        protected void AfterAllTests()
        {
            EnterExit();

            process.WaitForExit();

            Environment.SetEnvironmentVariable("PATH", oldPath);
        }
    }
}
