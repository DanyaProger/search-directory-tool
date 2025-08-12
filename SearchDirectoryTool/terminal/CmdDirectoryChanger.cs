using System.IO;

namespace SearchDirectoryTool.terminal
{
    public class CmdDirectoryChanger : TerminalDirectoryChanger
    {
        public CmdDirectoryChanger() : base(0) { }

        public override string PathToCdCommand(string path)
        {
            if (Path.GetPathRoot(Directory.GetCurrentDirectory()).ToLower().Equals(Path.GetPathRoot(path).ToLower()))
            {
                return "cd " + path;
            }
            else
            {
                return "cd /D " + path;
            }
        }
    }
}
