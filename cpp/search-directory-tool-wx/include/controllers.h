#ifndef CONTROLLERS_H_INCLUDED
#define CONTROLLERS_H_INCLUDED

#include <wx/string.h>
#include <wx/textctrl.h>

#include <vector>
#include <algorithm>

using namespace std;

class PathesController
{
private:
    wxTextCtrl* textCtrl;
    int selectedPath = -1;
    vector<long> rowStartPositions;
    vector<long> rowLengths;
    vector<wxString> pathes;
    vector<bool> isDirs;
    long length = 0;

    wxTextAttr defaultStyle;
    wxTextAttr fileStyle;
    wxTextAttr dirStyle;

    void positionToXY(long position, long&x, long& y)
    {
        vector<long>::iterator it = upper_bound(rowStartPositions.begin(), rowStartPositions.end(), position);
        it--;
        x = position - *it;
        y = it - rowStartPositions.begin();
    }

    void selectPath()
    {
        int startSel = 0, endSel = -1;
        startSel = rowStartPositions[selectedPath];
        endSel = startSel + rowLengths[selectedPath];

        textCtrl->SetSelection(startSel, endSel);
        textCtrl->SetFocus();
    }

public:
    PathesController() {}

    PathesController(wxTextCtrl* textCtrl)
    {
        this->textCtrl = textCtrl;
        rowStartPositions.push_back(0);
        rowLengths.push_back(0);

        defaultStyle = textCtrl->GetDefaultStyle();

        wxFont dirFont = textCtrl->GetFont();
        dirFont.SetUnderlined(true);
        dirStyle = defaultStyle;
        dirStyle.SetFont(dirFont);

        wxFont fileFont = textCtrl->GetFont();
        fileFont.SetStyle(wxFONTSTYLE_ITALIC);
        fileFont.SetUnderlined(true);
        fileStyle = defaultStyle;
        fileStyle.SetFont(fileFont);
    }

    void appendPath(wxString path, bool isDir)
    {
        if (!(rowLengths.size() == 1 && rowStartPositions.size() == 1 && rowStartPositions[0] == 0 && rowLengths[0] == 0))
        {
            textCtrl->AppendText("\n");
            length++;
        }
        if (!isDir)
        {
            size_t pos = path.Last('\\');
            textCtrl->AppendText(path.SubString(0, pos));
            textCtrl->SetDefaultStyle(fileStyle);
            textCtrl->AppendText(path.SubString(pos + 1, path.Length() - 1));
            textCtrl->SetDefaultStyle(defaultStyle);
        }
        else
        {
            size_t pos = path.Last('\\');
            if (pos == (long long)path.Length() - 1)
                pos = path.find_last_of('\\', pos - 1);
            textCtrl->AppendText(path.SubString(0, pos));
            textCtrl->SetDefaultStyle(dirStyle);
            textCtrl->AppendText(path.SubString(pos + 1, path.Length() - 1));
            textCtrl->SetDefaultStyle(defaultStyle);
        }

        if (!(rowLengths.size() == 1 && rowStartPositions.size() == 1 && rowStartPositions[0] == 0 && rowLengths[0] == 0))
        {
            rowStartPositions.push_back(length);
            rowLengths.push_back(path.size());
        } else
        {
            rowLengths.back() += path.size();
        }
        length += path.size();

        pathes.push_back(path);
        isDirs.push_back(isDir);
    }

    int getNumberOfLines()
    {
        return rowLengths.size();
    }

    int getSelectedPath()
    {
        return selectedPath;
    }

    int getPathesCount()
    {
        if (rowLengths.size() == 1 && rowStartPositions.size() == 1 && rowStartPositions[0] == 0 && rowLengths[0] == 0)
            return 0;
        else
            return rowLengths.size();
    }

    void getPath(int index, wxString& path, bool& isDir)
    {
        path = pathes[index];
        isDir = isDirs[index];
    }

    void pathSelectReset()
    {
        selectedPath = -1;
        textCtrl->SelectNone();
    }

    void selectNextPath()
    {
        if (selectedPath < getPathesCount() - 1)
            selectedPath++;
        if (getPathesCount() != 0)
            selectPath();
    }

    void selectPrevPath(bool& isReset)
    {
        isReset = false;
        if (selectedPath == -1)
            return;
        selectedPath--;
        if (selectedPath == -1)
        {
            pathSelectReset();
            isReset = true;
            return;
        }
        else
        {
            selectPath();
        }
    }

    void selectPathWithMouse()
    {
        if (getPathesCount() == 0)
            return;

        long x, y;
        positionToXY(textCtrl->GetInsertionPoint(), x, y);
        selectedPath = y;

        long int l, r;
        textCtrl->GetSelection(&l, &r);
        if (l == r)
        {
            if (getPathesCount() != 0)
                selectPath();
        }
    }

    void clear()
    {
        pathSelectReset();
        textCtrl->Clear();

        length = 0;

        rowStartPositions.clear();
        rowLengths.clear();
        rowStartPositions.push_back(0);
        rowLengths.push_back(0);

        pathes.clear();
        isDirs.clear();
    }
};

#endif // CONTROLLERS_H_INCLUDED
