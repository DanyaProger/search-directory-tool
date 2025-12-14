#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include <wx/string.h>
#include <wx/thread.h>
#include <vector>
#include <queue>
#include <windows.h>

#include "concurrency.h"

enum class SdTokenType {Slash, Asterisk, SubString};
enum class SearchExitCode {Success, Delete, Update, TimeLimit};

class Searcher
{
protected:
    class Path
    {
    public:
        wxString fullPath;
        bool isDir;
        bool isMatchingDir;
        Path(wxString fullPath, bool isDir)
            : fullPath(fullPath), isDir(isDir)
        {
        }

        Path(wxString fullPath, bool isDir, bool isMatchingDir)
            : fullPath(fullPath), isDir(isDir), isMatchingDir(isMatchingDir)
        {
        }
    };

    enum class LinkedSequenceType {DoubleAsterisk, LinkedSequence};
    enum class TokenSequenceType {StringDelimeterSequence, AsteriskSequence};
    enum class TokenType {Asterisk, String};
    enum class LineSequenceType {StringDelimeterSequence, AsteriskSequence, DoubleAsterisk};

    class TokenSequence
    {
    public:
        vector<wxString> tokens;
        vector<vector<long long>> prefixFunctions;
        vector<TokenType> tokensTypes;
    };

    class LinkedSequence
    {
    public:
        vector<TokenSequence> sequences;
        vector<TokenSequenceType> sequencesTypes;
    };

    class LineTokenSequence
    {
    public:
        vector<wxString> tokens;
        vector<TokenType> tokensTypes;
    };

    enum class MatchResult {MatchAndFull, MatchAndPartial, NoMatchAndFull, NoMatchAndPartial};

    wxThreadHelper* tHelper;
    long long version;
    wxString sdToken;
    double time;
    PercentageType pType;
    vector<LinkedSequence> linkedSequences;
    vector<LinkedSequenceType> linkedSequencesTypes;
    bool isAppendSlash = false;

    //long long iFirstMatchedChar;
    long long iLastMatchedChar;
    long long lastPrefixFunction;
    long long iLastPrefixFunctionProcessedChar;
    queue<long long> prefixFunctionMaximums;
    bool isFirstStringDelimeterSequence;
    TokenSequence stringDelimeterSequenceIsFirst;

    void onSuccessMatch(wxString& currentPath, bool& isDir)
    {
        PathesExchange::pushPath(version, PathesExchange::Path(currentPath, isDir, false));
    }

    void onPercentageChanged(int percentage)
    {
        PathesExchange::pushPercentage(version, make_pair(pType, percentage));
    }

    bool testDestroy()
    {
        return tHelper->GetThread()->TestDestroy();
    }

    bool updateWorker()
    {
        return SdTokenExchange::updateWorker(version, sdToken, time);
    }

    LineTokenSequence parseAsteriskSequence(wxString str)
    {
        LineTokenSequence sequence;
        for (int i = 0; i < str.Length(); i++)
            if (str.GetChar(i) != '*')
            {
                int j = i;
                while (j < (long long)str.Length() - 1 && str.GetChar(j + 1) != '*')
                    j++;
                sequence.tokens.push_back(str.SubString(i, j));
                sequence.tokensTypes.push_back(TokenType::String);

                i = j;
            } else
            {
                sequence.tokens.push_back("*");
                sequence.tokensTypes.push_back(TokenType::Asterisk);
            }
        return sequence;
    }

    vector<long long> KMP(wxString str)
    {
        vector<long long> prefixFunction(str.Length(), 0);
        for (int i = 1; i < str.Length(); i++)
        {
            long long t = prefixFunction[i - 1];
            while (t > 0 && str.GetChar(t) != str.GetChar(i))
                t = prefixFunction[t - 1];
            if (str.GetChar(t) == str.GetChar(i))
                prefixFunction[i] = t + 1;
        }

        return prefixFunction;
    }

    /*vector<long long> KMP(wxString str, wxString& sample, vector<long long>& samplePrefixFunction)
    {

    }*/

    long long calcPrefixFunction(long long pf, wxUniChar ch, wxString str, vector<long long> prefixFunction)
    {
        while (pf > 0 && str.GetChar(pf) != ch)
            pf = prefixFunction[pf - 1];
        if (str.GetChar(pf) == ch)
            pf = pf + 1;
        return pf;
    }

