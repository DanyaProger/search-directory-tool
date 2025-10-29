#ifndef CMDLINE_H_INCLUDED
#define CMDLINE_H_INCLUDED

#include <vector>
#include <map>
#include <set>
#include <windows.h>
#include <string>
#include <fstream>

#include <wx/string.h>

using namespace std;

class CmdLineFlag
{
public:
    wxString shortName, longName;
    bool isShort, isLong;

    CmdLineFlag(bool isShort, wxString s, bool isLong, wxString l)
        : shortName(s), longName(l), isShort(isShort), isLong(isLong)
    {
    }
};

class CmdLineOption
{
public:
    wxString shortName, longName;
    bool isShort, isLong;
    wxString value;

    CmdLineOption(bool isShort, wxString s, bool isLong, wxString l)
        : shortName(s), longName(l), isShort(isShort), isLong(isLong)
    {
    }
};

class CmdLineArgs
{
private:
    set<wxString> flags;
    map<wxString, wxString> options;
    vector<wxString> args;
public:
    CmdLineArgs(vector<CmdLineFlag> flags, vector<CmdLineOption> options, vector<wxString> args)
    {
        for (CmdLineFlag flag : flags)
        {
            if (flag.isShort)
                this->flags.insert(flag.shortName);
            if (flag.isLong)
                this->flags.insert(flag.longName);
        }
        for (CmdLineOption option : options)
        {
            if (option.isShort)
                this->options.insert(make_pair(option.shortName, option.value));
            if (option.isLong)
                this->options.insert(make_pair(option.longName, option.value));
        }
        this->args = args;
    }

    bool isOption(wxString option)
    {
        if (options.find(option) != options.end())
            return true;
        else
            return false;
    }

    wxString getOption(wxString option)
    {
        return options[option];
    }

    bool isFlag(wxString flag)
    {
        if (flags.find(flag) != flags.end())
            return true;
        else
            return false;
    }

    int argsSize() {
        return args.size();
    }

    wxString arg(int index)
    {
        return args[index];
    }
};

class CmdLineParser
{
private:
    vector<CmdLineFlag> possibleFlags;
    vector<CmdLineOption> possibleOptions;

    int findInFlags(wxString flagName)
    {
        for (int i = 0; i < (int)possibleFlags.size(); i++)
        {
            CmdLineFlag f = possibleFlags[i];
            if ((f.isShort && f.shortName.IsSameAs(flagName)) ||
                (f.isLong && f.longName.IsSameAs(flagName)))
                return i;
        }
        return -1;
    }

    int findInOptions(wxString optionName)
    {
        for (int i = 0; i < (int)possibleOptions.size(); i++)
        {
            CmdLineOption o = possibleOptions[i];
            if ((o.isShort && o.shortName.IsSameAs(optionName)) ||
                (o.isLong && o.longName.IsSameAs(optionName)))
                return i;
        }
        return -1;
    }

    int findNextNotDelimeterToken(vector<bool> isDelimeterToken, int iStart)
    {
        for (int i = iStart; i < (int)isDelimeterToken.size(); i++)
            if (!isDelimeterToken[i])
                return i;
        return -1;
    }

    void splitOnTokens(wxString line, vector<wxString>& tokens, vector<bool>& isDelimeterToken)
    {
        tokens.clear();
        isDelimeterToken.clear();

        wxString token;
        bool isDelimeterLastToken;

        for (size_t i = 0; i < line.length(); i++)
        {
            if (line.GetChar(i) == ' ' || line.GetChar(i) == '\t' || line.GetChar(i) == '=')
            {
                if (token.length() > 0 && !isDelimeterLastToken)
                {
                    tokens.push_back(token);
                    isDelimeterToken.push_back(false);
                    token.clear();
                }
                isDelimeterLastToken = true;
                token.Append(line.GetChar(i));
            }
            else if (line.GetChar(i) == '"')
            {
                if (token.length() > 0 && isDelimeterLastToken)
                {
                    tokens.push_back(token);
                    isDelimeterToken.push_back(true);
                    token.clear();
                }
                isDelimeterLastToken = false;
                size_t nextQuote = line.find('"', i + 1);
                if (nextQuote != wxString::npos)
                {
                    token.Append(line.SubString(i + 1, nextQuote - 1));
                    i = nextQuote;
                }
                else
                {
                    token.Append(line.GetChar(i));
                }
            }
            else
            {
                if (token.length() > 0 && isDelimeterLastToken)
                {
                    tokens.push_back(token);
                    isDelimeterToken.push_back(true);
                    token.clear();
                }
                isDelimeterLastToken = false;
                token.Append(line.GetChar(i));
            }
        }
        if (token.length() > 0)
        {
            tokens.push_back(token);
            isDelimeterToken.push_back(isDelimeterLastToken);
        }
    }

