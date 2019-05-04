#include <wx/wxprec.h>
#include "BuildFrame.h"
#include "MyFrame.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
	virtual int OnExit() { return 0; }
};


wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame();
	frame->Show(true);
	return true;
}