    void calcPrefixFunctions()
    {
        for (int iLSequence = 0; iLSequence < linkedSequences.size(); iLSequence++)
        {
            if (linkedSequencesTypes[iLSequence] == LinkedSequenceType::LinkedSequence)
            {
                for (int iSequence = 0; iSequence < linkedSequences[iLSequence].sequences.size(); iSequence++)
                {
                    TokenSequence& sequence = linkedSequences[iLSequence].sequences[iSequence];
                    for (int iToken = 0; iToken < sequence.tokens.size(); iToken++)
                    {
                        if (sequence.tokensTypes[iToken] == TokenType::Asterisk)
                        {
                            sequence.prefixFunctions.push_back(vector<long long>());
                        }
                        if (sequence.tokensTypes[iToken] == TokenType::String)
                        {
                            sequence.prefixFunctions.push_back(KMP(sequence.tokens[iToken]));
                        }
                    }
                }
            }
        }
    }

    void parseExpression(wxString expression)
    {
        expression.Replace("/", "\\");

        vector<int> processed(expression.Length(), -1);
        vector<LineTokenSequence> seqs;
        vector<LineSequenceType> types;
        int iSequence = -1;
        linkedSequences.clear();
        linkedSequencesTypes.clear();

        int asteriskCount = 0;
        for (int i = 0; i < expression.Length(); i++)
            if (expression.GetChar(i) == '*')
                asteriskCount++;
            else
            {
                if (asteriskCount > 1)
                {
                    iSequence++;
                    seqs.push_back(LineTokenSequence());
                    types.push_back(LineSequenceType::DoubleAsterisk);
                    for (int j = i - asteriskCount; j < i; j++)
                        processed[j] = iSequence;
                }
                asteriskCount = 0;
            }
        if (asteriskCount > 1)
        {
            iSequence++;
            seqs.push_back(LineTokenSequence());
            types.push_back(LineSequenceType::DoubleAsterisk);
            for (int j = (long long)expression.Length() - asteriskCount; j < expression.Length(); j++)
                processed[j] = iSequence;
        }

        for (int i = 0; i < expression.Length(); i++)
            if (processed[i] == -1)
            {
                if (expression.GetChar(i) == '*')
                {
                    int l = i, r = i;
                    while (l > 0 && processed[l - 1] == -1 && expression.GetChar(l - 1) != '\\')
                        l--;
                    while (r < (long long)expression.Length() - 1 && processed[r + 1] == -1 && expression.GetChar(r + 1) != '\\')
                        r++;

                    iSequence++;
                    types.push_back(LineSequenceType::AsteriskSequence);
                    seqs.push_back(parseAsteriskSequence(expression.SubString(l, r)));

                    for (int j = l; j <= r; j++)
                        processed[j] = iSequence;
                }
            }

        for (int i = 0; i < expression.Length(); i++)
            if (processed[i] == -1)
            {
                int j = i;
                while (j < (long long)expression.Length() - 1 && processed[j + 1] == -1)
                    j++;

                iSequence++;
                types.push_back(LineSequenceType::StringDelimeterSequence);
                LineTokenSequence seq;
                seq.tokens.push_back(expression.SubString(i, j));
                seq.tokensTypes.push_back(TokenType::String);
                seqs.push_back(seq);

                for (int k = i; k <= j; k++)
                    processed[k] = iSequence;
            }

        for (int i = 0; i < processed.size(); i++)
        {
            int iSequence = processed[i];
            if (types[iSequence] == LineSequenceType::DoubleAsterisk)
            {
                linkedSequencesTypes.push_back(LinkedSequenceType::DoubleAsterisk);
                linkedSequences.push_back(LinkedSequence());
            }
            else if (types[iSequence] == LineSequenceType::AsteriskSequence)
            {
                if (linkedSequencesTypes.size() == 0 || linkedSequencesTypes.back() == LinkedSequenceType::DoubleAsterisk)
                {
                    linkedSequencesTypes.push_back(LinkedSequenceType::LinkedSequence);
                    linkedSequences.push_back(LinkedSequence());
                }
                TokenSequence ts;
                ts.tokens = seqs[iSequence].tokens;
                ts.tokensTypes = seqs[iSequence].tokensTypes;
                linkedSequences.back().sequences.push_back(ts);
                linkedSequences.back().sequencesTypes.push_back(TokenSequenceType::AsteriskSequence);
            }
            else // StringDelimeterSequence
            {
                if (linkedSequencesTypes.size() == 0 || linkedSequencesTypes.back() == LinkedSequenceType::DoubleAsterisk)
                {
                    linkedSequencesTypes.push_back(LinkedSequenceType::LinkedSequence);
                    linkedSequences.push_back(LinkedSequence());
                }
                TokenSequence ts;
                ts.tokens = seqs[iSequence].tokens;
                ts.tokensTypes = seqs[iSequence].tokensTypes;
                linkedSequences.back().sequences.push_back(ts);
                linkedSequences.back().sequencesTypes.push_back(TokenSequenceType::StringDelimeterSequence);
            }

            int j = i;
            while (j < processed.size() - 1 && processed[j + 1] == processed[i])
                j++;
            i = j;
        }

        isAppendSlash = false;
        if (linkedSequencesTypes.size() > 0 && linkedSequencesTypes.back() == LinkedSequenceType::LinkedSequence &&
            linkedSequences.back().sequencesTypes.back() == TokenSequenceType::StringDelimeterSequence)
        {
            wxString token = linkedSequences.back().sequences.back().tokens[0];
            if (token.GetChar((long long)token.Length() - 1) == '\\')
            {
                token.RemoveLast(1);
                isAppendSlash = true;
                linkedSequences.back().sequences.back().tokens[0] = token;
                if (token.Length() == 0)
                {
                    linkedSequences.back().sequences.pop_back();
                    linkedSequences.back().sequencesTypes.pop_back();
                    if (linkedSequences.back().sequences.size() == 0)
                    {
                        linkedSequences.pop_back();
                        linkedSequencesTypes.pop_back();
                    }
                }
            }
        }



        calcPrefixFunctions();
    }

