#ifndef SEARCH_DIRECTORY_TOOL_WXHELP_H_INCLUDED
#define SEARCH_DIRECTORY_TOOL_WXHELP_H_INCLUDED

#include <wx/textctrl.h>
#include <wx/dialog.h>
#include <wx/sizer.h>
#include <wx/event.h>

class HelpDialog : public wxDialog
{
private:
    wxTextCtrl* TextCtrlText;
    bool closed = false;

    void OnClose(wxCloseEvent& event)
    {
        Close();
    }

public:
    HelpDialog(wxString title): wxDialog(NULL, -1, title, wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER, wxDialogNameStr)
    {
        wxBoxSizer* BoxSizer;
        BoxSizer = new wxBoxSizer(wxVERTICAL);

        TextCtrlText = new wxTextCtrl(this, 0, wxEmptyString, wxDefaultPosition, wxSize(700, 800), wxTE_PROCESS_ENTER|wxTE_MULTILINE|wxTE_READONLY|wxTE_RICH|wxTE_NOHIDESEL, wxDefaultValidator, _T("ID_TEXTCTRLTEXT"));
        wxFont TextCtrlTextFont(8,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_NORMAL,false,_T("Lucida Console"),wxFONTENCODING_DEFAULT);
        TextCtrlText->SetFont(TextCtrlTextFont);

        if (title.IsSameAs("sd help ru"))
            FillRussianHelp();
        else
            FillEnglishHelp();

        TextCtrlText->SetInsertionPoint(0);

        BoxSizer->Add(TextCtrlText, 1, wxEXPAND, 0);

        Bind(wxEVT_CLOSE_WINDOW, &HelpDialog::OnClose, this);

        SetSizerAndFit(BoxSizer);
    }

    void Close()
    {
        closed = true;
        if (IsModal())
            EndModal(wxOK);
        else
            Hide();
    }

    bool isClosed()
    {
        return closed;
    }

    void FillRussianHelp()
    {
        TextCtrlText->AppendText(
LR"(Программа sd - альтернативный способ поиска и открытия папок.

Использование: sd <куда переместиться>
               sd --alias <псевдоним для текущей папки>
               sd --alias <псевдоним> <куда переместиться>

<куда переместиться> может быть псевдонимом, относительным или абсолютным путём
    Примеры с псевдонимом:
        sd home            Переместиться в папку с псевдонимом home (псевдоним
                           должен быть заранее установлен опцией --alias или
                           --fill-dirs.txt).
    Примеры с относительным путём:
        sd Downloads       Переместиться в подпапку Downloads.
        sd ./Downloads     Переместиться в подпапку Downloads с явным указанием,
                           что это относительный путь. Это полезно в случаях,
                           когда относительный путь совпадает с псевдонимом.
        sd ..              Переместиться в родительский каталог.
    Примеры абсолютных путей:
        sd C:\Windows\System32

Опции:
    --alias <псевдоним>    Определить псевдоним для папки.
    --back                 Переместиться назад.
    --fill-dirs.txt        Создать стандартные псевдонимы. Создадутся следующие
                           псевдонимы: home, loads, doc, pic, music, videos, c, d,
                           e, f, pf, pf86, win.
    --help                 Показать это сообщение.
    --help-en              Show this message in English.
    --parent               Показать pid и имя родительского процесса
    --path                 добавить sd.exe в Path. Программа станет доступна из
                           любой папки.
    --remove-path          Убрать sd.exe из Path. Программа перестанет быть
                           доступной из любой папки.
    --time <число секунд>  Ограничение на время поиска. По умолчанию для
                           консольной версии - 3,
                           для GUI версии - inf(бесконечность).

    Принудительный выбор типа переключения (по умолчанию автоматически)
    -b, --bash             Использовать переключение для bash.
    -c, --cmd              Использовать переключение для cmd.
    -e, --explorer         Использовать переключение для Проводника.
    -f, --far              Использовать переключение для Far Manager.
    -p, --powershell       Использовать переключение для powershell.
    -t, --totalcmd         Использовать переключение для Total Commander.

Дополнильные сведения:
  - Программа переходит по первому найденному пути папки.
  - Псевдоним имеет приоритет над относительным путём.
  - Если выражение <куда переместиться> содержит пробел, то такое выражение
    нужно обернуть в кавычки. Это необязательно делать в GUI версии программы.
  - Можно искать файлы, тогда программа открывает папку, в которой находится
    файл.
  - В любых выражениях <куда переместиться> поддерживаются
    символы-разделители / и \, а также * и ** globbing.
    Пример:
        sd c:\win*/sys**powershell.exe
  - Программа ищет поиском в ширину.

Список поддерживаемых программ:
  - bash
  - cmd
  - Проводник (Windows 10, Windows 11)
  - Far Manager
  - powershell
  - Total Commander (новые версии)

Установка программы:
1) открыть папку с sd.exe
2) запустить "sd --path"
3) запустить "sd --fill-dirs.txt"

