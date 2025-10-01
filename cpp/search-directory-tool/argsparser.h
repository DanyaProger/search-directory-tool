#ifndef ARGSPARSER_H_INCLUDED
#define ARGSPARSER_H_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

class SdArgs
{
private:
    map<wstring, wstring> options;
    set<wstring> flags;
    vector<wstring> args;
    wstring epath;
public:
    SdArgs(wstring exe_path, map<wstring, wstring> options, set<wstring> flags, vector<wstring> args)
    {
        this->epath = exe_path;
        this->options = options;
        this->flags = flags;
        this->args = args;
    }

    wstring exe_path()
    {
        return epath;
    }

    bool is_option(wstring option)
    {
        if (options.find(option) != options.end())
            return true;
        else
            return false;
    }

    wstring get_option(wstring option)
    {
        return options[option];
    }

    bool is_flag(wstring flag)
    {
        if (flags.find(flag) != flags.end())
            return true;
        else
            return false;
    }

    int args_size() {
        return args.size();
    }

    wstring arg(int index)
    {
        return args[index];
    }
};

class SdArgsParser
{
private:
    set<wstring> possible_flags = {L"help", L"parent", L"remove-path", L"path"};
    set<wstring> possible_options = {L"alias"};

public:
    SdArgs parse(int argc, wchar_t** argv)
    {
        wstring exe_path(argv[0]);
        map<wstring, wstring> options;
        set<wstring> flags;
        vector<wstring> args;

        for (int i = 1; i < argc; i++)
        {
            wstring arg(argv[i]);
            if (arg.substr(0, 2) == L"--")
            {
                wstring trimmed_arg = arg.substr(2);
                if (possible_flags.find(trimmed_arg) != possible_flags.end())
                {
                    flags.insert(trimmed_arg);
                }
                else if (possible_options.find(trimmed_arg) != possible_options.end())
                {
                    if (i == argc - 1) {
                        MessageBoxW(NULL, (L"No value for option " + arg).c_str(), NULL, 0);
                        exit(0);
                    }
                    wstring option(trimmed_arg);
                    wstring value(argv[i + 1]);
                    options.insert(make_pair(option, value));
                    i++;
                }
                else
                {
                    args.push_back(arg);
                }
            }
            else
            {
                args.push_back(arg);
            }
        }

        return SdArgs(exe_path, options, flags, args);
    }
};

#endif
