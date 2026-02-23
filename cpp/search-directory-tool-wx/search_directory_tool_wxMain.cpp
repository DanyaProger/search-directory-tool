#include "search_directory_tool_wxMain.h"

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
    SetClientSize(wxSize(450,450));
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextSd = new wxStaticText(this, ID_STATICTEXTSD, _(" sd "), wxDefaultPosition, wxDefaultSize, wxALIGN_LEFT|wxALIGN_CENTRE, _T("ID_STATICTEXTSD"));
    wxFont StaticTextSdFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextSd->SetFont(StaticTextSdFont);
    BoxSizer2->Add(StaticTextSd, 0, wxTOP|wxALIGN_CENTER_VERTICAL, 1);
    TextCtrlCommand = new wxTextCtrl(this, ID_TEXTCTRLCOMMAND, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), wxTE_PROCESS_ENTER|wxTE_RICH2|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLCOMMAND"));
    TextCtrlCommand->SetMinSize(wxSize(-1,-1));
    wxFont TextCtrlCommandFont(9,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlCommand->SetFont(TextCtrlCommandFont);
    BoxSizer2->Add(TextCtrlCommand, 1, wxTOP|wxBOTTOM|wxEXPAND, 3);
    ParentIconBitmap = new wxStaticBitmap(this, ID_PARENTICONBITMAP, wxNullBitmap, wxDefaultPosition, wxSize(16,16), 0, _T("ID_PARENTICONBITMAP"));
    BoxSizer2->Add(ParentIconBitmap, 0, wxALL|wxEXPAND, 2);
    BoxSizer1->Add(BoxSizer2, 0, wxALL|wxEXPAND, 5);
    StaticTextPlaceholder1 = new wxStaticText(this, ID_STATICTEXTPLACEHOLDER1, wxEmptyString, wxDefaultPosition, wxSize(-1,10), 0, _T("ID_STATICTEXTPLACEHOLDER1"));
    BoxSizer1->Add(StaticTextPlaceholder1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    StaticTextPathesLabel = new wxStaticText(this, ID_STATICTEXTPATHESLABEL, _("Pathes:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXTPATHESLABEL"));
    wxFont StaticTextPathesLabelFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    StaticTextPathesLabel->SetFont(StaticTextPathesLabelFont);
    BoxSizer3->Add(StaticTextPathesLabel, 0, wxALL, 5);
    BoxSizer1->Add(BoxSizer3, 0, wxALIGN_LEFT, 5);
    TextCtrlPathes = new wxTextCtrl(this, ID_TEXTCTRLPATHES, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL|wxBORDER_NONE, wxDefaultValidator, _T("ID_TEXTCTRLPATHES"));
    wxFont TextCtrlPathesFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
    TextCtrlPathes->SetFont(TextCtrlPathesFont);
    BoxSizer1->Add(TextCtrlPathes, 1, wxBOTTOM|wxLEFT|wxRIGHT|wxEXPAND, 5);
    SetSizer(BoxSizer1);
    Timer1.SetOwner(this, ID_TIMER1);
    Timer1.Start(50, false);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[3] = { -1, -1, -1 };
    int __wxStatusBarStyles_1[3] = { wxSB_NORMAL, wxSB_NORMAL, wxSB_NORMAL };
    StatusBar1->SetFieldsCount(3,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(3,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    Layout();
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
    choosenBitmap = TerminalChangerType::None;
    ParentIconBitmap->SetBitmap(wxBitmapBundle::FromBitmap(bitmaps[choosenBitmap]));
    if (winApiController.checkForegroundWindow())
    {
        currentChangerType = winApiController.getParentProcessType();
        chooseBitmap(currentChangerType);
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
    if (helpDialogEn != NULL)
    {
        helpDialogEn->Close();
        helpDialogEn->Destroy();
        helpDialogEn = NULL;
    }
    if (helpDialogRu != NULL)
    {
        helpDialogRu->Close();
        helpDialogRu->Destroy();
        helpDialogRu = NULL;
    }
    if (parentDialog != NULL)
    {
        parentDialog->Close();
        parentDialog->Destroy();
        parentDialog = NULL;
    }
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

void search_directory_tool_wxFrame::tryComplete()
{
    if (pathesController.getPathesCount() > 0 && pathesController.getSelectedPath() >= 0)
    {
        PathesExchange::Path path = pathesController.getPath(pathesController.getSelectedPath());
        path.fullPath = prepareDirFromPath(path.fullPath, path.isDir);
        wxFileName dir = wxFileName::DirName(path.fullPath);
        switch (path.type)
        {
        case PercentageType::Alias:
                dir.MakeRelativeTo(path.basePath);
                path.fullPath = path.alias + "\\" + (dir.GetFullPath().IsSameAs(".") || dir.GetFullPath().IsSameAs(".\\") ? "" : dir.GetFullPath());
                break;
        case PercentageType::Relative:
                dir.MakeRelativeTo(path.basePath);
                path.fullPath = ".\\" + (dir.GetFullPath().IsSameAs(".") || dir.GetFullPath().IsSameAs(".\\") ? "" : dir.GetFullPath());
                break;
        case PercentageType::Absolute:
                break;
        }
        if (!path.fullPath.EndsWith("\\"))
            path.fullPath.Append("\\");
        path.fullPath.Append("*");

        if (parsed.argsSize() > 0)
            parsed.setArg(0, path.fullPath);
        else
            parsed.appendArg(path.fullPath);

        TextCtrlCommand->SetValue(parsed.toWxString());
        TextCtrlCommand->SetInsertionPoint(TextCtrlCommand->GetValue().Length() - 1);
        TextCtrlCommand->SetFocus();
    }
}

bool search_directory_tool_wxFrame::doOperations()
{
    if (parsed.isFlag("path"))
    {
        winApiController.addSdDirectoryToPath();
        Close();
        return true;
    }
    if (parsed.isFlag("remove-path"))
    {
        winApiController.removeSdDirectoryFromPath();
        Close();
        return true;
    }
    if (parsed.isFlag("fill-dirs.txt"))
    {
        winApiController.fillDirsTxt();
        Close();
        return true;
    }
    return false;
}

void search_directory_tool_wxFrame::tryChangeDirectory()
{
    if (pathesController.getPathesCount() > 0 &&
            (currentChangerType != TerminalChangerType::None || forceChangerType != TerminalChangerType::None) &&
            winApiController.checkForegroundWindow() &&
            winApiController.checkParentProcess())
    {
        PathesExchange::Path path("", false, false, PercentageType::Alias, "", "");
        int iPath = pathesController.getSelectedPath();
        if (iPath == -1)
            iPath = 0;
        path = pathesController.getPath(iPath);
        path.fullPath = prepareDirFromPath(path.fullPath, path.isDir);

        Hide();
        winApiController.focusForegroundWindow();

        wxString dirsPath = exePath.BeforeLast('\\');
        dirsPath.Append("\\dirs.txt");
        RecordsDispatcher dirs(dirsPath.ToStdWstring());
        dirs.load_dirs();
        if (parsed.isOption("alias"))
        {
            dirs.update_record_with_path_and_alias(path.fullPath.ToStdWstring(), parsed.getOption("alias").ToStdWstring());
        }
        dirs.set_variable(L"back", wxFileName::GetCwd().ToStdWstring());
        dirs.save_dirs();
        if (forceChangerType != TerminalChangerType::None)
            changers[forceChangerType]->change_directory(path.fullPath.ToStdWstring());
        else
            changers[currentChangerType]->change_directory(path.fullPath.ToStdWstring());

        Close();
    }
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
        tryComplete();
        break;
    case WXK_RETURN:
        if (!doOperations())
            tryChangeDirectory();
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
        tryComplete();
        break;
    case WXK_RETURN:
        if (!doOperations())
            tryChangeDirectory();
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
        if (!doOperations())
            tryChangeDirectory();
        break;
    case WXK_BACK:
        TextCtrlCommand->GetSelection(&from, &to);
        if (from != to || TextCtrlCommand->GetInsertionPoint() != 0)
            event.Skip();
        break;
    case WXK_DELETE:
        TextCtrlCommand->GetSelection(&from, &to);
        if (from != to || TextCtrlCommand->GetInsertionPoint() < (long long)(TextCtrlCommand->GetValue().Length()))
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

        double time = numeric_limits<double>::infinity();
        parsed = cmdLineParser.parseWithOneArg(TextCtrlCommand->GetValue());
        if (parsed.isFlag("help"))
        {
            if (helpDialogRu != NULL && helpDialogRu->isClosed())
            {
                helpDialogRu->Destroy();
                helpDialogRu = NULL;
            }
            if (helpDialogRu != NULL && !(helpDialogRu->isClosed()))
            {

            } else
            {
                helpDialogRu = new HelpDialog(L"sd help ru");
                helpDialogRu->Show();
            }
        }
        if (parsed.isFlag("help-en"))
        {
            if (helpDialogEn != NULL && helpDialogEn->isClosed())
            {
                helpDialogEn->Destroy();
                helpDialogEn = NULL;
            }
            if (helpDialogEn != NULL && !helpDialogEn->isClosed())
            {

            } else
            {
                helpDialogEn = new HelpDialog(L"sd help en");
                helpDialogEn->Show();
            }
        }
        if (parsed.isFlag("parent"))
        {
            if (parentDialog != NULL && parentDialog->isClosed())
            {
                parentDialog->Destroy();
                parentDialog = NULL;
            }
            if (parentDialog != NULL && !parentDialog->isClosed())
            {

            } else
            {
                DWORD pid = winApiController.getParentProcessId(GetCurrentProcessId());
                wxString fileName = winApiController.getProcessName(pid);
                parentDialog = new ParentDialog(pid, fileName);
                parentDialog->Show();
            }
        }
        if (parsed.isOption("time"))
        {
            wxString timeStr = parsed.getOption("time");
            wchar_t* e;
            time = wcstod(timeStr, &e);
            if (e - timeStr.c_str() != timeStr.length())
                time = numeric_limits<double>::infinity();
        }
        forceChangerType = TerminalChangerType::None;
        if (parsed.isFlag("bash"))
        {
            forceChangerType = TerminalChangerType::Bash;
        }
        if (parsed.isFlag("cmd"))
        {
            forceChangerType = TerminalChangerType::Cmd;
        }
        if (parsed.isFlag("explorer"))
        {
            forceChangerType = TerminalChangerType::Explorer;
        }
        if (parsed.isFlag("far"))
        {
            forceChangerType = TerminalChangerType::Far;
        }
        if (parsed.isFlag("powershell"))
        {
            forceChangerType = TerminalChangerType::Powershell;
        }
        if (parsed.isFlag("totalcmd"))
        {
            forceChangerType = TerminalChangerType::TotalCommander;
        }
        if (forceChangerType != TerminalChangerType::None)
        {
            chooseBitmap(forceChangerType);
        } else
        {
            chooseBitmap(currentChangerType);
        }
        if (parsed.isFlag("back"))
        {
            wxString dirsPath = exePath.BeforeLast('\\');
            dirsPath.Append("\\dirs.txt");
            RecordsDispatcher dirs(dirsPath.ToStdWstring());
            dirs.load_dirs();
            wstring prev_path;
            if (dirs.get_variable(L"back", prev_path))
            {
                pathesController.appendPath(PathesExchange::Path(prev_path, true, false, PercentageType::Absolute, "", ""));
            }
        }
        else
        {
            wxString sdToken;
            if (parsed.argsSize() == 1)
                sdToken = parsed.arg(0);
            else
                sdToken = "";
            SdTokenExchange::pushSdToken(exchangeVersion, sdToken, time);
        }
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
    PathesExchange::Path path("", false, false, PercentageType::Alias, "", "");

    while (clock() - st < TIME_ON_OnTimer1Trigger && PathesExchange::popPath(path))
    {
        pathesController.appendPath(path);
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

void search_directory_tool_wxFrame::chooseBitmap(TerminalChangerType changer)
{
    if (changer != choosenBitmap)
    {
        choosenBitmap = changer;
        ParentIconBitmap->SetBitmap(wxBitmapBundle::FromBitmap(bitmaps[choosenBitmap]));
    }
}
