using WindowsInput;

namespace SD.Tests
{
    internal class TotalCmdTests : AbstractChangerTests
    {
        protected override string GetChangerExe()
        {
            return TestsConfiguration.TotalCmdExe;
        }

        protected override string[] GetChangerExeArgs()
        {
            return new string[] {Directory.GetCurrentDirectory()};
        }

        protected override int GetInitSleep()
        {
            return 2000;
        }

        protected override void Enter(string command)
        {
            inputSimulator.Keyboard.KeyPress(VirtualKeyCode.RIGHT);
            inputSimulator.Keyboard.TextEntry(command);
            inputSimulator.Keyboard.KeyPress(VirtualKeyCode.RETURN);
        }

        protected override void EnterExit()
        {
            inputSimulator.Keyboard.KeyPress(VirtualKeyCode.RIGHT);
            inputSimulator.Keyboard.TextEntry("cm_Exit");
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