    void trimTokens(vector<wxString>& tokens, vector<bool>& isDelimeterToken)
    {
        int l = 0, r = tokens.size() - 1;
        while (l < (int)tokens.size() && isDelimeterToken[l])
            l++;
        while (r >= 0 && isDelimeterToken[r])
            r--;
        vector<wxString> resultTokens;
        vector<bool> resultIsDelimeterToken;
        for (int i = l; i <= r; i++)
        {
            resultTokens.push_back(tokens[i]);
            resultIsDelimeterToken.push_back(isDelimeterToken[i]);
        }

        tokens = resultTokens;
        isDelimeterToken = resultIsDelimeterToken;
    }

public:
    CmdLineParser(vector<CmdLineFlag> possibleFlags, vector<CmdLineOption> possibleOptions)
    {
        this->possibleFlags = possibleFlags;
        this->possibleOptions = possibleOptions;
    }

    CmdLineArgs parse(wxArrayString argv)
    {
        vector<CmdLineFlag> flags;
        vector<CmdLineOption> options;
        vector<wxString> args;

        int argc = argv.size();

        for (int i = 0; i < argc; i++)
        {
            wxString arg(argv[i]);
            if (arg.StartsWith(wxString("--")) || arg.StartsWith(wxString("-")))
            {
                wxString trimmedArg;
                if (arg.StartsWith(wxString("--")))
                    trimmedArg = arg.SubString(2, arg.Len() - 1);
                else
                    trimmedArg = arg.SubString(1, arg.Len() - 1);
                int pos = findInFlags(trimmedArg);
                if (pos != -1)
                {
                    flags.push_back(possibleFlags[pos]);
                }
                else
                {
                    pos = findInOptions(trimmedArg);
                    if (pos != -1 && i != argc - 1)
                    {
                        CmdLineOption o = possibleOptions[pos];
                        o.value = argv[i + 1];
                        options.push_back(o);
                        i++;
                    }
                    else
                    {
                        args.push_back(arg);
                    }
                }
            }
            else
            {
                args.push_back(arg);
            }
        }

        return CmdLineArgs(flags, options, args);
    }

    CmdLineArgs parseWithOneArg(wxString line)
    {
        vector<CmdLineFlag> flags;
        vector<CmdLineOption> options;
        vector<wxString> args;

        vector<wxString> tokens;
        vector<bool> isDelimeterToken;

        splitOnTokens(line, tokens, isDelimeterToken);

        trimTokens(tokens, isDelimeterToken);

        for (size_t i = 0; i < tokens.size(); i++)
        {
            if (!isDelimeterToken[i])
            {
                wxString trimmedToken;

                if (tokens[i].StartsWith(wxString("--")))
                {
                    trimmedToken = tokens[i].SubString(2, tokens[i].length() - 1);
                }
                else if (tokens[i].StartsWith(wxString("-")))
                {
                    trimmedToken = tokens[i].SubString(1, tokens[i].length() - 1);
                }

                int pos = findInFlags(trimmedToken);
                int iOptionValue;
                if (pos != -1)
                {
                    flags.push_back(possibleFlags[pos]);
                }
                else if ((pos = findInOptions(trimmedToken)) != -1 &&
                         (iOptionValue = findNextNotDelimeterToken(isDelimeterToken, i + 1)) != -1)
                {
                    CmdLineOption option = possibleOptions[pos];
                    option.value = tokens[iOptionValue];
                    options.push_back(option);
                    i = iOptionValue;
                }
                else
                {
                    wxString arg;
                    for (size_t j = i; j < tokens.size(); j++)
                        arg.Append(tokens[j]);
                    args.push_back(arg);
                    break;
                }
            }
        }

        return CmdLineArgs(flags, options, args);
    }
};

#endif // CMDLINE_H_INCLUDED
