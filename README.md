# Search directory tool README

This program switches conveniently between directories in terminals and file managers on Windows.

## Supported programs

 - cmd
 - powershell
 - bash
 - Total Commander
 - explorer
 - Far manager
 
## Supported features

 - change directory from any place to directory with certain alias:
    ```
    sd loads                        //equivalent cd C:\Users\Username\Downloads
    ```
 - define alias for directory:
    ```
    sd --alias loads                // create alias "loads" for current directory                        // equivalent cd C:\Users\Username 
    ```
 - add a directory with sd.exe to Path environment variable:
   ```
   sd --path                        // now sd.exe reachable from any place
   ```
 - remove a directory with sd.exe from Path environment variable:
   ```
   sd --remove-path
   ```
 - show parent process information:
   ```
   sd --parent                      // show message with parent process pid and name
   ```
 - show help:
   ```
   sd --help
   ```
   
## How to build:

 1) open file "cpp\sd-workspace.workspace" in Codeblocks;
 2) activate "search-directory-tool" project;
 3) choose "Release" target;
 4) run "build";
 5) go to "cpp\bin\Release" directory and run `sd --path`.
 
Now you can use "sd".