Удаление программы:
1) запустить "sd --remove-path"
2) удалить папку с sd.exe

Globbing в sd
Программа поддерживает * и ** в выражении <куда переместиться>. ** - это любая
последовательность символов, * - это любая последовательность символов кроме
разделителей папок. ** полезно использовать при поиске на большой глубине.
Примеры:
    c:\Program Files (x86)\**edge.exe
    c:\Program Files (x86)\*soft
    c:\Program Files (x86)\**
    c:\Program Files (x86)\*

У программы есть GUI версия, которая открывается, если запустить sd без агрументов.


Автор: Данила Моисеенков
github: https://github.com/DanyaProger/search-directory-tool
Дата: 05.03.2026)");
    }

    void FillEnglishHelp()
    {
        TextCtrlText->AppendText(LR"(Program sd - an alternative way to search and open folders.

Usage: sd <where to move>
       sd --alias <alias for current folder>
       sd --alias <alias> <where to move>

<where to move> can be alias, relative or absolute path
    Alias examples:
        sd home            Move to the folder with the alias home (alias
                           must be set in advance by the --alias or
                           --fill-dirs.txt options).
    Relative path examples:
        sd Downloads       Move to folder Downloads.
        sd ./Downloads     Move to folder Downloads with explicit indication,
                           that this is a relative path. This is useful in cases
                           when relative path matches the alias.
        sd ..              Move to parent folder.
    Absolute path examples:
        sd C:\Windows\System32

Options:
    --alias <alias>        Define alias for folder.
    --back                 Move back.
    --fill-dirs.txt        Create standard aliases. Following aliases will be
                           created: home, loads, doc, pic, music, videos, c, d,
                           e, f, pf, pf86, win.
    --help                 Показать это сообщение на русском.
    --help-en              Show this message.
    --parent               Show pid and name of parent process.
    --path                 Add sd.exe in Path. Program will be available from
                           any folder.
    --remove-path          Remove sd.exe from Path. The program will stop to be
                           available from any folder.
    --time <number of sec> Search time limit. By default for console version
                           is 3, and for GUI version is inf(infinity).

    Force switching type (automatic by default)
    -b, --bash             Use switching for bash.
    -c, --cmd              Use switching for cmd.
    -e, --explorer         Use switching for Explorer.
    -f, --far              Use switching for Far Manager.
    -p, --powershell       Use switching for powershell.
    -t, --totalcmd         Use switching for Total Commander.

Additional information:
  - Program moves to the first folder path found.
  - Alias takes precedence over the relative path.
  - If expression <where to move> contains a space, then this expression
    should be wrapped in quotation marks. It is not necessary to do this in the
    GUI version of the program.
  - You can search for file, then program opens folder where file is located.
  - In any expressions <where to move> folder separators / and \ are
    supported, * and ** globbing is also supported.
    Example:
        sd c:\win*/sys**powershell.exe
  - Program uses breadth-first search.

Supported programs list:
  - bash
  - cmd
  - Explorer (Windows 10, Windows 11)
  - Far Manager
  - powershell
  - Total Commander (new versions)

Program setup:
1) open folder with sd.exe
2) run "sd --path"
3) run "sd --fill-dirs.txt"

Program uninstall:
1) run "sd --remove-path"
2) delete folder with sd.exe

Sd globbing
Program supports * и ** in expressions <where to move>. ** - any sequence of
characters, * - any sequence of characters except folder separators. ** is
useful when search at great depth.
Examples:
    c:\Program Files (x86)\**edge.exe
    c:\Program Files (x86)\*soft
    c:\Program Files (x86)\**
    c:\Program Files (x86)\*

Program has a GUI version that opens if you run sd without arguments.


Author: Danila Maiseyenkau
github: https://github.com/DanyaProger/search-directory-tool
Дата: 05.03.2026)");
    }
};

#endif // SEARCH_DIRECTORY_TOOL_WXHELP_H_INCLUDED
