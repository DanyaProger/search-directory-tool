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

/** Shit code */

enum class FlagOrOption {Flag, Option};

class CmdLineFlag
{
public:
    wxString shortName, longName;
    bool fShort, fLong;
    bool isShort;

    CmdLineFlag(bool fShort, wxString s, bool fLong, wxString l)
        : shortName(s), longName(l), fShort(fShort), fLong(fLong)
    {
    }
};

class CmdLineOption
{
public:
    wxString shortName, longName;
    bool oShort, oLong;
    bool isShort;
    wxString value;

    CmdLineOption(bool oShort, wxString s, bool oLong, wxString l)
        : shortName(s), longName(l), oShort(oShort), oLong(oLong)
    {
    }
};

class CmdLineArgs
{
private:
    set<wxString> flags;
    map<wxString, wxString> options;
    vector<CmdLineFlag> flagsList;
    vector<CmdLineOption> optionsList;
    vector<wxString> args;
    vector<FlagOrOption> flagsAndOptions;
public:
    CmdLineArgs()
    {

    }

    CmdLineArgs(vector<CmdLineFlag> flags, vector<CmdLineOption> options, vector<wxString> args, vector<FlagOrOption> flagsAndOptions)
    {
        for (CmdLineFlag flag : flags)
        {
            if (flag.fShort)
                this->flags.insert(flag.shortName);
            if (flag.fLong)
                this->flags.insert(flag.longName);
        }
        for (CmdLineOption option : options)
        {
            if (option.oShort)
                this->options.insert(make_pair(option.shortName, option.value));
            if (option.oLong)
                this->options.insert(make_pair(option.longName, option.value));
        }
        this->flagsList = flags;
        this->optionsList = options;
        this->args = args;
        this->flagsAndOptions = flagsAndOptions;
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

    void setArg(int index, wxString arg)
    {
        args[index] = arg;
    }

    void appendArg(wxString arg)
    {
        args.push_back(arg);
    }

    wxString toWxString()
    {
        wxString result;
        int iFlag = 0, iOption = 0;
        for (FlagOrOption flagOrOption : flagsAndOptions)
        {
            if (result != "")
                result.Append(" ");
            if (flagOrOption == FlagOrOption::Flag)
            {
                if (flagsList[iFlag].isShort)
                    result.Append("-" + flagsList[iFlag].shortName);
                else
                    result.Append("--" + flagsList[iFlag].longName);
                iFlag++;
            }
            else
            {
                if (optionsList[iOption].isShort)
                    result.Append("-" + optionsList[iOption].shortName);
                else
                    result.Append("--" + optionsList[iOption].longName);
                result.Append(" " + optionsList[iOption].value);
                iOption++;
            }
        }
        for (wxString arg : args)
        {
            if (result != "")
                result.Append(" ");
            result.Append(arg);
        }

        return result;
    }
};

class CmdLineParser
{
private:
    vector<CmdLineFlag> possibleFlags;
    vector<CmdLineOption> possibleOptions;

    int findInFlags(wxString flagName, bool isShort)
    {
        for (int i = 0; i < (int)possibleFlags.size(); i++)
        {
            CmdLineFlag f = possibleFlags[i];
            if ((isShort && f.fShort && f.shortName.IsSameAs(flagName)) ||
                (!isShort && f.fLong && f.longName.IsSameAs(flagName)))
                return i;
        }
        return -1;
    }

    int findInOptions(wxString optionName, bool isShort)
    {
        for (int i = 0; i < (int)possibleOptions.size(); i++)
        {
            CmdLineOption o = possibleOptions[i];
            if ((isShort && o.oShort && o.shortName.IsSameAs(optionName)) ||
                (!isShort && o.oLong && o.longName.IsSameAs(optionName)))
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
        vector<FlagOrOption> flagsAndOptions;

        int argc = argv.size();

        for (int i = 1; i < argc; i++)
        {
            wxString arg(argv[i]);
            if (arg.StartsWith(wxString("--")) || arg.StartsWith(wxString("-")))
            {
                wxString trimmedArg;
                bool isShort;
                if (arg.StartsWith(wxString("--")))
                {
                    trimmedArg = arg.SubString(2, arg.Len() - 1);
                    isShort = false;
                }
                else
                {
                    trimmedArg = arg.SubString(1, arg.Len() - 1);
                    isShort = true;
                }
                int pos = findInFlags(trimmedArg, isShort);
                if (pos != -1)
                {
                    CmdLineFlag flag = possibleFlags[pos];
                    flag.isShort = isShort;
                    flags.push_back(flag);
                    flagsAndOptions.push_back(FlagOrOption::Flag);
                }
                else
                {
                    pos = findInOptions(trimmedArg, isShort);
                    if (pos != -1 && i != argc - 1)
                    {
                        CmdLineOption o = possibleOptions[pos];
                        o.isShort = isShort;
                        o.value = argv[i + 1];
                        options.push_back(o);
                        flagsAndOptions.push_back(FlagOrOption::Option);
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

        return CmdLineArgs(flags, options, args, flagsAndOptions);
    }

    CmdLineArgs parseWithOneArg(wxString line)
    {
        vector<CmdLineFlag> flags;
        vector<CmdLineOption> options;
        vector<wxString> args;
        vector<FlagOrOption> flagsAndOptions;

        vector<wxString> tokens;
        vector<bool> isDelimeterToken;

        splitOnTokens(line, tokens, isDelimeterToken);

        trimTokens(tokens, isDelimeterToken);

        for (size_t i = 0; i < tokens.size(); i++)
        {
            if (!isDelimeterToken[i])
            {
                wxString trimmedToken;
                bool isShort = false;

                if (tokens[i].StartsWith(wxString("--")))
                {
                    trimmedToken = tokens[i].SubString(2, tokens[i].length() - 1);
                    isShort = false;
                }
                else if (tokens[i].StartsWith(wxString("-")))
                {
                    trimmedToken = tokens[i].SubString(1, tokens[i].length() - 1);
                    isShort = true;
                }

                int pos = findInFlags(trimmedToken, isShort);
                int iOptionValue;
                if (pos != -1)
                {
                    CmdLineFlag flag = possibleFlags[pos];
                    flag.isShort = isShort;
                    flags.push_back(flag);
                    flagsAndOptions.push_back(FlagOrOption::Flag);
                }
                else if ((pos = findInOptions(trimmedToken, isShort)) != -1 &&
                         (iOptionValue = findNextNotDelimeterToken(isDelimeterToken, i + 1)) != -1)
                {
                    CmdLineOption option = possibleOptions[pos];
                    option.isShort = isShort;
                    option.value = tokens[iOptionValue];
                    options.push_back(option);
                    flagsAndOptions.push_back(FlagOrOption::Option);
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

        return CmdLineArgs(flags, options, args, flagsAndOptions);
    }
};

#endif // CMDLINE_H_INCLUDED
