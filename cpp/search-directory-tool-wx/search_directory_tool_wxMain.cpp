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
const wxWindowID search_directory_tool_wxFrame::ID_TEXTCTRLPATHES = wxNewId();
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

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextSd = new wxStaticText(this, ID_STATICTEXTSD, _(" sd "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxALIGN_CENTRE, _T("ID_STATICTEXTSD"));
    wxFont StaticTextSdFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextSd->SetFont(StaticTextSdFont);
    BoxSizer2->Add(StaticTextSd, 0, wxALIGN_CENTER_VERTICAL, 5);
    TextCtrlCommand = new wxTextCtrl(this, ID_TEXTCTRLCOMMAND, wxEmptyString, wxDefaultPosition, wxSize(400,-1), wxTE_RICH|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLCOMMAND"));
    wxFont TextCtrlCommandFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlCommand->SetFont(TextCtrlCommandFont);
    BoxSizer2->Add(TextCtrlCommand, 5, wxALIGN_LEFT, 5);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextPlaceholder1 = new wxStaticText(this, ID_STATICTEXTPLACEHOLDER1, wxEmptyString, wxDefaultPosition, wxSize(-1,10), 0, _T("ID_STATICTEXTPLACEHOLDER1"));
    BoxSizer1->Add(StaticTextPlaceholder1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    StaticTextPathesLabel = new wxStaticText(this, ID_STATICTEXTPATHESLABEL, _("Pathes:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXTPATHESLABEL"));
    wxFont StaticTextPathesLabelFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextPathesLabel->SetFont(StaticTextPathesLabelFont);
    BoxSizer1->Add(StaticTextPathesLabel, 0, wxALL|wxALIGN_LEFT, 5);
    TextCtrlPathes = new wxTextCtrl(this, ID_TEXTCTRLPATHES, wxEmptyString, wxDefaultPosition, wxSize(-1,400), wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLPATHES"));
    wxFont TextCtrlPathesFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlPathes->SetFont(TextCtrlPathesFont);
    BoxSizer1->Add(TextCtrlPathes, 10, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_TEXTCTRLCOMMAND, wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnTextCtrlCommandText);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnClose);
    Connect(wxEVT_KEY_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnKeyDown);
    Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnLeftDown);
    //*)

    Bind(wxEVT_THREAD, &search_directory_tool_wxFrame::OnThreadUpdate, this);
    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnCommandKeyDown), NULL, this);
    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnCommandLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnPathesKeyDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_UP, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftUp), NULL, this);

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
            tokens.push_back(sdToken.SubString(i, i));
            tokensTypes.push_back(SdTokenType::Asterisk);
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

void addSubDir(wxString& path, wxString& dir, int& sz)
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

void popSubDir(wxString& path, int& sz)
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
    addSubDir(currentPath, asterisk, sz);
    HANDLE h = FindFirstFileW(currentPath.c_str(), &ffd);
    popSubDir(currentPath, sz);

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
                        addSubDir(currentPath, fileNames[i], sz);
                        DfsMatchExitCode exitCode = dfsMatch(iToken, tokens, tokensTypes, currentPath, true, true, lastTime, version, sdToken, time);
                        popSubDir(currentPath, sz);
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
                    addSubDir(currentPath, fileNames[i], sz);
                    DfsMatchExitCode exitCode = dfsMatch(iToken + 1, tokens, tokensTypes, currentPath, false, isDirs[i], lastTime, version, sdToken, time);
                    popSubDir(currentPath, sz);
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
                    addSubDir(currentPath, fileNames[i], sz);
                    DfsMatchExitCode exitCode = dfsMatch(iTokenAfterMatch, tokens, tokensTypes, currentPath, isSearchAfterMatch, isDirs[i], lastTime, version, sdToken, time);
                    popSubDir(currentPath, sz);
                    if (exitCode == DfsMatchExitCode::Delete || exitCode == DfsMatchExitCode::Update)
                        return exitCode;
                }
            }
        }
    }

    return DfsMatchExitCode::Success;
}

wxThread::ExitCode search_directory_tool_wxFrame::Entry()
{
    long long version = SdTokenExchange::getVersion();
    wxString sdToken;
    double time;

    vector<wxString> tokens;
    vector<SdTokenType> tokensTypes;

    string pathes[] = {
            "c:\\Users\\danil",
            "C:\\Users\\danil\\Downloads",
            "C:\\Users\\danil\\source\\repos\\search-directory-tool",
            "C:\\Program Files",
            "C:\\Users\\danil\\Documents",
            "d:\\Soft\\totalcmd",
            "C:\\Windows\\System32"
    };

    while (true)
    {
        while (true)
        {
            if (GetThread()->TestDestroy())
            {
                return nullptr;
            }

            if (SdTokenExchange::updateWorker(version, sdToken, time))
                break;

            wxThread::This()->Sleep(100);
        }
        if (GetThread()->TestDestroy())
            return nullptr;

        splitOnTokens(sdToken, tokens, tokensTypes);

        wxString currentPath = "c:\\Users\\danil";

        clock_t lastTime = clock();

        dfsMatch(0, tokens, tokensTypes, currentPath, false, true, lastTime, version, sdToken, time);
    }

    return nullptr;
}

void search_directory_tool_wxFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void search_directory_tool_wxFrame::OnAbout(wxCommandEvent& event)
{
}

void search_directory_tool_wxFrame::OnThreadUpdate(wxThreadEvent& event)
{
    vector<PathesExchange::Path> pathes = PathesExchange::popPathes();
    for (PathesExchange::Path path : pathes)
    {
        if (TextCtrlPathes->GetValue().length() == 0)
            TextCtrlPathes->AppendText(path.fullPath);
        else
            TextCtrlPathes->AppendText("\n" + path.fullPath);
    }
}

void search_directory_tool_wxFrame::OnButton1Click(wxCommandEvent& event)
{
    wxTextAttr style = TextCtrlPathes->GetDefaultStyle();
    wxTextAttr newStyle = wxTextAttr(wxNullColour, wxColour(200, 255, 200));
    TextCtrlPathes->SetDefaultStyle(newStyle);
    TextCtrlPathes->AppendText(wxT("c:\\Users\\danil\\Downloads\n"));
    TextCtrlPathes->SetDefaultStyle(style);
    TextCtrlPathes->AppendText("c:\\Users\\danil\\Documents\n");
    TextCtrlPathes->AppendText("c:\\Users\\danil\\");
    wxFont font = TextCtrlPathes->GetFont();
    font.SetUnderlined(true);
    newStyle = wxTextAttr(wxNullColour, wxNullColour, font);
    TextCtrlPathes->SetDefaultStyle(newStyle);
    TextCtrlPathes->AppendText("Documents");
    TextCtrlPathes->SetDefaultStyle(style);
    TextCtrlPathes->AppendText("\n");
    selectRow();
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

void search_directory_tool_wxFrame::processCommand()
{

}

void search_directory_tool_wxFrame::OnTextCtrlCommandText(wxCommandEvent& event)
{
    {
        exchangeVersion += 1;
        PathesExchange::updateVersion(exchangeVersion);
        PathesExchange::clearPathes();
        TextCtrlPathes->Clear();

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
