/***************************************************************
 * Name:      search_directory_tool_wxMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Danila Maiseyenkau ()
 * Created:   2025-10-13
 * Copyright: Danila Maiseyenkau ()
 * License:
 **************************************************************/

#include "search_directory_tool_wxMain.h"
#include "search_directory_tool_wxApp.h"

//(*InternalHeaders(search_directory_tool_wxFrame)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//(*IdInit(search_directory_tool_wxFrame)
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTSD = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_TEXTCTRLCOMMAND = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTPLACEHOLDER1 = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTPATHESLABEL = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTALIAS = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTALIASPERCENTAGE = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTREL = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTRELPERCENTAGE = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTABS = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTABSPERCENTAGE = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_TEXTCTRLPATHES = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(search_directory_tool_wxFrame,wxFrame)
    //(*EventTable(search_directory_tool_wxFrame)
    //*)
END_EVENT_TABLE()

search_directory_tool_wxFrame::search_directory_tool_wxFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(search_directory_tool_wxFrame)
    wxBoxSizer* BoxSizer1;
    wxBoxSizer* BoxSizer2;
    wxBoxSizer* BoxSizer3;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextSd = new wxStaticText(this, ID_STATICTEXTSD, _(" sd "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxALIGN_CENTRE, _T("ID_STATICTEXTSD"));
    wxFont StaticTextSdFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextSd->SetFont(StaticTextSdFont);
    BoxSizer2->Add(StaticTextSd, 0, wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlCommand = new wxTextCtrl(this, ID_TEXTCTRLCOMMAND, wxEmptyString, wxDefaultPosition, wxSize(400,-1), wxTE_PROCESS_ENTER|wxTE_RICH2|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLCOMMAND"));
    wxFont TextCtrlCommandFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlCommand->SetFont(TextCtrlCommandFont);
    BoxSizer2->Add(TextCtrlCommand, 5, wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextPlaceholder1 = new wxStaticText(this, ID_STATICTEXTPLACEHOLDER1, wxEmptyString, wxDefaultPosition, wxSize(-1,10), 0, _T("ID_STATICTEXTPLACEHOLDER1"));
    BoxSizer1->Add(StaticTextPlaceholder1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextPathesLabel = new wxStaticText(this, ID_STATICTEXTPATHESLABEL, _("Pathes:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXTPATHESLABEL"));
    wxFont StaticTextPathesLabelFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextPathesLabel->SetFont(StaticTextPathesLabelFont);
    BoxSizer3->Add(StaticTextPathesLabel, 0, wxALL, 5);
    StaticTextAlias = new wxStaticText(this, ID_STATICTEXTALIAS, _("alias"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXTALIAS"));
    wxFont StaticTextAliasFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextAlias->SetFont(StaticTextAliasFont);
    BoxSizer3->Add(StaticTextAlias, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextAliasPercentage = new wxStaticText(this, ID_STATICTEXTALIASPERCENTAGE, _T("    "), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE|wxALIGN_RIGHT, _T("ID_STATICTEXTALIASPERCENTAGE"));
    wxFont StaticTextAliasPercentageFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextAliasPercentage->SetFont(StaticTextAliasPercentageFont);
    BoxSizer3->Add(StaticTextAliasPercentage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextRel = new wxStaticText(this, ID_STATICTEXTREL, _("rel"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXTREL"));
    wxFont StaticTextRelFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextRel->SetFont(StaticTextRelFont);
    BoxSizer3->Add(StaticTextRel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextRelPercentage = new wxStaticText(this, ID_STATICTEXTRELPERCENTAGE, _T("    "), wxDefaultPosition, wxDefaultSize, wxST_NO_AUTORESIZE|wxALIGN_RIGHT, _T("ID_STATICTEXTRELPERCENTAGE"));
    wxFont StaticTextRelPercentageFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextRelPercentage->SetFont(StaticTextRelPercentageFont);
    BoxSizer3->Add(StaticTextRelPercentage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextAbs = new wxStaticText(this, ID_STATICTEXTABS, _("abs"), wxDefaultPosition, wxDefaultSize, wxALIGN_RIGHT, _T("ID_STATICTEXTABS"));
    wxFont StaticTextAbsFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextAbs->SetFont(StaticTextAbsFont);
    BoxSizer3->Add(StaticTextAbs, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextAbsPercentage = new wxStaticText(this, ID_STATICTEXTABSPERCENTAGE, _T("    "), wxDefaultPosition, wxSize(-1,-1), wxST_NO_AUTORESIZE, _T("ID_STATICTEXTABSPERCENTAGE"));
    wxFont StaticTextAbsPercentageFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextAbsPercentage->SetFont(StaticTextAbsPercentageFont);
    BoxSizer3->Add(StaticTextAbsPercentage, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxEXPAND, 5);
    TextCtrlPathes = new wxTextCtrl(this, ID_TEXTCTRLPATHES, wxEmptyString, wxDefaultPosition, wxSize(-1,400), wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLPATHES"));
    wxFont TextCtrlPathesFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlPathes->SetFont(TextCtrlPathesFont);
    BoxSizer1->Add(TextCtrlPathes, 10, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(200, false);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_TEXTCTRLCOMMAND, wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnTextCtrlCommandText);
    Connect(ID_TIMER1, wxEVT_TIMER, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnTimer1Trigger);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnClose);
    Connect(wxEVT_KEY_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnKeyDown);
    Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnLeftDown);
    //*)

    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnCommandKeyDown), NULL, this);
    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnCommandLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnPathesKeyDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_UP, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftUp), NULL, this);

    exchangeVersion += 1;
    PathesExchange::updateVersion(exchangeVersion);
    PathesExchange::clearPathes();
    SdTokenExchange::pushSdToken(exchangeVersion, "", SdTokenExchange::DEFAULT_TIME);

    if (CreateThread() != wxTHREAD_NO_ERROR)
    {
        wxMessageBox(wxString("Cannot create worker thread"), wxString("Error"));
        Close();
    }
    if (GetThread()->Run() != wxTHREAD_NO_ERROR)
    {
        wxMessageBox(wxString("Cannot run worker thread"), wxString("Error"));
        Close();
    }
}

search_directory_tool_wxFrame::~search_directory_tool_wxFrame()
{
    //(*Destroy(search_directory_tool_wxFrame)
    //*)
}

void search_directory_tool_wxFrame::splitOnTokens(wxString sdToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes)
{
    tokens.clear();
    tokensTypes.clear();

    wxString token;
    for (size_t i = 0; i < sdToken.length(); i++)
    {
        if (sdToken.GetChar(i) == '/' || sdToken.GetChar(i) == '\\')
        {
            if (token.length() > 0)
            {
                tokens.push_back(token);
                tokensTypes.push_back(SdTokenType::SubString);
                token.clear();
            }
            tokens.push_back(sdToken.SubString(i, i));
            tokensTypes.push_back(SdTokenType::Slash);
        }
        else if (sdToken.GetChar(i) == '*')
        {
            if (token.length() > 0)
            {
                tokens.push_back(token);
                tokensTypes.push_back(SdTokenType::SubString);
                token.clear();
            }
            if (tokens.size() == 0 || tokensTypes[tokens.size() - 1] != SdTokenType::Asterisk)
            {
                tokens.push_back(sdToken.SubString(i, i));
                tokensTypes.push_back(SdTokenType::Asterisk);
            }
        }
        else
        {
            token.Append(sdToken.GetChar(i));
        }
    }
    if (token.length() > 0)
    {
        tokens.push_back(token);
        tokensTypes.push_back(SdTokenType::SubString);
        token.clear();
    }
}

void addSubPath(wxString& path, wxString dir, int& sz)
{
    if (!(path.EndsWith("\\") || path.EndsWith("/")))
    {
        sz = 1;
        path.Append("\\");
    } else
    {
        sz = 0;
    }
    path.Append(dir);
    sz += dir.length();
}

void popSubPath(wxString& path, int& sz)
{
    path.RemoveLast(sz);
}

void loadFileNamesInCurrentPath(wxString& currentPath, vector<wxString>& fileNames, vector<bool>& isDirs)
{
    fileNames.clear();
    isDirs.clear();

    WIN32_FIND_DATAW ffd;

    int sz;
    wxString asterisk = "*";
    addSubPath(currentPath, asterisk, sz);
    HANDLE h = FindFirstFileW(currentPath.c_str(), &ffd);
    popSubPath(currentPath, sz);

    if (h == INVALID_HANDLE_VALUE)
        return;
    do {
        wxString fileName(ffd.cFileName);
        if (fileName == "." || fileName == "..")
            continue;
        fileNames.push_back(fileName);
        if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            isDirs.push_back(true);
        } else
        {
            isDirs.push_back(false);
        }
    } while (FindNextFileW(h, &ffd) != 0);
    FindClose(h);
    return;
}

bool fileNameMatch(wxString& fileName, int iToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes, bool isSearch, bool& isSearchAfterMatch, int& iTokenAfterMatch)
{
    wxString lowerFileName = fileName.Lower();
    size_t pos = 0;
    while (iToken < (int)tokens.size() && !(tokensTypes[iToken] == SdTokenType::Slash))
    {
        if (tokensTypes[iToken] == SdTokenType::Asterisk)
        {
            if (iToken == (int)tokens.size() - 1)
            {
                iTokenAfterMatch = iToken + 1;
                isSearchAfterMatch = false;
                return true;
            }
            else
            {
                isSearch = true;
            }
        }
        else
        {
            wxString lowerToken = tokens[iToken].Lower();
            if (!isSearch)
            {
                if (pos + lowerToken.length() <= lowerFileName.length() && lowerFileName.SubString(pos, pos + lowerToken.length() - 1) == lowerToken)
                {
                    isSearch = false;
                    pos += lowerToken.length();
                }
                else
                {
                    return false;
                }
            }
            else
            {
                pos = lowerFileName.find(lowerToken, pos);
                if (pos != wxString::npos)
                {
                    isSearch = false;
                    pos += lowerToken.length();
                }
                else
                {
                    iTokenAfterMatch = iToken;
                    isSearchAfterMatch = true;
                    return true;
                }
            }
        }
        iToken++;
    }

    if (!isSearch && pos != lowerFileName.length())
        return false;
    else
    {
        iTokenAfterMatch = iToken;
        isSearchAfterMatch = isSearch;
        return true;
    }
}

DfsMatchExitCode search_directory_tool_wxFrame::dfsMatch(int iToken, vector<wxString>& tokens, vector<SdTokenType>& tokensTypes, wxString& currentPath, bool isSearch, bool isDir, clock_t& lastTime, long long &version, wxString& sdToken, double& time)
{
    if (iToken == (int)tokens.size())
    {
        PathesExchange::pushPath(version, PathesExchange::Path(currentPath, isDir, false));
        messagesCount++;
        wxQueueEvent(GetEventHandler(), new wxThreadEvent());
        return DfsMatchExitCode::Success;
    } else if (!isDir && iToken < (int)tokens.size())
    {
        return DfsMatchExitCode::Success;
    }
    else
    {
        vector<wxString> fileNames;
        vector<bool> isDirs;
        int sz;
        int iTokenAfterMatch;
        bool isSearchAfterMatch;


        if (tokensTypes[iToken] == SdTokenType::Slash)
        {
            if (!(currentPath.EndsWith("\\") || currentPath.EndsWith("/")))
            {
                currentPath.Append("\\");
                DfsMatchExitCode exitCode = dfsMatch(iToken + 1, tokens, tokensTypes, currentPath, false, true, lastTime, version, sdToken, time);
                currentPath.RemoveLast(1);
                if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                    return exitCode;
            }
            if (isSearch)
            {
                // ищем по всем подкаталогам
                loadFileNamesInCurrentPath(currentPath, fileNames, isDirs);
                for (size_t i = 0; i < fileNames.size(); i++)
                {
                    if (isDirs[i])
                    {
                        addSubPath(currentPath, fileNames[i], sz);
                        DfsMatchExitCode exitCode = dfsMatch(iToken, tokens, tokensTypes, currentPath, true, true, lastTime, version, sdToken, time);
                        popSubPath(currentPath, sz);
                        if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                            return exitCode;
                    }
                }
            }
        }
        else if (tokensTypes[iToken] == SdTokenType::Asterisk)
        {
            if (iToken == (int)tokens.size() - 1)
            {
                // выводим текущую директорию и все подкаталоги
                DfsMatchExitCode exitCode = dfsMatch(iToken + 1, tokens, tokensTypes, currentPath, false, true, lastTime, version, sdToken, time);
                if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                    return exitCode;

                loadFileNamesInCurrentPath(currentPath, fileNames, isDirs);
                for (size_t i = 0; i < fileNames.size(); i++)
                {
                    addSubPath(currentPath, fileNames[i], sz);
                    DfsMatchExitCode exitCode = dfsMatch(iToken + 1, tokens, tokensTypes, currentPath, false, isDirs[i], lastTime, version, sdToken, time);
                    popSubPath(currentPath, sz);
                    if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                        return exitCode;
                }
            }
            else
            {
                DfsMatchExitCode exitCode = dfsMatch(iToken + 1, tokens, tokensTypes, currentPath, true, true, lastTime, version, sdToken, time);
                if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                    return exitCode;
            }
        }
        else
        {
            // проверяем файлы по началу имён
            loadFileNamesInCurrentPath(currentPath, fileNames, isDirs);
            for (size_t i = 0; i < fileNames.size(); i++)
            {
                if (fileNameMatch(fileNames[i], iToken, tokens, tokensTypes, isSearch, isSearchAfterMatch, iTokenAfterMatch))
                {
                    addSubPath(currentPath, fileNames[i], sz);
                    DfsMatchExitCode exitCode = dfsMatch(iTokenAfterMatch, tokens, tokensTypes, currentPath, isSearchAfterMatch, isDirs[i], lastTime, version, sdToken, time);
                    popSubPath(currentPath, sz);
                    if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                        return exitCode;
                }
            }
        }
    }

    return DfsMatchExitCode::Success;
}

bool shiftMatch(wxString& currentPathLower, long iLastProcessedCurrentPathChar,
                vector<wxString>& tokens, vector<SdTokenType>& tokensTypes,
                int iFirstTokenOfSlashOrSubstringSuffix, int iFirstNotMatchedToken, int& iFirstToken,
                bool isSearch,
                long& newILastProcessedCurrentPathChar,
                int& newIFirstTokenOfSlashOrSubstringSuffix, int& newIFirstNotMatchedToken,
                bool& newIsSearch)
{
    while (iFirstNotMatchedToken != tokens.size())
    {
        if (tokensTypes[iFirstNotMatchedToken] == SdTokenType::Asterisk)
        {
            if (iFirstNotMatchedToken == iFirstToken && iLastProcessedCurrentPathChar < currentPathLower.Length() - 1 && currentPathLower.GetChar(iLastProcessedCurrentPathChar + 1) == '\\')
                iLastProcessedCurrentPathChar += 1;
            isSearch = true;
            iFirstTokenOfSlashOrSubstringSuffix = -1;
            iFirstNotMatchedToken += 1;
            continue;
        }

        if (tokensTypes[iFirstNotMatchedToken] == SdTokenType::SubString || tokensTypes[iFirstNotMatchedToken] == SdTokenType::Slash)
        {
            if (iFirstNotMatchedToken == tokens.size() - 1 && tokensTypes[iFirstNotMatchedToken] == SdTokenType::Slash)
            {
                break;
            }
            wxString token = tokens[iFirstNotMatchedToken].Lower();
            if (tokensTypes[iFirstNotMatchedToken] == SdTokenType::Slash)
                token = "\\";
            if (iFirstTokenOfSlashOrSubstringSuffix == -1)
            {
                if (isSearch)
                {
                    size_t pos = currentPathLower.find(token, iLastProcessedCurrentPathChar + 1);
                    if (pos != wxString::npos)
                    {
                        iLastProcessedCurrentPathChar = pos + token.size() - 1;
                        iFirstTokenOfSlashOrSubstringSuffix = iFirstNotMatchedToken;
                        iFirstNotMatchedToken++;
                    }
                    else
                    {
                        iLastProcessedCurrentPathChar = currentPathLower.Length() - 1;
                        break;
                    }
                }
                else
                {
                    if (currentPathLower.Length() - 1 >= iLastProcessedCurrentPathChar + 1 + token.Length() - 1 &&
                        currentPathLower.SubString(iLastProcessedCurrentPathChar + 1, iLastProcessedCurrentPathChar + 1 + token.Length() - 1).IsSameAs(token))
                    {
                        iLastProcessedCurrentPathChar += 1 + token.length() - 1;
                        iFirstTokenOfSlashOrSubstringSuffix = iFirstNotMatchedToken;
                        iFirstNotMatchedToken++;
                    }
                    else if (iFirstNotMatchedToken == iFirstToken &&
                         tokensTypes[iFirstNotMatchedToken] == SdTokenType::SubString &&
                         iLastProcessedCurrentPathChar + 1 < currentPathLower.size() &&
                         currentPathLower.GetChar(iLastProcessedCurrentPathChar + 1) == '\\' &&
                         currentPathLower.Length() - 1 >= iLastProcessedCurrentPathChar + 2 + token.Length() - 1 &&
                         currentPathLower.SubString(iLastProcessedCurrentPathChar + 2, iLastProcessedCurrentPathChar + 2 + token.Length() - 1).IsSameAs(token))
                    {
                        iLastProcessedCurrentPathChar += 2 + token.length() - 1;
                        iFirstTokenOfSlashOrSubstringSuffix = iFirstNotMatchedToken;
                        iFirstNotMatchedToken++;
                    }
                    else
                    {
                        if (iLastProcessedCurrentPathChar == currentPathLower.Length() - 1)
                            break;
                        else
                            return false;
                    }
                }
            }
            else
            {
                if (currentPathLower.Length() - 1 >= iLastProcessedCurrentPathChar + 1 + token.Length() - 1 &&
                        currentPathLower.SubString(iLastProcessedCurrentPathChar + 1, iLastProcessedCurrentPathChar + 1 + token.Length() - 1).IsSameAs(token))
                {
                    iLastProcessedCurrentPathChar += 1 + token.length() - 1;
                    iFirstNotMatchedToken++;
                }
                else if (iLastProcessedCurrentPathChar == currentPathLower.Length() - 1)
                    break;
                else
                {
                    if (isSearch)
                    {
                        size_t suffixLength = 0;
                        for (int i = iFirstTokenOfSlashOrSubstringSuffix; i < iFirstNotMatchedToken; i++)
                            suffixLength += tokens[i].Length();
                        iLastProcessedCurrentPathChar = iLastProcessedCurrentPathChar - suffixLength + 1;
                        iFirstNotMatchedToken = iFirstTokenOfSlashOrSubstringSuffix;
                        iFirstTokenOfSlashOrSubstringSuffix = -1;
                    }
                    else
                    {
                        return false;
                    }
                }
            }
        }
    }

    if (!isSearch && iLastProcessedCurrentPathChar != currentPathLower.Length() - 1)
        return false;
    newIsSearch = isSearch;
    newIFirstTokenOfSlashOrSubstringSuffix = iFirstTokenOfSlashOrSubstringSuffix;
    newIFirstNotMatchedToken = iFirstNotMatchedToken;
    if (tokensTypes[iFirstNotMatchedToken - 1] == SdTokenType::Asterisk)
        newILastProcessedCurrentPathChar = currentPathLower.Length() - 1;
    else
        newILastProcessedCurrentPathChar = iLastProcessedCurrentPathChar;
    return true;
}

DfsMatchExitCode search_directory_tool_wxFrame::dfsMatch2(wxString& currentPath, wxString& currentPathLower, long iLastProcessedCurrentPathChar,
                                                          vector<wxString>&tokens, vector<SdTokenType>& tokensTypes,
                                                          int iFirstTokenOfSlashOrSubstringSuffix, int iFirstNotMatchedToken, int& iFirstToken,
                                                          bool isSearch, bool isDir,
                                                          clock_t lastTime, double percentageStart, double percentageEnd, PercentageType& pType,
                                                          long long& version, wxString& sdToken, double& time)
{
    if (GetThread()->TestDestroy())
        return DfsMatchExitCode::Delete;
    if (SdTokenExchange::updateWorker(version, sdToken, time))
        return DfsMatchExitCode::Update;

    long newILastProcessedCurrentPathChar = iLastProcessedCurrentPathChar;
    int newIFirstTokenOfSlashOrSubstringSuffix = iFirstTokenOfSlashOrSubstringSuffix;
    int newIFirstNotMatchedToken = iFirstNotMatchedToken;
    bool newIsSearch = isSearch;
    bool match = true;
    bool isRoot = currentPath.Length() - 1 == iLastProcessedCurrentPathChar;
    if (!isRoot)
        match = shiftMatch(currentPathLower, iLastProcessedCurrentPathChar, tokens, tokensTypes, iFirstTokenOfSlashOrSubstringSuffix, iFirstNotMatchedToken, iFirstToken, isSearch,
               newILastProcessedCurrentPathChar, newIFirstTokenOfSlashOrSubstringSuffix, newIFirstNotMatchedToken, newIsSearch);
    if (match)
    {
        if (newILastProcessedCurrentPathChar == currentPath.Length() - 1 && newIFirstNotMatchedToken == tokens.size() ||
            (isRoot && ((tokens.size() == iFirstNotMatchedToken + 1 && tokensTypes[iFirstNotMatchedToken] == SdTokenType::Asterisk) ||
                        (tokens.size() == iFirstNotMatchedToken + 2 && tokensTypes[iFirstNotMatchedToken] == SdTokenType::Slash && tokensTypes[iFirstNotMatchedToken + 1] == SdTokenType::Asterisk))))
        {
            wregex re(L"[A-Za-z]:");
            wsmatch m;
            if (regex_match(currentPath.ToStdWstring(), m, re))
            {
                currentPath.Append('\\');
                PathesExchange::pushPath(version, PathesExchange::Path(currentPath, isDir, false));
                currentPath.RemoveLast(1);
            } else
            {
                PathesExchange::pushPath(version, PathesExchange::Path(currentPath, isDir, false));
            }
        }
        if (isDir &&
            newILastProcessedCurrentPathChar == currentPath.Length() - 1 &&
            (newIFirstNotMatchedToken == tokens.size() - 1 && tokensTypes[tokens.size() - 1] == SdTokenType::Slash))
        {
            currentPath.Append('\\');

            PathesExchange::pushPath(version, PathesExchange::Path(currentPath, isDir, false));

            currentPath.RemoveLast(1);
        }
        if (isDir &&
            (newIFirstNotMatchedToken < tokens.size() - 1 || (newIFirstNotMatchedToken == tokens.size() - 1 && tokensTypes[tokens.size() - 1] != SdTokenType::Slash)))
        {
            vector<wxString> fileNames;
            vector<bool> isDirs;
            int sz1;
            int sz2;

            loadFileNamesInCurrentPath(currentPath, fileNames, isDirs);
            double percentage = 0, percentageNext;
            if (percentageStart == -1 || percentageEnd - percentageStart < 1e-4)
                percentage = -1;
            for (int i = 0; i < fileNames.size(); i++)
            {
                if (percentage != -1)
                {
                    percentage = percentageStart + (percentageEnd - percentageStart) / isDirs.size() * i;
                    percentageNext = percentageStart + (percentageEnd - percentageStart) / isDirs.size() * (i + 1);
                }
                addSubPath(currentPath, fileNames[i], sz1);
                addSubPath(currentPathLower, fileNames[i].Lower(), sz2);
                DfsMatchExitCode exitCode = dfsMatch2(currentPath, currentPathLower, newILastProcessedCurrentPathChar,
                                                      tokens, tokensTypes,
                                                      newIFirstTokenOfSlashOrSubstringSuffix, newIFirstNotMatchedToken, iFirstToken,
                                                      newIsSearch, isDirs[i],
                                                      lastTime, percentage, percentageNext, pType,
                                                      version, sdToken, time);
                popSubPath(currentPath, sz1);
                popSubPath(currentPathLower, sz2);
                if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                            return exitCode;
            }
        }
    }

    if (percentageStart != -1 && int(percentageStart) != int(percentageEnd))
    {
        PathesExchange::pushPercentage(version, make_pair(pType, int(percentageEnd)));
    }

    return DfsMatchExitCode::Success;
}

wxThread::ExitCode search_directory_tool_wxFrame::Entry()
{
    long long version = -1;
    wxString sdToken;
    double time;

    vector<wxString> tokens;
    vector<SdTokenType> tokensTypes;
    clock_t lastTime;
    wxString currentPath;
    wxString currentPathLower;
    int iFirstToken;
    PercentageType pType;
    DfsMatchExitCode exitCode;

    bool isUpdated = false;

    while (true)
    {
        while (!isUpdated)
        {
            if (GetThread()->TestDestroy())
            {
                return nullptr;
            }

            if (SdTokenExchange::updateWorker(version, sdToken, time))
            {
                isUpdated = true;
                break;
            }

            wxThread::This()->Sleep(100);
        }
        if (GetThread()->TestDestroy())
            return nullptr;

        splitOnTokens(sdToken, tokens, tokensTypes);

        if (tokens.size() > 0 && tokensTypes[0] == SdTokenType::SubString)
        {
            wxString dirsPath = exePath.BeforeLast('\\');
            dirsPath.Append("\\dirs.txt");
            RecordsDispatcher dirs(dirsPath.ToStdWstring());
            dirs.load_dirs();
            wstring dir;
            bool isAlias = dirs.get_path_with_alias(tokens[0].ToStdWstring(), dir);
            dirs.save_dirs();
            if (isAlias)
            {
                wregex re1(L"[A-Za-z]:\\\\");
                wsmatch m1;
                if (regex_match(dir, m1, re1))
                {
                    dir.pop_back();
                }
                currentPath = dir;
                currentPathLower = currentPath.Lower();
                lastTime = clock();
                iFirstToken = 1;
                PathesExchange::pushPercentage(version, make_pair(PercentageType::Alias, 0));
                pType = PercentageType::Alias;
                exitCode = dfsMatch2(currentPath, currentPathLower, currentPath.Length() - 1, tokens, tokensTypes, -1, iFirstToken, iFirstToken, false, true, lastTime, 0, 100, pType, version, sdToken, time);
                if (exitCode == DfsMatchExitCode::Delete)
                    break;
                if (exitCode == DfsMatchExitCode::Update)
                {
                    isUpdated = true;
                    continue;
                }
            }
        }

        currentPath = wxFileName::GetCwd();
        currentPathLower = currentPath.Lower();

        lastTime = clock();
        iFirstToken = 0;

        //dfsMatch(0, tokens, tokensTypes, currentPath, false, true, lastTime, version, sdToken, time);
        PathesExchange::pushPercentage(version, make_pair(PercentageType::Relative, 0));
        pType = PercentageType::Relative;
        exitCode = dfsMatch2(currentPath, currentPathLower, currentPath.Length() - 1, tokens, tokensTypes, -1, iFirstToken, iFirstToken, false, true, lastTime, 0, 100, pType, version, sdToken, time);
        if (exitCode == DfsMatchExitCode::Delete)
            break;
        if (exitCode == DfsMatchExitCode::Update)
        {
            isUpdated = true;
            continue;
        }

        wregex re2(L"[A-Za-z]:");
        wsmatch m2;
        if (tokens.size() >= 2 && regex_match(tokens[0].ToStdWstring(), m2, re2) && tokensTypes[1] == SdTokenType::Slash)
        {
            currentPath = tokens[0];
            currentPathLower = currentPath.Lower();

            lastTime = clock();
            iFirstToken = 1;

            PathesExchange::pushPercentage(version, make_pair(PercentageType::Absolute, 0));
            pType = PercentageType::Absolute;
            exitCode = dfsMatch2(currentPath, currentPathLower, currentPath.Length() - 1, tokens, tokensTypes, -1, iFirstToken, iFirstToken, false, true, lastTime, 0, 100, pType, version, sdToken, time);
            if (exitCode == DfsMatchExitCode::Delete)
                break;
            if (exitCode == DfsMatchExitCode::Update)
            {
                isUpdated = true;
                continue;
            }
        }

        isUpdated = false;
    }

    return nullptr;
}

void search_directory_tool_wxFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

long getNumberLines(wxTextCtrl* textCtrl)
{
    wxString text = textCtrl->GetValue();
    long cnt = 0;
    for (size_t i = 0; i < text.length(); i++)
        if (text.GetChar(i) == '\n')
            cnt++;
    return cnt + 1;
}

long getRowStartPosition(wxTextCtrl* textCtrl, long row)
{
    wxString text = textCtrl->GetValue();
    if (row == 0)
        return 0;
    long iRow = 0;
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text.GetChar(i) == '\n')
        {
            iRow += 1;
            if (iRow == row)
                return i + 1;
        }
    }
    return text.length();
}

long getRowLength(wxTextCtrl* textCtrl, long row)
{
    wxString text = textCtrl->GetValue();
    long iRow = 0, rowStart = 0;
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text.GetChar(i) == '\n')
        {
            if (iRow == row)
                return i - rowStart;
            iRow++;
            rowStart = i + 1;
        }
    }
    if (iRow == row)
    {
        return text.length() - rowStart;
    } else
    {
        return 0;
    }
}

void positionToXY(wxTextCtrl* textCtrl, long position, long&x, long& y)
{
    wxString text = textCtrl->GetValue();
    long iRow = 0, rowStart = 0;
    for (size_t i = 0; i < text.length(); i++)
    {
        if (text.GetChar(i) == '\n')
        {
            if (rowStart <= position && position <= (long)i)
            {
                x = i - rowStart;
                y = iRow;
                return;
            }
            iRow++;
            rowStart = i + 1;
        }
    }
    if (rowStart <= position && position <= (long)text.length())
    {
        x = position - rowStart;
        y = iRow;
    } else
    {
        x = text.length() - rowStart;
        y = iRow;
    }
}

void search_directory_tool_wxFrame::selectRow()
{
    if (selectedRow < -1 || selectedRow >= getNumberLines(TextCtrlPathes))
        return;
    if (selectedRow == -1)
    {
        TextCtrlPathes->SelectNone();
        TextCtrlCommand->SetFocus();
        return;
    }

    {
        int startSel = 0, endSel = -1;
        startSel = getRowStartPosition(TextCtrlPathes, selectedRow);
        endSel = startSel + getRowLength(TextCtrlPathes, selectedRow);

        TextCtrlPathes->SetSelection(startSel, endSel);
        TextCtrlPathes->SetFocus();
    }
}

void search_directory_tool_wxFrame::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_UP:
        if (selectedRow >= 0)
            selectedRow--;
        selectRow();
        break;
    case WXK_DOWN:
        if (selectedRow < TextCtrlPathes->GetNumberOfLines() - 1)
            selectedRow += 1;
        selectRow();
        break;
    case WXK_BACK:
        selectedRow = -1;
        TextCtrlPathes->SelectNone();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_ESCAPE:
        selectedRow = -1;
        TextCtrlPathes->SelectNone();
        TextCtrlCommand->SetFocus();
        break;
    default:
        event.Skip();
        break;
    }
}

void search_directory_tool_wxFrame::OnCommandKeyDown(wxKeyEvent& event)
{
    long from, to;

    switch (event.GetKeyCode())
    {
    case WXK_UP:
        if (selectedRow >= 0)
            selectedRow--;
        selectRow();
        break;
    case WXK_DOWN:
        if (selectedRow < getNumberLines(TextCtrlPathes) - 1)
            selectedRow += 1;
        selectRow();
        break;
    case WXK_RETURN:
        break;
    case WXK_BACK:
        TextCtrlCommand->GetSelection(&from, &to);
        if (from != to || TextCtrlCommand->GetInsertionPoint() != 0)
            event.Skip();
        break;
    case WXK_DELETE:
        TextCtrlCommand->GetSelection(&from, &to);
        if (from != to || TextCtrlCommand->GetInsertionPoint() < TextCtrlCommand->GetValue().Length())
            event.Skip();
        break;
    default:
        event.Skip();
        break;
    }
}

void search_directory_tool_wxFrame::OnPathesKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_UP:
        if (selectedRow >= 0)
            selectedRow--;
        selectRow();
        break;
    case WXK_DOWN:
        if (selectedRow < TextCtrlPathes->GetNumberOfLines() - 1)
            selectedRow += 1;
        selectRow();
        break;
    case WXK_BACK:
        selectedRow = -1;
        TextCtrlPathes->SelectNone();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_ESCAPE:
        selectedRow = -1;
        TextCtrlPathes->SelectNone();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_DELETE:
        break;
    case WXK_RETURN:
        break;
    default:
        event.Skip();
        break;
    }
}

