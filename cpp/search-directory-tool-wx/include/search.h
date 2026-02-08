#ifndef SEARCH_H_INCLUDED
#define SEARCH_H_INCLUDED

#include <wx/string.h>
#include <wx/thread.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <vector>
#include <queue>
#include <string>
#include <windows.h>
#include <regex>

#include "concurrency.h"
#include "search_tree.h"
#include "percentage.h"
#include "RecordsDispatcher.h"

using namespace std;

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
    enum class TokenSequenceType {Delimeter, FileNameSequence};
    enum class TokenType {Asterisk, String};
    enum class LineSequenceType {Delimeter, FileNameSequence, DoubleAsterisk};

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

    const wxString exePath = wxStandardPaths::Get().GetExecutablePath();

    wxThreadHelper* tHelper;
    long long version;
    wxString sdToken;
    double time;
    PercentageType pType;
    vector<LinkedSequence> linkedSequences;
    vector<LinkedSequenceType> linkedSequencesTypes;
    bool isAppendSlash = false;

    FileTree fileTree;

    void onSuccessMatch(wxString& currentPath, bool isDir)
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

    LineTokenSequence parseFileNameSequence(wxString str)
    {
        LineTokenSequence sequence;
        for (int i = 0; i < (int)str.Length(); i++)
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
        for (int i = 1; i < (int)str.Length(); i++)
        {
            long long t = prefixFunction[i - 1];
            while (t > 0 && str.GetChar(t) != str.GetChar(i))
                t = prefixFunction[t - 1];
            if (str.GetChar(t) == str.GetChar(i))
                prefixFunction[i] = t + 1;
        }

        return prefixFunction;
    }

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
        for (int iLSequence = 0; iLSequence < (long long)(linkedSequences.size()); iLSequence++)
        {
            if (linkedSequencesTypes[iLSequence] == LinkedSequenceType::LinkedSequence)
            {
                for (int iSequence = 0; iSequence < (long long)(linkedSequences[iLSequence].sequences.size()); iSequence++)
                {
                    TokenSequence& sequence = linkedSequences[iLSequence].sequences[iSequence];
                    for (int iToken = 0; iToken < (long long)(sequence.tokens.size()); iToken++)
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

    void parseSdToken(wxString expression)
    {
        expression.Replace("/", "\\");
        expression.MakeLower();

        vector<int> processed(expression.Length(), -1);
        vector<LineTokenSequence> seqs;
        vector<LineSequenceType> types;
        int iSequence = -1;
        linkedSequences.clear();
        linkedSequencesTypes.clear();

        int asteriskCount = 0;
        for (int i = 0; i < (int)expression.Length(); i++)
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
            for (int j = (int)expression.Length() - asteriskCount; j < (int)expression.Length(); j++)
                processed[j] = iSequence;
        }

        for (int i = 0; i < (int)expression.Length(); i++)
            if (expression.GetChar(i) == '\\')
            {
                iSequence++;
                types.push_back(LineSequenceType::Delimeter);
                LineTokenSequence seq;
                seq.tokens.push_back("\\");
                seq.tokensTypes.push_back(TokenType::String);
                seqs.push_back(seq);

                processed[i] = iSequence;
            }

        for (int i = 0; i < (int)expression.Length(); i++)
            if (processed[i] == -1)
            {
                int l = i, r = i;
                while (l > 0 && processed[l - 1] == -1 && expression.GetChar(l - 1) != '\\')
                    l--;
                while (r < (long long)expression.Length() - 1 && processed[r + 1] == -1 && expression.GetChar(r + 1) != '\\')
                    r++;

                iSequence++;
                types.push_back(LineSequenceType::FileNameSequence);
                seqs.push_back(parseFileNameSequence(expression.SubString(l, r)));

                for (int j = l; j <= r; j++)
                    processed[j] = iSequence;
            }

        for (int i = 0; i < (int)processed.size(); i++)
        {
            int iSequence = processed[i];
            if (types[iSequence] == LineSequenceType::DoubleAsterisk)
            {
                linkedSequencesTypes.push_back(LinkedSequenceType::DoubleAsterisk);
                linkedSequences.push_back(LinkedSequence());
            }
            else if (types[iSequence] == LineSequenceType::FileNameSequence)
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
                linkedSequences.back().sequencesTypes.push_back(TokenSequenceType::FileNameSequence);
            }
            else
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
                linkedSequences.back().sequencesTypes.push_back(TokenSequenceType::Delimeter);
            }

            int j = i;
            while (j < (int)processed.size() - 1 && processed[j + 1] == processed[i])
                j++;
            i = j;
        }

        isAppendSlash = false;
        if (linkedSequencesTypes.size() > 0 && linkedSequencesTypes.back() == LinkedSequenceType::LinkedSequence &&
            linkedSequences.back().sequencesTypes.back() == TokenSequenceType::Delimeter)
        {
            isAppendSlash = true;

            linkedSequences.back().sequences.pop_back();
            linkedSequences.back().sequencesTypes.pop_back();
            if (linkedSequences.back().sequences.size() == 0)
            {
                linkedSequences.pop_back();
                linkedSequencesTypes.pop_back();
            }
        }

        calcPrefixFunctions();
    }

    void initFields(wxThreadHelper* tHelper,
                    long long& version, wxString& sdToken, double& time)
    {
        this->tHelper = tHelper;
        this->version = version;
        this->sdToken = sdToken;
        this->time = time;
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

        HANDLE h = FindFirstFileW((currentPath + "\\*").c_str(), &ffd);
        if (h == INVALID_HANDLE_VALUE)
        {
            return;
        }
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

    bool matchSeq(long long currentNodeId, long long& currentNodeLastMatchedChar, TokenSequence& sequence, TokenSequenceType& sequenceType, bool isLast, bool hasNextInLinkedSequence)
    {
        if (sequenceType == TokenSequenceType::Delimeter)
        {
            bool isMatch = true;
            if (!isLast && currentNodeLastMatchedChar + 1 < fileTree.getNodeLength(currentNodeId))
            {
                if (fileTree.getNodeChar(currentNodeId, currentNodeLastMatchedChar + 1) != '\\')
                {
                    isMatch = false;
                }
            }
            else
            {
                isMatch = false;
            }
            if (isMatch)
            {
                currentNodeLastMatchedChar++;
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            long long pf = 0;
            bool isAsterisk = false;
            long long iFirstNotMatchedToken = 0;
            long long iChar = currentNodeLastMatchedChar;
            while (iFirstNotMatchedToken != (long long)sequence.tokens.size())
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
                    while (iLastProcessedCharForString < fileTree.getNodeLength(currentNodeId) - 1 && fileTree.getNodeChar(currentNodeId, iLastProcessedCharForString + 1) != '\\')
                    {
                        iLastProcessedCharForString++;
                        pf = calcPrefixFunction(pf, fileTree.getNodeChar(currentNodeId, iLastProcessedCharForString), sequence.tokens[iFirstNotMatchedToken], sequence.prefixFunctions[iFirstNotMatchedToken]);
                        if (!isAsterisk && iLastProcessedCharForString - iChar != pf)
                        {
                            return false;
                        }
                        if (pf == (long long)sequence.tokens[iFirstNotMatchedToken].Length() &&
                            (iFirstNotMatchedToken < (long long)sequence.tokens.size() - 1 ||
                             ((!isLast || iLastProcessedCharForString == fileTree.getNodeLength(currentNodeId) - 1) &&
                              (!hasNextInLinkedSequence || iLastProcessedCharForString == fileTree.getNodeLength(currentNodeId) - 1 || fileTree.getNodeChar(currentNodeId, iLastProcessedCharForString + 1) == '\\')
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
            currentNodeLastMatchedChar = iChar;
            if (isAsterisk)
            {
                currentNodeLastMatchedChar = fileTree.getNodeLength(currentNodeId) - 1;
            }
            return true;
        }
    }

    bool matchFirstSeq(vector<FileTree::DelimeterFileNameNode*>& processingNodes,
                       long long& iFirstSeqNode,
                       long long& firstSeqNodeLastMatchedChar,
                       TokenSequence& sequence, TokenSequenceType& sequenceType,
                       bool isDoubleAsterisk, bool isLast, bool hasNextInLinkedSequence,
                       bool& skipped)
    {
        skipped = false;
        long long firstSeqNodeId = processingNodes[iFirstSeqNode]->nodeId;
        if (sequenceType == TokenSequenceType::Delimeter)
        {
            long long i;
            bool match;
            if (!isLast)
            {
                if (!isDoubleAsterisk)
                {
                    if (firstSeqNodeLastMatchedChar + 1 < fileTree.getNodeLength(firstSeqNodeId) && fileTree.getNodeChar(firstSeqNodeId, firstSeqNodeLastMatchedChar + 1) == '\\')
                    {
                        match = true;
                        i = firstSeqNodeLastMatchedChar + 1;
                    }
                    else
                        match = false;
                } else
                {
                    long long pos;
                    if (firstSeqNodeLastMatchedChar == -1)
                        pos = 0;
                    else
                    {
                        iFirstSeqNode++;
                        firstSeqNodeLastMatchedChar = -1;
                        if (iFirstSeqNode != (long long)processingNodes.size())
                        {
                            pos = 0;
                        }
                        else
                        {
                            skipped = true;
                            return true;
                        }
                    }
                    if (pos != -1)
                    {
                        match = true;
                        i = pos;
                    }
                    else
                    {
                        match = false;
                    }
                }
            }
            else
                match = false;
            if (match)
            {
                firstSeqNodeLastMatchedChar = i;
                return true;
            } else
            {
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
                long long iChar = firstSeqNodeLastMatchedChar;
                bool isMatch = false;
                if (isDoubleAsterisk)
                {
                    if (iFirstSeqNode != (long long)processingNodes.size() - 1 && firstSeqNodeLastMatchedChar == fileTree.getNodeLength(firstSeqNodeId) - 1)
                    {
                        iFirstSeqNode++;
                        firstSeqNodeId = processingNodes[iFirstSeqNode]->nodeId;
                        firstSeqNodeLastMatchedChar = -1;
                        iChar = -1;
                    }
                    if (iChar + 1 < fileTree.getNodeLength(firstSeqNodeId) && fileTree.getNodeChar(firstSeqNodeId, iChar + 1) == '\\')
                    {
                        iChar++;
                        firstSeqNodeLastMatchedChar++;
                    }
                }
                if (iFirstSeqNode == (long long)processingNodes.size() - 1 && iChar == fileTree.getNodeLength(firstSeqNodeId) - 1)
                {
                    if (isDoubleAsterisk)
                    {
                        skipped = true;
                        return true;
                    }
                    return false;
                }
                while (iFirstNotMatchedToken != (long long)sequence.tokens.size())
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
                        while (iLastProcessedCharForString < fileTree.getNodeLength(firstSeqNodeId) - 1 && fileTree.getNodeChar(firstSeqNodeId, iLastProcessedCharForString + 1) != '\\')
                        {
                            iLastProcessedCharForString++;
                            pf = calcPrefixFunction(pf, fileTree.getNodeChar(firstSeqNodeId, iLastProcessedCharForString), sequence.tokens[iFirstNotMatchedToken], sequence.prefixFunctions[iFirstNotMatchedToken]);
                            if (!isAsterisk && !isDoubleAsterisk && iLastProcessedCharForString - iChar != pf)
                            {
                                isMatch = false;
                                break;
                            }
                            if (pf == (long long)(sequence.tokens[iFirstNotMatchedToken].Length()) &&
                                (iFirstNotMatchedToken < (long long)sequence.tokens.size() - 1 ||
                                 ((!isLast || iLastProcessedCharForString == fileTree.getNodeLength(firstSeqNodeId) - 1) &&
                                  (!hasNextInLinkedSequence || iLastProcessedCharForString == fileTree.getNodeLength(firstSeqNodeId) - 1 || fileTree.getNodeChar(firstSeqNodeId, iLastProcessedCharForString + 1) == '\\')
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
                        firstSeqNodeLastMatchedChar = fileTree.getNodeLength(firstSeqNodeId) - 1;
                    }
                    else
                        return false;
                }
                else
                {
                    firstSeqNodeLastMatchedChar = iChar;
                    if (isAsterisk)
                    {
                        firstSeqNodeLastMatchedChar = fileTree.getNodeLength(firstSeqNodeId) - 1;
                    }

                    return true;
                }
            }
        }
    }

    bool processLinkedSequence(LinkedSequence linkedSequence,
                               long long newNodeId, long long& newNodeLastMatchedChar, long long& firstNotMatchedLinkedSequence, long long& firstNotMatchedSequenceInLinkedSequence, long long& nodeIdOfFirstSequenceInLinkedSequence,
                               bool isDoubleAsterisk,
                               bool isLast,
                               bool shiftFirstSeq)
    {
        vector<FileTree::DelimeterFileNameNode*> processingNodes;
        long long iCurrentNode, currentNodeLastMatchedChar = newNodeLastMatchedChar;
        long long iFirstSeqNode = 0;
        if (nodeIdOfFirstSequenceInLinkedSequence == -1)
            nodeIdOfFirstSequenceInLinkedSequence = newNodeId;
        processingNodes = fileTree.getNodesInProcessing(newNodeId, nodeIdOfFirstSequenceInLinkedSequence);
        iCurrentNode = processingNodes.size() - 1;

        if (shiftFirstSeq)
        {
            iFirstSeqNode++;
        }

        while (firstNotMatchedSequenceInLinkedSequence != (long long)(linkedSequence.sequences.size()))
        {
            if (firstNotMatchedSequenceInLinkedSequence != 0)
                if (matchSeq(processingNodes[iCurrentNode]->nodeId,
                             currentNodeLastMatchedChar,
                             linkedSequence.sequences[firstNotMatchedSequenceInLinkedSequence],
                             linkedSequence.sequencesTypes[firstNotMatchedSequenceInLinkedSequence],
                             isLast && (long long)linkedSequence.sequences.size() - 1 == firstNotMatchedSequenceInLinkedSequence,
                             (long long)linkedSequence.sequences.size() > firstNotMatchedSequenceInLinkedSequence + 1))
                {
                    firstNotMatchedSequenceInLinkedSequence++;
                    if (currentNodeLastMatchedChar == fileTree.getNodeLength(processingNodes[iCurrentNode]->nodeId) - 1)
                    {
                        iCurrentNode++;
                        if (iCurrentNode == (long long)processingNodes.size())
                        {
                            break;
                        }
                        currentNodeLastMatchedChar = -1;
                    }
                }
                else
                {
                    if (isDoubleAsterisk)
                    {
                        shiftFirstSeq = true;
                        iFirstSeqNode++;
                        firstNotMatchedSequenceInLinkedSequence = 0;
                        if (iFirstSeqNode == (long long)processingNodes.size())
                        {
                            newNodeLastMatchedChar = fileTree.getNodeLength(processingNodes[iCurrentNode]->nodeId) - 1;
                            nodeIdOfFirstSequenceInLinkedSequence = -1;
                            return true;
                        }
                    }
                    else
                        return false;
                }
            else
            {
                long long firstSeqNodeLastMatchedChar;
                if (shiftFirstSeq)
                    firstSeqNodeLastMatchedChar = -1;
                else
                    firstSeqNodeLastMatchedChar = newNodeLastMatchedChar;
                bool skipped;
                if (matchFirstSeq(processingNodes, iFirstSeqNode, firstSeqNodeLastMatchedChar,
                                  linkedSequence.sequences[firstNotMatchedSequenceInLinkedSequence],
                                  linkedSequence.sequencesTypes[firstNotMatchedSequenceInLinkedSequence],
                                  isDoubleAsterisk,
                                  isLast && (long long)linkedSequence.sequences.size() - 1 == firstNotMatchedSequenceInLinkedSequence,
                                  (long long)(linkedSequence.sequences.size()) > firstNotMatchedSequenceInLinkedSequence + 1,
                                  skipped))
                {
                    if (skipped)
                    {
                        newNodeLastMatchedChar = fileTree.getNodeLength(processingNodes[iCurrentNode]->nodeId) - 1;
                        nodeIdOfFirstSequenceInLinkedSequence = -1;
                        return true;
                    }
                    currentNodeLastMatchedChar = firstSeqNodeLastMatchedChar;
                    iCurrentNode = iFirstSeqNode;
                    firstNotMatchedSequenceInLinkedSequence++;
                    if (currentNodeLastMatchedChar == fileTree.getNodeLength(processingNodes[iCurrentNode]->nodeId) - 1)
                    {
                        iCurrentNode++;
                        if (iCurrentNode == (long long)processingNodes.size())
                        {
                            break;
                        }
                        currentNodeLastMatchedChar = -1;
                    }
                }
                else
                {
                    return false;
                }
            }
        }

        newNodeLastMatchedChar = currentNodeLastMatchedChar;
        nodeIdOfFirstSequenceInLinkedSequence = processingNodes[iFirstSeqNode]->nodeId;
        if (firstNotMatchedSequenceInLinkedSequence == (long long)(linkedSequence.sequences.size()))
        {
            firstNotMatchedLinkedSequence++;
            firstNotMatchedSequenceInLinkedSequence = 0;
            if (firstNotMatchedLinkedSequence != (long long)(linkedSequences.size()))
                nodeIdOfFirstSequenceInLinkedSequence = -1;
        }
        return true;
    }

    MatchResult match(long long newNodeId)
    {
        long long firstNotMatchedLinkedSequence = 0;
        long long firstNotMatchedSequenceInLinkedSequence = 0;
        long long nodeIdOfFirstSequenceInLinkedSequence = -1;
        long long newNodeLastMatchedChar = -1;

        long long prevNodeId = fileTree.getPrevNodeId(newNodeId);

        bool shiftFirstSeq = false;

        if (prevNodeId != -1)
        {
            firstNotMatchedLinkedSequence = fileTree.getFirstNotMatchedLinkedSequence(prevNodeId);
            firstNotMatchedSequenceInLinkedSequence = fileTree.getFirstNotMatchedSequenceInLinkedSequence(prevNodeId);
            nodeIdOfFirstSequenceInLinkedSequence = fileTree.getNodeIdOfFirstSequenceInLinkedSequence(prevNodeId);

            if (firstNotMatchedLinkedSequence == (long long)(linkedSequences.size()))
            {
                if (linkedSequences.size() > 0)
                {
                    if (linkedSequencesTypes.back() == LinkedSequenceType::LinkedSequence)
                    {
                        shiftFirstSeq = true;
                        firstNotMatchedLinkedSequence--;
                        firstNotMatchedSequenceInLinkedSequence = 0;
                    }
                }
            }
        }

        if (isAppendSlash && !fileTree.isDir(newNodeId))
            return MatchResult::NoMatchAndFull;

        while (firstNotMatchedLinkedSequence < (long long)(linkedSequencesTypes.size()))
        {
            if (linkedSequencesTypes[firstNotMatchedLinkedSequence] == LinkedSequenceType::DoubleAsterisk)
            {
                firstNotMatchedLinkedSequence++;
                firstNotMatchedSequenceInLinkedSequence = 0;
                nodeIdOfFirstSequenceInLinkedSequence = -1;
            }
            else
            {
                bool isDoubleAsterisk = firstNotMatchedLinkedSequence >= 1;

                bool processResult = processLinkedSequence(linkedSequences[firstNotMatchedLinkedSequence],
                                      newNodeId, newNodeLastMatchedChar, firstNotMatchedLinkedSequence, firstNotMatchedSequenceInLinkedSequence, nodeIdOfFirstSequenceInLinkedSequence,
                                      isDoubleAsterisk,
                                      firstNotMatchedLinkedSequence == (long long)linkedSequences.size() - 1,
                                      shiftFirstSeq);
                if (!processResult)
                {
                    return MatchResult::NoMatchAndFull;
                }
                else if (newNodeLastMatchedChar == fileTree.getNodeLength(newNodeId) - 1 && (firstNotMatchedLinkedSequence != (long long)linkedSequences.size() - 1 || linkedSequencesTypes[firstNotMatchedLinkedSequence] != LinkedSequenceType::DoubleAsterisk))
                    break;
            }
        }

        fileTree.updateNode(newNodeId, firstNotMatchedLinkedSequence, firstNotMatchedSequenceInLinkedSequence, nodeIdOfFirstSequenceInLinkedSequence, newNodeLastMatchedChar);

        if (firstNotMatchedLinkedSequence == (long long)(linkedSequences.size()))
        {
            if (linkedSequencesTypes.size() >= 2 || (linkedSequencesTypes.size() == 1 && linkedSequencesTypes[0] == LinkedSequenceType::DoubleAsterisk))
                return MatchResult::MatchAndPartial;
            else
                return MatchResult::MatchAndFull;
        }
        else
        {
            if (newNodeLastMatchedChar == fileTree.getNodeLength(newNodeId) - 1)
                return MatchResult::NoMatchAndPartial;
            else
                return MatchResult::NoMatchAndFull;
        }
    }

public:
    virtual SearchExitCode search(wxString &sdToken, long long& version, double& time, wxThreadHelper* tHelper)
    {
        return SearchExitCode::Success;
    }
};

class BfsSearcher : public Searcher
{
private:
    SearchExitCode bfs(wxString currentDir)
    {
        fileTree = FileTree();
        queue<long long> allFilesIds;
        allFilesIds.push(-1);

        int depth = 0;
        long long currentDepthCount = 0;
        long long nextDepthCount = 0;
        PercentageCalculator percentageCalculator;

        while (!allFilesIds.empty())
        {
            if (testDestroy())
                return SearchExitCode::Delete;
            if (updateWorker())
                return SearchExitCode::Update;

            long long currentNodeId = allFilesIds.front();
            allFilesIds.pop();

            if (fileTree.isDir(currentNodeId))
            {
                if (fileTree.getNodeDepth(currentNodeId) != depth)
                {
                    if  (depth != 0 && percentageCalculator.addLayer(depth, currentDepthCount, nextDepthCount))
                        onPercentageChanged(percentageCalculator.getPercentage());
                    depth++;
                    currentDepthCount = nextDepthCount;
                    nextDepthCount = 0;
                }
            }

            MatchResult mResult;
            if (currentNodeId != -1)
                mResult = match(currentNodeId);
            else
                if (linkedSequences.size() == 0)
                    mResult = MatchResult::MatchAndFull;
                else
                    mResult = MatchResult::NoMatchAndPartial;

            if ((mResult == MatchResult::MatchAndFull || mResult == MatchResult::MatchAndPartial))
            {
                wregex re(L"[A-Za-z]:");
                wsmatch m;
                if (regex_match(currentDir.ToStdWstring(), m, re) && currentNodeId == -1)
                {
                    currentDir.Append("\\");
                    onSuccessMatch(currentDir, fileTree.isDir(currentNodeId));
                    currentDir.RemoveLast(1);
                }
                else
                {
                    if (!isAppendSlash)
                    {
                        wxString path = fileTree.getFullPath(currentNodeId);
                        currentDir.Append(path);
                        onSuccessMatch(currentDir, fileTree.isDir(currentNodeId));
                        currentDir.RemoveLast(path.Length());
                    }
                    else
                    {
                        wxString path = fileTree.getFullPath(currentNodeId);
                        path.Append("\\");
                        currentDir.Append(path);
                        onSuccessMatch(currentDir, fileTree.isDir(currentNodeId));
                        currentDir.RemoveLast(path.Length());
                    }
                }
            }
            if (fileTree.isDir(currentNodeId) && (mResult == MatchResult::MatchAndPartial || mResult == MatchResult::NoMatchAndPartial))
            {
                vector<Path> pathes;
                loadFileNamesInCurrentPath(currentDir + fileTree.getFullPath(currentNodeId), pathes);

                for (int i = 0; i < (long long)(pathes.size()); i++)
                {
                    if (pathes[i].isDir)
                        nextDepthCount++;
                    long long nodeId = fileTree.addNode(currentNodeId, pathes[i].fullPath, pathes[i].isDir);
                    allFilesIds.push(nodeId);
                }
            }
        }

        if (currentDepthCount != 0)
        {
            if  (depth != 0 && percentageCalculator.addLayer(depth, currentDepthCount, 0))
                onPercentageChanged(percentageCalculator.getPercentage());
            depth++;
            currentDepthCount = 0;
        }

        fileTree = FileTree();

        return SearchExitCode::Success;
    }

    bool aliasSearchPrepare(wxString sdToken, wxString& currentDir, wxString& preparedSdToken)
    {
        wxString dirsPath = exePath.BeforeLast('\\');
        dirsPath.Append("\\dirs.txt");
        RecordsDispatcher dirs(dirsPath.ToStdWstring());
        dirs.load_dirs();
        wstring dir;
        long long iFirstNotAliasChar = 0;
        while ((long long)sdToken.Length() > iFirstNotAliasChar &&
               sdToken.GetChar(iFirstNotAliasChar) != '*' &&
               sdToken.GetChar(iFirstNotAliasChar) != '\\' &&
               sdToken.GetChar(iFirstNotAliasChar) != '/')
                iFirstNotAliasChar++;
        bool isAlias = dirs.get_path_with_alias(sdToken.SubString(0, iFirstNotAliasChar - 1).ToStdWstring(), dir);
        dirs.save_dirs();
        if (isAlias)
        {
            if (dir.back() == L'\\')
                dir.pop_back();

            currentDir = dir;

            preparedSdToken = sdToken.SubString(iFirstNotAliasChar, sdToken.Length() - 1);

            wregex re2(L"([\\\\/]\\.\\.)*(([\\\\/]|(\\*\\*)).*)?");
            wregex re3(L"^[\\\\/]\\.\\.");
            wstring s = preparedSdToken.ToStdWstring();
            if (regex_match(s, re2))
            {
                int cnt = 0;
                wsmatch m;
                for (; regex_search(s, m, re3); s = m.suffix())
                {
                    cnt++;
                }
                wxFileName trimmedDir = wxFileName::DirName(currentDir);
                if ((long long)(trimmedDir.GetDirCount()) + 1 > cnt)
                {
                    while (cnt != 0)
                    {
                        cnt--;
                        trimmedDir.RemoveLastDir();
                    }
                    currentDir = trimmedDir.GetFullPath();
                    currentDir.RemoveLast();
                    preparedSdToken = s;

                    return true;
                } else
                {
                    return false;
                }
            }

            return true;
        }
        return false;
    }

    bool relativePathSearchPrepare(wxString sdToken, wxString& currentDir, wxString& preparedSdToken)
    {
        if (sdToken.Length() > 0 && (sdToken.GetChar(0) == '\\' || sdToken.GetChar(0) == '/'))
        {
            return false;
        }

        if (sdToken == ".")
        {
            sdToken = "";
        }
        if (sdToken.StartsWith("./") || sdToken.StartsWith(".\\"))
        {
            sdToken = sdToken.SubString(2, sdToken.Length() - 1);
        }

        int cnt = 0;
        while (sdToken.StartsWith("..\\") || sdToken.StartsWith("../"))
        {
            sdToken = sdToken.SubString(3, sdToken.Length());
            cnt++;
        }
        if (sdToken.StartsWith(".."))
        {
            if (sdToken == "..")
            {
                sdToken = "";
                cnt++;
            }
            else if (sdToken.StartsWith("..**"))
            {
                sdToken = sdToken.SubString(2, sdToken.Length());
                cnt++;
            } else
            {
                return false;
            }
        }
        wxFileName trimmedDir = wxFileName::DirName(wxFileName::GetCwd());
        if ((long long)(trimmedDir.GetDirCount()) + 1 > cnt)
        {
            while (cnt != 0)
            {
                cnt--;
                trimmedDir.RemoveLastDir();
            }
            currentDir = trimmedDir.GetFullPath();
            currentDir.RemoveLast();
        }
        else
            return false;

        if (!sdToken.StartsWith("**") && sdToken != "")
            sdToken = '/' + sdToken;
        preparedSdToken = sdToken;

        return true;
    }

    bool absolutePathSearchPrepare(wxString sdToken, wxString& currentDir, wxString& preparedSdToken)
    {
        wregex re(L"[A-Za-z]:[\\\\/]");
        wsmatch m;
        if (sdToken.Length() >= 3 && regex_match(sdToken.SubString(0, 2).ToStdWstring(), m, re))
        {
            currentDir = sdToken.SubString(0, 1);
            preparedSdToken = sdToken.SubString(2, sdToken.Length() - 1);
            return true;
        }
        return false;
    }

public:
    SearchExitCode search(wxString &sdToken, long long& version, double& time, wxThreadHelper* tHelper) override
    {
        initFields(tHelper, version, sdToken, time);
        wxString preparedSdToken;
        wxString currentDir;

        if (aliasSearchPrepare(sdToken, currentDir, preparedSdToken))
        {
            this->pType = PercentageType::Alias;
            onPercentageChanged(0);

            parseSdToken(preparedSdToken);

            SearchExitCode exitCode = bfs(currentDir);
            if (exitCode == SearchExitCode::Delete)
                return SearchExitCode::Delete;
            if (exitCode == SearchExitCode::Update)
            {
                cloneFields(version, sdToken, time);
                return SearchExitCode::Update;
            }
            onPercentageChanged(100);
        }

        if (relativePathSearchPrepare(sdToken, currentDir, preparedSdToken))
        {
            this->pType = PercentageType::Relative;
            onPercentageChanged(0);

            parseSdToken(preparedSdToken);

            SearchExitCode exitCode = bfs(currentDir);
            if (exitCode == SearchExitCode::Delete)
                return SearchExitCode::Delete;
            if (exitCode == SearchExitCode::Update)
            {
                cloneFields(version, sdToken, time);
                return SearchExitCode::Update;
            }
            onPercentageChanged(100);
        }

        if (absolutePathSearchPrepare(sdToken, currentDir, preparedSdToken))
        {
            this->pType = PercentageType::Absolute;
            onPercentageChanged(0);

            parseSdToken(preparedSdToken);

            SearchExitCode exitCode = bfs(currentDir);
            if (exitCode == SearchExitCode::Delete)
                return SearchExitCode::Delete;
            if (exitCode == SearchExitCode::Update)
            {
                cloneFields(version, sdToken, time);
                return SearchExitCode::Update;
            }
            onPercentageChanged(100);
        }

        return SearchExitCode::Success;
    }
};

#endif // SEARCH_H_INCLUDED
