#ifndef RECORDSDISPATCHER_H_INCLUDED
#define RECORDSDISPATCHER_H_INCLUDED

#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <algorithm>

using namespace std;

const wstring ALIAS_PLACEHOLDER = L"_no_alias_";

class DirectoryRecord
{
public:
    wstring full_path;
    int count;
    wstring alias;

    DirectoryRecord() {}

    DirectoryRecord(wstring full_path, wstring alias)
    {
        this->full_path = full_path;
        if (alias == L"")
        {
            alias = ALIAS_PLACEHOLDER;
        }
        this->alias = alias;
        this->count = 1;
    }
};

class RecordsDispatcher
{
private:
    wstring dirs_file_name;
    vector<DirectoryRecord> directories;

public:
    RecordsDispatcher(wstring dirs_file_name)
    {
        this->dirs_file_name = dirs_file_name;
    }

    void update_record_with_path_and_alias(wstring path, wstring alias = ALIAS_PLACEHOLDER)
    {
        filesystem::path updated_path(path);

        int index = -1;
        for (size_t i = 0; i < directories.size(); i++)
        {
            filesystem::path current_path(directories[i].full_path);
            if (filesystem::exists(updated_path) && filesystem::exists(current_path) && filesystem::equivalent(updated_path, current_path))
                index = i;
        }

        for (size_t i = 0; i < directories.size(); i++)
        {
            if (directories[i].alias != ALIAS_PLACEHOLDER && directories[i].alias == alias) {
                directories[i].alias = ALIAS_PLACEHOLDER;
            }
        }

        if (index != -1) {
            directories[index].count++;
            if (alias != ALIAS_PLACEHOLDER)
                directories[index].alias = alias;
        } else {
            directories.push_back(DirectoryRecord(path, alias));
        }
    }

    wstring get_most_suitable_path(wstring token)
    {
        int index = -1, max_count = 0;
        filesystem::path p(token);
        for (size_t i = 0; i < directories.size(); i++)
        {
            if (token == directories[i].alias)
            {
                index = i;
                break;
            }
            filesystem::path p1(directories[i].full_path);
            if (p.is_absolute() && filesystem::exists(p) && filesystem::exists(p1) && filesystem::equivalent(p, p1))
            {
                index = i;
                break;
            }

            wstring l_last_dir = (filesystem::path(directories[i].full_path)).filename().wstring();
            wstring l_token = token;
            transform(l_last_dir.begin(), l_last_dir.end(), l_last_dir.begin(), ::towlower);
            transform(l_token.begin(), l_token.end(), l_token.begin(), ::towlower);
            if (l_last_dir.find(l_token) != string::npos)
            {
                if (directories[i].count > max_count)
                {
                    index = i;
                    max_count = directories[i].count;
                }
            }
        }

        if (index != -1)
        {
            return directories[index].full_path;
        }
        return L"";
    }

    bool get_path_with_alias(wstring alias, wstring& path)
    {
        int pos = -1;
        for (size_t i = 0; i < directories.size(); i++)
            if (directories[i].alias == alias)
                pos = i;
        if (pos != -1)
        {
            path = directories[pos].full_path;
            return true;
        }
        else
        {
            path = L"";
            return false;
        }
    }

    void remove_record_with_alias(wstring alias)
    {
        int pos = -1;
        for (size_t i = 0; i < directories.size(); i++)
        {
            if (directories[i].alias == alias)
                pos = i;
        }
        if (pos != -1)
        {
            directories.erase(directories.begin() + pos);
        }
    }

    void load_dirs()
    {
        directories.clear();

        if (!filesystem::exists(dirs_file_name))
        {
            filesystem::path dirs_txt(dirs_file_name);
            ofstream writer(dirs_txt);
            writer.close();
        }

        wstring full_path, alias;
        int cnt;
        filesystem::path dirs_txt(dirs_file_name);
        wifstream reader(dirs_txt);
        reader.imbue(std::locale(reader.getloc(), new std::codecvt_utf8<wchar_t>));
        while (true)
        {
            getline(reader, full_path);
            if (full_path == L"" || reader.eof())
                break;
            wstring str;
            getline(reader, str);
            int pos = str.find(L" ");
            cnt = stoi(str.substr(0, pos));
            alias = str.substr(pos + 1);

            DirectoryRecord record;
            record.full_path = full_path;
            record.count = cnt;
            record.alias = alias;

            directories.push_back(record);
        }
        reader.close();
    }

    void save_dirs()
    {
        filesystem::path dirs_txt(dirs_file_name);
        wofstream writer(dirs_txt);
        writer.imbue(std::locale(writer.getloc(), new std::codecvt_utf8<wchar_t>));

        for (DirectoryRecord record : directories)
        {
            writer << record.full_path << "\n";
            writer << record.count << " " << record.alias << "\n";
        }

        writer.close();

        directories.clear();
    }
};

#endif // RECORDSDISPATCHER_H_INCLUDED
