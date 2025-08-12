using SearchDirectoryTool.terminal;
using WindowsInput;

namespace SD.Tests
{
    internal class CmdTests : AbstractChangerTests
    {
        protected override string GetChangerExe()
        {
            return "cmd.exe";
        }

        protected override ITerminalDirectoryChanger GetChangerObject()
        {
            return new CmdDirectoryChanger();
        }

        protected override int GetInitSleep()
        {
            return 2000;
        }

        protected override void Enter(string command)
        {
            inputSimulator.Keyboard.TextEntry(command);
            inputSimulator.Keyboard.KeyPress(VirtualKeyCode.RETURN);
        }

        protected override void EnterExit()
        {
            inputSimulator.Keyboard.TextEntry("exit");
            inputSimulator.Keyboard.KeyPress(VirtualKeyCode.RETURN);
        }

        [OneTimeSetUp]
        public new void BeforeAllTests()
        {
            base.BeforeAllTests();
        }

        [OneTimeTearDown]
        public new void AfterAllTests()
        {
            base.AfterAllTests();
        }


        [Test]
        public new void TestSdHome()
        {
            base.TestSdHome();
        }
    }
}
