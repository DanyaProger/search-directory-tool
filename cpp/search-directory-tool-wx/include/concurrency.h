#ifndef CONCURRENCY_H_INCLUDED
#define CONCURRENCY_H_INCLUDED

#include <queue>
#include <utility>
#include <wx/string.h>
#include <wx/thread.h>

using namespace std;

class SdTokenExchange
{
private:
    static wxCriticalSection sdTokenExchangeCS;
    static wxString sdToken;
    static double time;
    static long long version;

public:
    static double DEFAULT_TIME;

    static long long pushSdToken(long long newVersion, wxString sdToken)
    {
        wxCriticalSectionLocker enter(sdTokenExchangeCS);
        version = newVersion;
        SdTokenExchange::sdToken = sdToken;
        time = DEFAULT_TIME;
        return version;
    }

    static long long pushSdToken(long long newVersion, wxString sdToken, double time)
    {
        wxCriticalSectionLocker enter(sdTokenExchangeCS);
        version = newVersion;
        SdTokenExchange::sdToken = sdToken;
        SdTokenExchange::time = time;
        return version;
    }

    static long long getVersion()
    {
        wxCriticalSectionLocker enter(sdTokenExchangeCS);
        return version;
    }

    static bool updateWorker(long long& version, wxString& sdToken, double& time)
    {
        wxCriticalSectionLocker enter(sdTokenExchangeCS);
        bool isMatch = SdTokenExchange::version == version;
        if (!isMatch)
        {
            version = SdTokenExchange::version;
            sdToken = SdTokenExchange::sdToken;
            time = SdTokenExchange::time;
        }
        return !isMatch;
    }
};

enum class PercentageType {Alias, Relative, Absolute};

class PathesExchange
{
public:
    class Path
    {
    public:
        wxString fullPath;
        bool isDir;
        bool isFromDirsTxt;

        Path(wxString fullPath, bool isDir, bool isFromDirsTxt)
            :fullPath(fullPath), isDir(isDir), isFromDirsTxt(isFromDirsTxt)
        {
        }
    };

    static queue<Path> pathes;
    static queue<pair<PercentageType, int>> percentages;
    static long long version;
    static wxCriticalSection pathesExchangeCS;

    static void pushPath(long long version, Path path)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        if (version == PathesExchange::version)
        {
            pathes.push(path);
        }
    }

    static void updateVersion(long long version)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        PathesExchange::version = version;
    }

    static void clearPathes()
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        while (!pathes.empty()) pathes.pop();
    }

    static bool popPath(Path& inFront)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        if (!pathes.empty())
        {
            inFront = pathes.front();
            pathes.pop();
            return true;
        }
        else
            return false;
    }

    static void pushPercentage(long long version, pair<PercentageType, int> percentage)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        if (version == PathesExchange::version)
        {
            percentages.push(percentage);
        }
    }

    static bool popPercentage(pair<PercentageType, int>& percentage)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        if (!percentages.empty())
        {
            percentage = percentages.front();
            percentages.pop();
            return true;
        }
        else
            return false;
    }

    static void clearPercentages()
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        while (!percentages.empty()) percentages.pop();
    }
};

#endif // CONCURRENCY_H_INCLUDED
