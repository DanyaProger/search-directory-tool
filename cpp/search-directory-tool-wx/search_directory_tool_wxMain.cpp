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
const wxWindowID search_directory_tool_wxFrame::ID_PARENTICONBITMAP = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTPLACEHOLDER1 = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATICTEXTPATHESLABEL = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_TEXTCTRLPATHES = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_TIMER1 = wxNewId();
const wxWindowID search_directory_tool_wxFrame::ID_STATUSBAR1 = wxNewId();
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
    ParentIconBitmap = new wxStaticBitmap(this, ID_PARENTICONBITMAP, wxNullBitmap, wxDefaultPosition, wxSize(16,16), 0, _T("ID_PARENTICONBITMAP"));
    BoxSizer2->Add(ParentIconBitmap, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 2);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    StaticTextPlaceholder1 = new wxStaticText(this, ID_STATICTEXTPLACEHOLDER1, wxEmptyString, wxDefaultPosition, wxSize(-1,10), 0, _T("ID_STATICTEXTPLACEHOLDER1"));
    BoxSizer1->Add(StaticTextPlaceholder1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextPathesLabel = new wxStaticText(this, ID_STATICTEXTPATHESLABEL, _("Pathes:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXTPATHESLABEL"));
    wxFont StaticTextPathesLabelFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextPathesLabel->SetFont(StaticTextPathesLabelFont);
    BoxSizer3->Add(StaticTextPathesLabel, 0, wxALL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxEXPAND, 5);
    TextCtrlPathes = new wxTextCtrl(this, ID_TEXTCTRLPATHES, wxEmptyString, wxDefaultPosition, wxSize(-1,400), wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLPATHES"));
    wxFont TextCtrlPathesFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlPathes->SetFont(TextCtrlPathesFont);
    BoxSizer1->Add(TextCtrlPathes, 10, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(50, false);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, -1, -1 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    BoxSizer1->SetSizeHints(this);
    Center();

    Connect(ID_TEXTCTRLCOMMAND, wxEVT_COMMAND_TEXT_UPDATED, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnTextCtrlCommandText);
    Connect(ID_TIMER1, wxEVT_TIMER, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnTimer1Trigger);
    Connect(wxID_ANY, wxEVT_CLOSE_WINDOW, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnClose);
    Connect(wxEVT_KEY_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnKeyDown);
    Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&search_directory_tool_wxFrame::OnLeftDown);
    //*)

    SetTitle("search directory tool");
    SetIcon(wxICON(aaaa));

    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnCommandKeyDown), NULL, this);
    TextCtrlCommand->Connect(ID_TEXTCTRLCOMMAND, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnCommandLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_KEY_DOWN, wxKeyEventHandler (search_directory_tool_wxFrame::OnPathesKeyDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_DOWN, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftDown), NULL, this);
    TextCtrlPathes->Connect(ID_TEXTCTRLPATHES, wxEVT_LEFT_UP, wxMouseEventHandler (search_directory_tool_wxFrame::OnPathesLeftUp), NULL, this);

    pathesController = PathesController(TextCtrlPathes);

    bitmaps[TerminalChangerType::Bash] = wxBITMAP_PNG(bash);
    bitmaps[TerminalChangerType::Cmd] = wxBITMAP_PNG(cmd);
    bitmaps[TerminalChangerType::Explorer] = wxBITMAP_PNG(explorer);
    bitmaps[TerminalChangerType::Far] = wxBITMAP_PNG(far);
    bitmaps[TerminalChangerType::Powershell] = wxBITMAP_PNG(powershell);
    bitmaps[TerminalChangerType::TotalCommander] = wxBITMAP_PNG(totalcommander);
    bitmaps[TerminalChangerType::None] = wxBITMAP_PNG(none);

    winApiController.saveForegroundWindow();
    currentChangerType = TerminalChangerType::None;
    if (winApiController.checkForegroundWindow())
    {
        currentChangerType = winApiController.getParentProcessType();
        ParentIconBitmap->SetBitmap(wxBitmapBundle::FromBitmap(bitmaps[currentChangerType]));
    }

    changers[TerminalChangerType::Bash] = &bashChanger;
    changers[TerminalChangerType::Cmd] = &cmdChanger;
    changers[TerminalChangerType::Explorer] = &explorerChanger;
    changers[TerminalChangerType::Far] = &farChanger;
    changers[TerminalChangerType::Powershell] = &powershellChanger;
    changers[TerminalChangerType::TotalCommander] = &totalCommanderChanger;

    setPercentage(make_pair(PercentageType::Alias, -1));
    setPercentage(make_pair(PercentageType::Relative, -1));
    setPercentage(make_pair(PercentageType::Absolute, -1));

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
    PercentageType pType;
    SearchExitCode exitCode = SearchExitCode::Success;
    BfsSearcher bfsSearcher;
    Searcher* searcher = &bfsSearcher;

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

            wxThread::This()->Sleep(25);
        }
        if (GetThread()->TestDestroy())
            return nullptr;

        exitCode = searcher->search(sdToken, version, time, this);
        if (exitCode == SearchExitCode::Delete)
            break;
        if (exitCode == SearchExitCode::Update)
        {
            isUpdated = true;
            continue;
        }

        isUpdated = false;
    }

    return nullptr;
}

void search_directory_tool_wxFrame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void search_directory_tool_wxFrame::OnClose(wxCloseEvent& event)
{
    if (GetThread() &&
        GetThread()->IsRunning())
            GetThread()->Delete();
    Destroy();
}

wxString prepareDirFromPath(wxString path, bool isDir)
{
    wxString result;
    if (!isDir)
    {
        size_t pos = path.Last('\\');
        result = path.SubString(0, pos);
    } else
    {
        result = path;
        if (!path.EndsWith("\\"))
            result.Append('\\');
    }
    return result;
}

