/***************************************************************
 * Name:      search_directory_tool_wxApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Danila Maiseyenkau ()
 * Created:   2025-10-13
 * Copyright: Danila Maiseyenkau ()
 * License:
 **************************************************************/

#include "search_directory_tool_wxApp.h"

//(*AppHeaders
#include "search_directory_tool_wxMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(search_directory_tool_wxApp);

bool search_directory_tool_wxApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
        search_directory_tool_wxFrame* Frame = new search_directory_tool_wxFrame(0);
        Frame->Show();
        SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
