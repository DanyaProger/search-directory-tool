namespace SearchDirectoryTool.terminal
{
    public interface ITerminalDirectoryChanger : IDirectoryChanger
    {
        string PathToCdCommand(string path);
        int Delay();
    }
}
