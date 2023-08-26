namespace SearchDirectoryTool.terminal
{
    internal class BashDirectoryChanger : TerminalDirectoryChanger
    {
        public BashDirectoryChanger() : base(200)
        {
            
        }

        public override string PathToCdCommand(string path)
        {
            return "cd \'" + path + "\'";
        }
    }
}
