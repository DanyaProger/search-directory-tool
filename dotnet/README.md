# Search directory tool README

This tool gives an opportunity to switch conveniently between directories in terminals (cmd, git-bash) and file managers (Total Commander) on Windows.

## Supported features

 - change directory from any place by substring of full path*:
    ```
    sd loads                        //equivalent cd C:\Users\Username\Downloads
    ```
 - add aliases for directory:
    ```
    cd C:\Users\Username
    sd --alias home                  // create alias "home" for current directory
    cd %SOMEWHERE%
    sd home                          // equivalent cd C:\Users\Username 
    ```

*directory must be indexed or to be full path to switch to a destination.