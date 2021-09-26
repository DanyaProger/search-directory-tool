using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SearchDirectoryTool
{
    class PathDispatcher
    {
        public static string DIRS_FILE = "dirs.txt";
        private List<DirectoryElement> directories;

        public void LoadDirs()
        {
            using (StreamReader file = new StreamReader(DIRS_FILE))
            {
                directories = new List<DirectoryElement>();

                string str;
                while ((str = file.ReadLine()) != null)
                {
                    DirectoryElement current = new DirectoryElement();

                    str = file.ReadLine();
                    string[] secondLine = str.Split(" ");
                    if (secondLine.Length == 2)
                    {
                        int counter;
                        try
                        {
                            counter = int.Parse(secondLine[0]);
                        } catch (FormatException e)
                        {
                            directories.Clear();
                            return;
                        }

                        string alias = secondLine[1];
                        current.fullpath = str;
                        current.count = counter;
                        current.alias = alias;

                        directories.Add(current);
                    }
                }
            }
        }

        public void SaveDirs()
        {
            using (StreamWriter file = new StreamWriter(DIRS_FILE))
            {
                foreach (var dir in directories)
                {
                    file.WriteLine(dir.fullpath);
                    file.WriteLine(dir.count + " " + dir.alias);
                }
            }
        }

        public string UpdateMostSuitablePath(string path)
        {
            if (directories == null)
            {
                LoadDirs();
            }

            int index = -1, maxCount = 0;
            for (int i = 0; i < directories.Count; i++)
            {
                if (path.Equals(directories[i].alias))
                {
                    index = i;
                    break;
                }
                if (GetLastDir(directories[i].fullpath).IndexOf(path) != -1)
                {
                    if (directories[i].count > maxCount)
                    {
                        index = i;
                        maxCount = directories[i].count;
                    }
                }
            }

            if (index != -1)
            {
                directories[index].count += 1;
                return directories[index].fullpath;
            } else
            {
                return null;
            }
            
        }

        public string GetLastDir(string path)
        {
            int lastPos = path.Length;
            if (path[path.Length - 1] == '\\')
            {
                lastPos -= 1;
            }
            int firstPos = path.LastIndexOf('\\', lastPos - 1);

            return path.Substring(firstPos + 1, lastPos - firstPos - 1);
        }
    }
}
