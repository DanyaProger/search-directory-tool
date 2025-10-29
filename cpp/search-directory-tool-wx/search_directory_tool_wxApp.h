/***************************************************************
 * Name:      search_directory_tool_wxApp.h
 * Purpose:   Defines Application Class
 * Author:    Danila Maiseyenkau ()
 * Created:   2025-10-13
 * Copyright: Danila Maiseyenkau ()
 * License:
 **************************************************************/

#ifndef SEARCH_DIRECTORY_TOOL_WXAPP_H
#define SEARCH_DIRECTORY_TOOL_WXAPP_H

#include <wx/app.h>

class search_directory_tool_wxApp : public wxApp
{
    public:
        virtual bool OnInit();
};

DECLARE_APP(search_directory_tool_wxApp)

#endif // SEARCH_DIRECTORY_TOOL_WXAPP_H