    void initFields(wxString expression, PercentageType pType, wxThreadHelper* tHelper,
                    long long& version, wxString& sdToken, double& time)
    {
        this->pType = pType;
        this->tHelper = tHelper;
        this->version = version;
        this->sdToken = sdToken;
        this->time = time;
        parseExpression(expression);
    }

    void cloneFields(long long& version, wxString& sdToken, double& time)
    {
        version = this->version;
        sdToken = this->sdToken;
        time = this->time;
    }

    void loadFileNamesInCurrentPath(wxString currentPath, vector<Path>& pathes)
    {
        pathes.clear();

        WIN32_FIND_DATAW ffd;

        int sz;
        HANDLE h = FindFirstFileW((currentPath + "\\*").c_str(), &ffd);

        if (h == INVALID_HANDLE_VALUE)
            return;
        do {
            wxString fileName(ffd.cFileName);
            if (fileName == "." || fileName == "..")
                continue;
            Path path = Path(fileName, false);
            if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                path.isDir = true;
            } else
            {
                path.isDir = false;
            }
            pathes.push_back(path);
        } while (FindNextFileW(h, &ffd) != 0);
        FindClose(h);
        return;
    }

    void matchSequenceReset(long long& iLastProcessedChar, TokenSequence sequence, TokenSequenceType sequenceType)
    {
        iLastMatchedChar = iLastProcessedChar;
        if (sequenceType == TokenSequenceType::StringDelimeterSequence)
        {
            lastPrefixFunction = 0;
            while (!prefixFunctionMaximums.empty())
                prefixFunctionMaximums.pop();
            iLastPrefixFunctionProcessedChar = iLastProcessedChar;
            isFirstStringDelimeterSequence = true;
            stringDelimeterSequenceIsFirst = sequence;
        }
        else
            isFirstStringDelimeterSequence = false;
    }

    bool matchSeq(wxString& lowerPath, TokenSequence& sequence, TokenSequenceType& sequenceType, long long& iLastProcessedChar, bool isLast, bool hasNextInLinkedSequence, bool& isFullCoverage)
    {
        isFullCoverage = false;
        if (sequenceType == TokenSequenceType::StringDelimeterSequence)
        {
            bool isMatch = true;
            if (iLastProcessedChar + (long long)sequence.tokens[0].Length() < (long long)lowerPath.Length())
            {
                for (int i = 0; i < sequence.tokens[0].Length(); i++)
                {
                    if (isFirstStringDelimeterSequence && iLastProcessedChar + 1 + i == iLastPrefixFunctionProcessedChar + 1)
                    {
                        iLastPrefixFunctionProcessedChar++;
                        lastPrefixFunction = calcPrefixFunction(lastPrefixFunction, lowerPath.GetChar(iLastPrefixFunctionProcessedChar), stringDelimeterSequenceIsFirst.tokens[0], stringDelimeterSequenceIsFirst.prefixFunctions[0]);
                        if (lastPrefixFunction == stringDelimeterSequenceIsFirst.tokens[0].Length())
                            prefixFunctionMaximums.push(iLastPrefixFunctionProcessedChar);
                    }
                    if (sequence.tokens[0].GetChar(i) != lowerPath.GetChar(iLastProcessedChar + 1 + i))
                    {
                        isMatch = false;
                        break;
                    }
                }
            }
            else
            {
                isMatch = false;
            }
            if (isMatch && (!isLast || iLastProcessedChar + (long long)sequence.tokens[0].Length() == (long long)lowerPath.Length() - 1))
            {
                if (iLastProcessedChar + (long long)sequence.tokens[0].Length() == (long long)lowerPath.Length() - 1)
                    isFullCoverage = true;
                iLastProcessedChar = iLastProcessedChar + (long long)sequence.tokens[0].Length();
                return true;
            }
            else
            {
                if (iLastProcessedChar + (long long)sequence.tokens[0].Length() >= (long long)lowerPath.Length() &&
                    lowerPath.SubString(iLastProcessedChar + 1, (long long)lowerPath.Length() - 1).IsSameAs(sequence.tokens[0].SubString(0, (long long)lowerPath.Length() - 1 - (iLastProcessedChar + 1))))
                    isFullCoverage = true;
                return false;
            }
        }
        else
        {
            long long pf = 0;
            bool isAsterisk = false;
            long long iFirstNotMatchedToken = 0;
            long long iChar = iLastProcessedChar;
            while (iFirstNotMatchedToken != sequence.tokens.size())
            {
                if (sequence.tokensTypes[iFirstNotMatchedToken] == TokenType::Asterisk)
                {
                    isAsterisk = true;
                    iFirstNotMatchedToken++;
                }
                else
                {
                    pf = 0;
                    long long iLastProcessedCharForString = iChar;
                    bool isMatch = false;
                    while (iLastProcessedCharForString < (long long)lowerPath.Length() - 1 && lowerPath.GetChar(iLastProcessedCharForString + 1) != '\\')
                    {
                        iLastProcessedCharForString++;
                        if (isFirstStringDelimeterSequence && iLastProcessedCharForString == iLastPrefixFunctionProcessedChar + 1)
                        {
                            iLastPrefixFunctionProcessedChar++;
                            lastPrefixFunction = calcPrefixFunction(lastPrefixFunction, lowerPath.GetChar(iLastPrefixFunctionProcessedChar), stringDelimeterSequenceIsFirst.tokens[0], stringDelimeterSequenceIsFirst.prefixFunctions[0]);
                            if (lastPrefixFunction == (long long)stringDelimeterSequenceIsFirst.tokens[0].Length())
                                prefixFunctionMaximums.push(iLastPrefixFunctionProcessedChar);
                        }
                        pf = calcPrefixFunction(pf, lowerPath.GetChar(iLastProcessedCharForString), sequence.tokens[iFirstNotMatchedToken], sequence.prefixFunctions[iFirstNotMatchedToken]);
                        if (!isAsterisk && iLastProcessedCharForString - iChar != pf)
                        {
                            return false;
                        }
                        if (pf == sequence.tokens[iFirstNotMatchedToken].Length() &&
                            (iFirstNotMatchedToken < (long long)sequence.tokens.size() - 1 ||
                             ((!isLast || iLastProcessedCharForString == (long long)lowerPath.Length() - 1) &&
                              (!hasNextInLinkedSequence || iLastProcessedCharForString == (long long)lowerPath.Length() - 1 || lowerPath.GetChar(iLastProcessedCharForString + 1) == '\\')
                             )
                            )
                           )
                        {
                            isMatch = true;
                            break;
                        }
                    }
                    if (!isMatch)
                        return false;
                    else
                    {
                        iChar = iLastProcessedCharForString;
                        iFirstNotMatchedToken++;
                    }
                    isAsterisk = false;
                }

            }
            iLastProcessedChar = iChar;
            if (isAsterisk)
            {
                while (iLastProcessedChar + 1 < (long long)lowerPath.Length() && lowerPath.GetChar(iLastProcessedChar + 1) != '\\')
                {
                    iLastProcessedChar++;
                    if (isFirstStringDelimeterSequence && iLastProcessedChar == iLastPrefixFunctionProcessedChar + 1)
                    {
                        iLastPrefixFunctionProcessedChar++;
                        lastPrefixFunction = calcPrefixFunction(lastPrefixFunction, lowerPath.GetChar(iLastPrefixFunctionProcessedChar), stringDelimeterSequenceIsFirst.tokens[0], stringDelimeterSequenceIsFirst.prefixFunctions[0]);
                        if (lastPrefixFunction == (long long)stringDelimeterSequenceIsFirst.tokens[0].Length())
                            prefixFunctionMaximums.push(iLastPrefixFunctionProcessedChar);
                    }
                }
            }
            if (iLastProcessedChar == (long long)lowerPath.Length() - 1)
                isFullCoverage = true;
            return true;
        }
    }

    bool matchFirstSeq(wxString& lowerPath, TokenSequence& sequence, TokenSequenceType& sequenceType, bool isDoubleAsterisk, bool isLast, bool hasNextInLinkedSequence, bool& isFullCoverage)
    {
        isFullCoverage = false;
        if (sequenceType == TokenSequenceType::StringDelimeterSequence)
        {
            long long cnt = 0;
            while (prefixFunctionMaximums.empty() &&
                   iLastPrefixFunctionProcessedChar < (long long)lowerPath.Length() - 1 &&
                   (isDoubleAsterisk || (iLastPrefixFunctionProcessedChar < iLastMatchedChar + (long long)sequence.tokens[0].Length()))
                   )
            {
                cnt++;
                iLastPrefixFunctionProcessedChar++;
                lastPrefixFunction = calcPrefixFunction(lastPrefixFunction, lowerPath.GetChar(iLastPrefixFunctionProcessedChar), sequence.tokens[0], sequence.prefixFunctions[0]);
                if (lastPrefixFunction == sequence.tokens[0].Length() && (!isLast || iLastPrefixFunctionProcessedChar == (long long)lowerPath.Length() - 1))
                    prefixFunctionMaximums.push(iLastPrefixFunctionProcessedChar);
            }
            if (!prefixFunctionMaximums.empty())
            {
                long long i = prefixFunctionMaximums.front();
                if (i == (long long)lowerPath.Length() - 1)
                    isFullCoverage = true;
                prefixFunctionMaximums.pop();
                //iFirstMatchedChar = i - sequence.tokens[0].Length() + 1;
                iLastMatchedChar = i;
                return true;
            } else
            {
                if (isDoubleAsterisk || (iLastPrefixFunctionProcessedChar == (long long)lowerPath.Length() - 1 && lastPrefixFunction == cnt))
                    isFullCoverage = true;
                return false;
            }
        }
        else
        {
            while (true)
            {
                long long pf = 0;
                bool isAsterisk = false;
                long long iFirstNotMatchedToken = 0;
                long long iChar = iLastMatchedChar;
                bool isMatch = false;
                if (isDoubleAsterisk && iChar + 1 < (long long)lowerPath.Length() && lowerPath.GetChar(iChar + 1) == '\\')
                    iChar++;
                if (iChar == (long long)lowerPath.Length() - 1)
                {
                    if (isDoubleAsterisk)
                        isFullCoverage = true;
                    return false;
                }
                while (iFirstNotMatchedToken != sequence.tokens.size())
                {
                    if (sequence.tokensTypes[iFirstNotMatchedToken] == TokenType::Asterisk)
                    {
                        isAsterisk = true;
                        iFirstNotMatchedToken++;
                    }
                    else
                    {
                        pf = 0;
                        long long iLastProcessedCharForString = iChar;
                        isMatch = false;
                        while (iLastProcessedCharForString < (long long)lowerPath.Length() - 1 && lowerPath.GetChar(iLastProcessedCharForString + 1) != '\\')
                        {
                            iLastProcessedCharForString++;
                            pf = calcPrefixFunction(pf, lowerPath.GetChar(iLastProcessedCharForString), sequence.tokens[iFirstNotMatchedToken], sequence.prefixFunctions[iFirstNotMatchedToken]);
                            if (!isAsterisk && !isDoubleAsterisk && iLastProcessedCharForString - iChar != pf)
                            {
                                isMatch = false;
                                break;
                            }
                            if (pf == sequence.tokens[iFirstNotMatchedToken].Length() &&
                                (iFirstNotMatchedToken < (long long)sequence.tokens.size() - 1 ||
                                 ((!isLast || iLastProcessedCharForString == (long long)lowerPath.Length() - 1) &&
                                  (!hasNextInLinkedSequence || iLastProcessedCharForString == (long long)lowerPath.Length() - 1 || lowerPath.GetChar(iLastProcessedCharForString + 1) == '\\')
                                 )
                                )
                               )
                            {
                                isMatch = true;
                                break;
                            }
                        }
                        if (!isMatch)
                            break;
                        else
                        {
                            iChar = iLastProcessedCharForString;
                            iFirstNotMatchedToken++;
                        }
                        isAsterisk = false;
                    }

                }
                if (!isMatch)
                {
                    if (isDoubleAsterisk)
                    {
                        while (iLastMatchedChar + 1 < (long long)lowerPath.Length() && lowerPath.GetChar(iLastMatchedChar + 1) != '\\')
                            iLastMatchedChar++;
                    }
                }
                else
                {
                    iLastMatchedChar = iChar;
                    if (isAsterisk)
                    {
                        while (iLastMatchedChar + 1 < (long long)lowerPath.Length() && lowerPath.GetChar(iLastMatchedChar + 1) != '\\')
                        {
                            iLastMatchedChar++;
                        }
                    }

                    if (iLastMatchedChar == (long long)lowerPath.Length() - 1)
                        isFullCoverage = true;
                    return true;
                }
            }
        }
    }

    bool processLinkedSequence(LinkedSequence& linkedSequence, wxString& lowerPath,
                               long long& iLastChar,
                               bool isDoubleAsterisk,
                               bool isLast,
                               bool& isFullCoverage)
    {
        isFullCoverage = false;
        bool newIsFullCoverage;
        long long iLastProcessedChar = iLastChar;
        int iFirstNotMatchedSeq;
        matchSequenceReset(iLastProcessedChar, linkedSequence.sequences[0], linkedSequence.sequencesTypes[0]);
        while (true)
        {
            if (!matchFirstSeq(lowerPath, linkedSequence.sequences[0], linkedSequence.sequencesTypes[0], isDoubleAsterisk, isLast && linkedSequence.sequences.size() == 1, linkedSequence.sequences.size() > 1, newIsFullCoverage))
            {
                isFullCoverage = isFullCoverage || newIsFullCoverage;
                iLastChar = iLastProcessedChar;
                return false;
            }
            else
            {
                isFullCoverage = isFullCoverage || newIsFullCoverage;
                iFirstNotMatchedSeq = 1;
                iLastProcessedChar = iLastMatchedChar;
            }
            while (iFirstNotMatchedSeq < linkedSequence.sequences.size())
            {
                if (matchSeq(lowerPath, linkedSequence.sequences[iFirstNotMatchedSeq], linkedSequence.sequencesTypes[iFirstNotMatchedSeq], iLastProcessedChar, isLast && linkedSequence.sequences.size() - 1 == iFirstNotMatchedSeq, linkedSequence.sequences.size() > iFirstNotMatchedSeq + 1, newIsFullCoverage))
                {
                    isFullCoverage = isFullCoverage || newIsFullCoverage;
                    iFirstNotMatchedSeq++;
                }
                else
                {
                    isFullCoverage = isFullCoverage || newIsFullCoverage;
                    break;
                }
            }
            if (iFirstNotMatchedSeq == linkedSequence.sequences.size())
            {
                iLastChar = iLastProcessedChar;
                return true;
            }
        }
    }

    MatchResult match(Path path)
    {
        /**
        hello**tank*i*onli**ne
        **tanki/online**
        doubleASeq = (**)?(ASeq||strDelSeq)(**)?(ASeq||strDelSeq)(**)? // (str1*str2)/(str3*str4*str5)
        strDelSeq = (\)?str1\str2(\)?   // str1*str2/str3 -> (str1*str2)/str3
        ASeq = *str1*str2*str3*

        aaa/aaa/aaa/aaa/ab
        aaa/aaa/ab или (aaa/aaa/)(*b)
        **/

        long long iLastProcessedChar = -1;
        bool isDoubleAsterisk = false;
        bool isDoubleAsteriskAtAll = false;
        wxString lowerPath = path.fullPath.Lower();
        for (int iLSequence = 0; iLSequence < linkedSequences.size(); iLSequence++)
        {
            if (linkedSequencesTypes[iLSequence] == LinkedSequenceType::DoubleAsterisk)
            {
                isDoubleAsterisk = true;
                isDoubleAsteriskAtAll = true;
            }
            if (linkedSequencesTypes[iLSequence] == LinkedSequenceType::LinkedSequence)
            {
                bool processResult;
                bool isFullCoverage = false;
                if (isAppendSlash && !path.isDir)
                    processResult = false;
                else
                    processResult = processLinkedSequence(linkedSequences[iLSequence],
                                                           lowerPath,
                                                           iLastProcessedChar,
                                                           isDoubleAsterisk,
                                                           iLSequence == linkedSequences.size() - 1,
                                                           isFullCoverage
                                                          );
                if (!processResult)
                {
                    if (isDoubleAsteriskAtAll || isFullCoverage)
                        return MatchResult::NoMatchAndPartial;
                    else
                        return MatchResult::NoMatchAndFull;
                }
                isDoubleAsterisk = false;
            }
        }
        if (iLastProcessedChar == (long long)lowerPath.Length() - 1)
        {
            if (isDoubleAsteriskAtAll)
                return MatchResult::MatchAndPartial;
            else
                return MatchResult::MatchAndFull;
        }
        else if (isDoubleAsterisk)
        {
            return MatchResult::MatchAndPartial;
        }

        if (isDoubleAsteriskAtAll)
            return MatchResult::NoMatchAndPartial;
        else
            return MatchResult::NoMatchAndFull;
    }