void search_directory_tool_wxFrame::OnKeyDown(wxKeyEvent& event)
{
    switch (event.GetKeyCode())
    {
    case WXK_UP:
        bool isReset;
        pathesController.selectPrevPath(isReset);
        if (isReset)
            TextCtrlCommand->SetFocus();
        break;
    case WXK_DOWN:
        pathesController.selectNextPath();
        break;
    case WXK_TAB:
        if (pathesController.getPathesCount() > 0 && pathesController.getSelectedPath() >= 0)
        {
            wxString path;
            bool isDir;
            pathesController.getPath(pathesController.getSelectedPath(), path, isDir);
            path = prepareDirFromPath(path, isDir);

            TextCtrlCommand->SetValue(path + "*");
            TextCtrlCommand->SetInsertionPoint(TextCtrlCommand->GetValue().Length() - 1);
            TextCtrlCommand->SetFocus();
        }
        break;
    case WXK_RETURN:
        if (pathesController.getPathesCount() > 0 &&
            pathesController.getSelectedPath() >= 0 &&
            currentChangerType != TerminalChangerType::None &&
            winApiController.checkForegroundWindow() &&
            winApiController.checkParentProcess())
        {
            wxString path;
            bool isDir;
            pathesController.getPath(pathesController.getSelectedPath(), path, isDir);
            path = prepareDirFromPath(path, isDir);

            Hide();
            winApiController.focusForegroundWindow();
            changers[currentChangerType]->change_directory(path.ToStdWstring());
            Close();
        }
        break;
    case WXK_BACK:
        pathesController.pathSelectReset();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_ESCAPE:
        pathesController.pathSelectReset();
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
        break;
    case WXK_DOWN:
        pathesController.selectNextPath();
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
    case WXK_TAB:
        if (!TextCtrlCommand->GetValue().EndsWith("**"))
        {
            TextCtrlCommand->AppendText("*");
        }
        if (TextCtrlCommand->GetValue().EndsWith("**"))
            TextCtrlCommand->SetInsertionPoint(TextCtrlCommand->GetValue().Length() - 2);
        else
            TextCtrlCommand->SetInsertionPoint(TextCtrlCommand->GetValue().Length() - 1);
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
        bool isReset;
        pathesController.selectPrevPath(isReset);
        if (isReset)
            TextCtrlCommand->SetFocus();
        break;
    case WXK_DOWN:
        pathesController.selectNextPath();
        break;
    case WXK_TAB:
        if (pathesController.getPathesCount() > 0 && pathesController.getSelectedPath() >= 0)
        {
            wxString path;
            bool isDir;
            pathesController.getPath(pathesController.getSelectedPath(), path, isDir);
            path = prepareDirFromPath(path, isDir);

            TextCtrlCommand->SetValue(path + "*");
            TextCtrlCommand->SetInsertionPoint(TextCtrlCommand->GetValue().Length() - 1);
            TextCtrlCommand->SetFocus();
        }
        break;
    case WXK_RETURN:
        if (pathesController.getPathesCount() > 0 &&
            pathesController.getSelectedPath() >= 0 &&
            currentChangerType != TerminalChangerType::None &&
            winApiController.checkForegroundWindow() &&
            winApiController.checkParentProcess())
        {
            wxString path;
            bool isDir;
            pathesController.getPath(pathesController.getSelectedPath(), path, isDir);
            path = prepareDirFromPath(path, isDir);

            Hide();
            winApiController.focusForegroundWindow();
            changers[currentChangerType]->change_directory(path.ToStdWstring());
            Close();
        }
        break;
    case WXK_BACK:
        pathesController.pathSelectReset();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_ESCAPE:
        pathesController.pathSelectReset();
        TextCtrlCommand->SetFocus();
        break;
    case WXK_DELETE:
        break;
    default:
        event.Skip();
        break;
    }
}

void search_directory_tool_wxFrame::selectPathWithMouse()
{
    pathesController.selectPathWithMouse();
}

void search_directory_tool_wxFrame::OnLeftDown(wxMouseEvent& event)
{
}

void search_directory_tool_wxFrame::OnCommandLeftDown(wxMouseEvent& event)
{
    pathesController.pathSelectReset();
    TextCtrlCommand->SetFocus();
    event.Skip();
}

void search_directory_tool_wxFrame::OnPathesLeftDown(wxMouseEvent& event)
{
    if (pathesController.getPathesCount() != 0)
        event.Skip();
}

void search_directory_tool_wxFrame::OnPathesLeftUp(wxMouseEvent& event)
{
    if (pathesController.getPathesCount() != 0)
    {
        event.Skip();
        CallAfter(search_directory_tool_wxFrame::selectPathWithMouse);
    }
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

        pathesController.clear();

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

    while (clock() - st < TIME_ON_OnTimer1Trigger && PathesExchange::popPath(path))
    {
        pathesController.appendPath(path.fullPath, path.isDir);
        if (pathesController.getPathesCount() == MAX_PATHES_COUNT)
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
        value = "partial";
     else
        value = to_string(percentage.second) + "%";
     switch (percentage.first)
     {
     case PercentageType::Alias:
         StatusBar1->SetStatusText("alias " + value, 0);
         aliasPercentage = percentage.second;
         break;
     case PercentageType::Relative:
         StatusBar1->SetStatusText("relative " + value, 1);
         relativePercentage = percentage.second;
         break;
     case PercentageType::Absolute:
         StatusBar1->SetStatusText("absolute " + value, 2);
         absolutePercentage = percentage.second;
         break;
     }
 }
