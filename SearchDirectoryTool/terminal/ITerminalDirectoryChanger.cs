namespace SearchDirectoryTool.terminal
{
    internal interface ITerminalDirectoryChanger : IDirectoryChanger
    {
        string PathToCdCommand(string path);
        int Delay();
    }
}