void search_directory_tool_wxFrame::selectRowWithMouse()
{
    long x, y;
    positionToXY(TextCtrlPathes, TextCtrlPathes->GetInsertionPoint(), x, y);
    selectedRow = y;

    if (selectedRow < 0 || selectedRow >= TextCtrlPathes->GetNumberOfLines())
        return;

    long int l, r;
    TextCtrlPathes->GetSelection(&l, &r);
    if (l == r)
    {
        int startSel = 0, endSel = -1;
        startSel = getRowStartPosition(TextCtrlPathes, selectedRow);
        endSel = startSel + getRowLength(TextCtrlPathes, selectedRow);
        TextCtrlPathes->SetSelection(startSel, endSel);
        TextCtrlPathes->SetFocus();
    }
}

void search_directory_tool_wxFrame::OnLeftDown(wxMouseEvent& event)
{
}

void search_directory_tool_wxFrame::OnCommandLeftDown(wxMouseEvent& event)
{
    selectedRow = -1;
    TextCtrlPathes->SelectNone();
    TextCtrlCommand->SetFocus();
    event.Skip();
}

void search_directory_tool_wxFrame::OnPathesLeftDown(wxMouseEvent& event)
{
    event.Skip();
}

void search_directory_tool_wxFrame::OnPathesLeftUp(wxMouseEvent& event)
{
    event.Skip();
    CallAfter(search_directory_tool_wxFrame::selectRowWithMouse);
}

