using System;

namespace SearchDirectoryTool
{
    class Program
    {
        static void Main(string[] args)
        {
            SDTool sdTool = new SDTool();
            args = new string[1] { "D:\\Programming"};
            sdTool.pipeline(args);
        }
    }
}
