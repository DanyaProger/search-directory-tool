# Search directory tool README

This program is a alternative way to search and open folders in terminals and file managers on Windows.

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
 - define alias for current directory:
    ```
    sd --alias loads                // create alias "loads" for current directory
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
 - create default aliases (home, loads, doc, pic, music, videos, c, d, e, f, pf, pf86, win):
   ```
   sd --fill-dirs.txt
   ```
 - open sd GUI verison:
   ```
   sd
   ```
 - show russian help:
   ```
   sd --help
   ```
 - show english help:
   ```
   sd --help-en
   ```
   
## Installing and uninstalling

View "program setup" and "program uninstall" sections in help (`sd --help-en`)
   
## How to build:
 1) Build wxWidgets 3.3 with command:
    ```
    mingw32-make -f makefile.gcc BUILD=release MONOLITHIC=1 SHARED=0 UNICODE=1
    ```
 2) Create global variable `wx` in settings of Codeblocks;
 3) open file `cpp\sd-workspace.workspace`;
 4) activate `search-directory-tool` project;
 5) choose `Release` target;
 6) run `build`;
 7) go to `cpp\bin\Release` directory and run `sd --path`.
 
Now you can use `sd`.