void search_directory_tool_wxFrame::OnTextCtrlCommandText(wxCommandEvent& event)
{
    {
        exchangeVersion += 1;
        PathesExchange::updateVersion(exchangeVersion);
        PathesExchange::clearPathes();

        PathesExchange::clearPercentages();
        setPercentage(make_pair(PercentageType::Alias, -1));
        setPercentage(make_pair(PercentageType::Relative, -1));
        setPercentage(make_pair(PercentageType::Absolute, -1));

        TextCtrlPathes->Clear();
        isFirstInPathes = true;
        pathesCount = 0;

        double time = SdTokenExchange::DEFAULT_TIME;
        wxString sdToken;
        CmdLineArgs parsed = cmdLineParser.parseWithOneArg(TextCtrlCommand->GetValue());
        if (parsed.isOption("time"))
        {
            wxString timeStr = parsed.getOption("time");
            wchar_t* e;
            time = wcstod(timeStr, &e);
            if (e - timeStr.c_str() != timeStr.length())
                time = SdTokenExchange::DEFAULT_TIME;
        }
        if (parsed.argsSize() == 1)
            sdToken = parsed.arg(0);
        SdTokenExchange::pushSdToken(exchangeVersion, sdToken, time);
    }
}

void search_directory_tool_wxFrame::OnClose(wxCloseEvent& event)
{
    if (GetThread() &&
        GetThread()->IsRunning())
            GetThread()->Delete();
    Destroy();
}

