#ifndef CONCURRENCY_H_INCLUDED
#define CONCURRENCY_H_INCLUDED

#include <vector>
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

    static vector<Path> pathes;
    static long long version;
    static wxCriticalSection pathesExchangeCS;

    static void pushPath(long long version, Path path)
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        if (version == PathesExchange::version)
        {
            pathes.push_back(path);
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
        pathes.clear();
    }

    static vector<Path> popPathes()
    {
        wxCriticalSectionLocker enter(pathesExchangeCS);
        vector<Path> result = pathes;
        pathes.clear();
        return result;
    }
};

#endif // CONCURRENCY_H_INCLUDED
