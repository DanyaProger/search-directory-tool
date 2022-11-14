using System;
using System.IO;

namespace SearchDirectoryTool
{
    class Program
    {
        static void Main(string[] args)
        {
            SDTool sdTool = new SDTool();
            sdTool.pipeline(args);
        }
    }
}