void search_directory_tool_wxFrame::OnTimer1Trigger(wxTimerEvent& event)
{
    pair<PercentageType, int> percentage;
    while (PathesExchange::popPercentage(percentage))
    {
        setPercentage(percentage);
    }

    int TIME_ON_OnTimer1Trigger = Timer1.GetInterval() / 2;
    clock_t st = clock();
    PathesExchange::Path path("", false, false);

    wxFont underlinedFont = TextCtrlPathes->GetFont();
    underlinedFont.SetUnderlined(true);
    wxTextAttr defaultStyle = TextCtrlPathes->GetDefaultStyle();
    wxTextAttr underlinedStyle = defaultStyle;
    underlinedStyle.SetFont(underlinedFont);

    while (clock() - st < TIME_ON_OnTimer1Trigger && PathesExchange::popPath(path))
    {
        if (isFirstInPathes)
        {
            isFirstInPathes = false;
        }
        else
            TextCtrlPathes->AppendText("\n");
        if (!path.isDir)
        {
            size_t pos = path.fullPath.Last('\\');
            TextCtrlPathes->AppendText(path.fullPath.SubString(0, pos));
            TextCtrlPathes->SetDefaultStyle(underlinedStyle);
            TextCtrlPathes->AppendText(path.fullPath.SubString(pos + 1, path.fullPath.Length() - 1));
            TextCtrlPathes->SetDefaultStyle(defaultStyle);
        }
        else
        {
            TextCtrlPathes->AppendText(path.fullPath);
        }
        pathesCount += 1;
        if (pathesCount == MAX_PATHES_COUNT)
        {
            exchangeVersion += 1;
            PathesExchange::updateVersion(exchangeVersion);
            PathesExchange::clearPathes();
            if (aliasPercentage >= 0)
                setPercentage(make_pair(PercentageType::Alias, -2));
            if (relativePercentage >= 0)
                setPercentage(make_pair(PercentageType::Relative, -2));
            if (absolutePercentage >= 0)
                setPercentage(make_pair(PercentageType::Absolute, -2));
            break;
        }
    }
}

 void search_directory_tool_wxFrame::setPercentage(pair<PercentageType, int> percentage)
 {
     wxString value;
     if (percentage.second == -1)
        value = "-%";
     else if (percentage.second == -2)
        value = "part";
     else
        value = to_string(percentage.second) + "%";
     switch (percentage.first)
     {
     case PercentageType::Alias:
         StaticTextAliasPercentage->SetLabel(value);
         aliasPercentage = percentage.second;
         break;
     case PercentageType::Relative:
         StaticTextRelPercentage->SetLabel(value);
         relativePercentage = percentage.second;
         break;
     case PercentageType::Absolute:
         StaticTextAbsPercentage->SetLabel(value);
         absolutePercentage = percentage.second;
         break;
     }
 }
