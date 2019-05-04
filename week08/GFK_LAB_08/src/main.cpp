#include <wx/wx.h>
#include "GUIMyFrame.h"

class MyApp : public wxApp {

public:

 virtual bool OnInit();
 virtual int OnExit() { return 0; }

};

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit() 
{
 GUIMyFrame *mainFrame = new GUIMyFrame(NULL);
 mainFrame->SetTitle(wxString("GFK LAB 08 - Tomasz Rajchel"));
 mainFrame->Show(true);
 SetTopWindow(mainFrame);

 return true;
}