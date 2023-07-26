using System;
using System.Collections.Generic;
using System.IO;
using System.Text;

namespace SearchDirectoryTool
{
    class PathDispatcher
    {
        public static string DIRS_FILE;
        public static string EXE_DIR;
        private List<DirectoryElement> directories;

        public PathDispatcher()
        {
            string EXE_PATH = System.Reflection.Assembly.GetExecutingAssembly().Location;
            EXE_DIR = Path.GetDirectoryName(EXE_PATH);
            DIRS_FILE = EXE_DIR + "\\dirs.txt"; 
        }

        public void LoadDirs()
        {
            if (!File.Exists(DIRS_FILE))
            {
                using (File.Create(DIRS_FILE));
            }
            using (StreamReader file = new StreamReader(DIRS_FILE))
            {
                directories = new List<DirectoryElement>();

                string str1, str2;
                while ((str1 = file.ReadLine()) != null)
                {
                    DirectoryElement current = new DirectoryElement();

                    str2 = file.ReadLine();
                    string[] secondLine = str2.Split(" ");
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
                        current.fullpath = str1;
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
                if (IsFullPath(path) && Path.GetFullPath(path).Equals(directories[i].fullpath))
                {
                    index = i;
                    break;
                }
                if (GetLastDir(directories[i].fullpath).ToLower().IndexOf(path.ToLower()) != -1)
                {
                    if (directories[i].count > maxCount)
                    {
                        index = i;
                        maxCount = directories[i].count;
                    }
                }
            }

            if (index == -1 && IsFullPath(path))
            {
                DirectoryElement dir = new DirectoryElement(Path.GetFullPath(path), "");
                directories.Add(dir);
                return dir.fullpath;
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

        public void UpdateAlias(string fullPath, string alias)
        {
            foreach(var dir in directories)
            {
                if (dir.fullpath.Equals(fullPath))
                {
                    dir.alias = alias;
                }
            }
        }

        public bool IsFullPath(string path)
        {
            return Path.IsPathRooted(path) && Path.IsPathFullyQualified(path) && Directory.Exists(path);
        }

        public string AddPath(string path, string alias)
        {
            string fullPath = Path.GetFullPath(path);
            directories.Add(new DirectoryElement(fullPath, alias));

            return fullPath;
        }

        public string GetDirFromFile(string path)
        {
            string filePath = Path.GetFullPath(path);
            if (File.Exists(filePath))
            {
                return filePath.Substring(0, filePath.LastIndexOf('\\'));
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

        public void PrintDirs()
        {
            LoadDirs();
            foreach (var d in directories)
            {
                Console.WriteLine(d.fullpath);
                Console.WriteLine(d.count + " " + d.alias);
            }
        }
    }
}