public:
    virtual SearchExitCode search(wxString currentDir, wxString expression,
                                  PercentageType pType, wxThreadHelper* tHelper,
                                  long long& version, wxString& sdToken, double& time)
    {
        return SearchExitCode::Success;
    }
};

class BfsSearcher : public Searcher
{
private:
    SearchExitCode bfs(wxString currentDir)
    {
        queue<Path> allPathes;
        allPathes.push(Path(L"", true, true));
        while (!allPathes.empty())
        {
            if (testDestroy())
                return SearchExitCode::Delete;
            if (updateWorker())
                return SearchExitCode::Update;

            Path path = allPathes.front();
            allPathes.pop();

            MatchResult mResult = match(path);
            if ((mResult == MatchResult::MatchAndFull || mResult == MatchResult::MatchAndPartial))
            {
                wregex re(L"[A-Za-z]:");
                wsmatch m;
                if (regex_match(currentDir.ToStdWstring(), m, re) && path.fullPath == L"")
                {
                    path.fullPath.Append("\\");
                    currentDir.Append(path.fullPath);
                    onSuccessMatch(currentDir, path.isDir);
                    currentDir.RemoveLast(path.fullPath.Length());
                    path.fullPath.RemoveLast(1);
                }
                else
                {
                    if (!isAppendSlash)
                    {
                        currentDir.Append(path.fullPath);
                        onSuccessMatch(currentDir, path.isDir);
                        currentDir.RemoveLast(path.fullPath.Length());
                    }
                    else
                    {
                        path.fullPath.Append("\\");
                        currentDir.Append(path.fullPath);
                        onSuccessMatch(currentDir, path.isDir);
                        currentDir.RemoveLast(path.fullPath.Length());
                        path.fullPath.RemoveLast(1);
                    }
                }
            }
            if (mResult == MatchResult::MatchAndPartial || mResult == MatchResult::NoMatchAndPartial)
            {
                vector<Path> pathes;
                loadFileNamesInCurrentPath(currentDir + path.fullPath, pathes);

                for (int i = 0; i < pathes.size(); i++)
                {
                    pathes[i].fullPath = path.fullPath + "\\" + pathes[i].fullPath;
                    allPathes.push(pathes[i]);
                }
            }
        }

        return SearchExitCode::Success;
    }
public:
    SearchExitCode search(wxString currentDir, wxString expression,
                          PercentageType pType, wxThreadHelper* tHelper,
                          long long& version, wxString& sdToken, double& time) override
    {
        initFields(expression, pType, tHelper, version, sdToken, time);

        SearchExitCode exitCode = bfs(currentDir);

        cloneFields(version, sdToken, time);

        return exitCode;
    }
};

#endif // SEARCH_H_INCLUDED
