using System;
using System.Collections.Generic;
using System.Text;

namespace SearchDirectoryTool
{
    class DirectoryElement
    {
        public string fullpath;
        public int count;
        public string alias;

        public DirectoryElement()
        {

        }

        public DirectoryElement(string fullpath, string alias)
        {
            this.fullpath = fullpath;
            if (alias.Equals(""))
            {
                alias = "1d2q3m_empty";
            }
            this.alias = alias;
            this.count = 1;
        }
    }
}
