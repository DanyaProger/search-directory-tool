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
    Timer1.Start(200, false);
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

            wxThread::This()->Sleep(100);
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
        if (selectedRow < getNumberLines(TextCtrlPathes) - 1)
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
        if (selectedRow >= 0)
            selectedRow--;
        selectRow();
        break;
    case WXK_DOWN:
        if (selectedRow < getNumberLines(TextCtrlPathes) - 1)
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

    wxFont dirFont = TextCtrlPathes->GetFont();
    dirFont.SetStyle(wxFONTSTYLE_ITALIC);
    dirFont.SetUnderlined(true);
    wxTextAttr dirStyle = defaultStyle;
    dirStyle.SetFont(dirFont);

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
            TextCtrlPathes->SetDefaultStyle(dirStyle);
            TextCtrlPathes->AppendText(path.fullPath.SubString(pos + 1, path.fullPath.Length() - 1));
            TextCtrlPathes->SetDefaultStyle(defaultStyle);
        }
        else
        {
            size_t pos = path.fullPath.Last('\\');
            TextCtrlPathes->AppendText(path.fullPath.SubString(0, pos));
            TextCtrlPathes->SetDefaultStyle(underlinedStyle);
            TextCtrlPathes->AppendText(path.fullPath.SubString(pos + 1, path.fullPath.Length() - 1));
            TextCtrlPathes->SetDefaultStyle(defaultStyle);
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
