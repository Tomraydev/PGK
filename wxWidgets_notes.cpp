// ******** wxWidgets - notes ********
#include <wx/wxprec.h> // Includes appropriate precompiled headers

// Main class representing the application itself, includes application-wide settings for GUI-only apps
class MyApp : public wxApp
{
public:
	virtual bool OnInit(); // usually creates the app's main windows
};

// window whose size and position can be changed by the user
class MyFrame : public wxFrame
{
public:
	MyFrame();
private:
	//EVENT HANDLING
	void OnExit(wxCloseEvent & e); //event handling
	void Form_Resize(wxSizeEvent & e); //event handling
	void Mouse_Move(wxMouseEvent & e); //event handling

	//CONTROLS
	wxButton *WxButton1;
	wxTextCtrl *WxEdit1;
	wxCheckBox *WxCheckBox1;
	wxStaticText *WxStaticText1;
	wxScrollBar *WxScrollBar1;

	void WxButton1_Click(wxCommandEvent &e);
	void WxEdit1_Updated(wxCommandEvent &e);
	void WxCheckBox1_Click(wxCommandEvent &e);
	void WxScrollBar1_Scroll(wxScrollEvent &e);

	enum
	{
		ID_WXBUTTON1 = 1001,
		ID_WXEDIT1 = 1002,
		ID_WXCHECKBOX1 = 1003,
		ID_WXSCROLLBAR1 = 1004
	};

	//MENU, RESOURCES, TIMER
	wxMenuBar *WxMenuBar1;
	wxTimer *WxTimer1;
	wxCheckBox *WxCheckBox1;
	wxStaticText *WxStaticText1;
	wxCursor MyCursor;

	void Timer1_Timer(wxTimerEvent &e);
	void CheckBox1_Click(wxCommandEvent &e);

	enum
	{
		ID_MENU_PLIK_1004 = 1004,
		ID_MENU_NOWY_1007 = 1007,
		ID_MENU_ZAKONCZ_1009 = 1009,
		ID_MENU_OPCJA_1_1010 = 1010,
		ID_MENU_OPCJA_2_1011 = 1011,
		ID_MENU_WYBOR_A_1013 = 1013,
		ID_MENU_WYBOR_B_1014 = 1014,

		ID_WXTIMER1 = 1002,
		ID_WXCHECKBOX1 = 1003
	};

	// DRAWING FUNCTIONS
	void Mouse_Move(wxMouseEvent &e);
	void Form_Paint(wxPaintEvent &e);
	bool DrawFlag;
};

wxIMPLEMENT_APP(MyApp); //Macro - works like the "main" function

// ******** DEFINITIONS ********
bool MyApp::OnInit()
{
	MyFrame *frame = new MyFrame(); //create a new frame object
	frame->Show(true);
	return true;
}

MyFrame::MyFrame() : wxFrame(NULL, wxID_ANY, "Demo 01")
{
	SetTitle(_("Demo 01 - Okno i zdarzenia"));
	SetIcon(wxNullIcon);
	SetSize(8, 8, 570, 360);
	Center();

	//EVENT HANDLING
	Bind(wxEVT_CLOSE_WINDOW, &MyFrame::OnExit, this); //event handling
	Bind(wxEVT_SIZE, &MyFrame::Form_Resize, this); //event handling
	Bind(wxEVT_MOTION, &MyFrame::Mouse_Move, this); //event handling

	//CONTROLS
	WxButton1 = new wxButton(this, ID_WXBUTTON1, _("Jakiœ przycisk"), wxPoint(19, 15), wxSize(113, 27), 0, wxDefaultValidator, _("WxButton1")); //similar for others
	Bind(wxEVT_BUTTON, &MyFrame::WxButton1_Click, this, ID_WXBUTTON1);

	//MENU, RESOURCES, TIMER
	WxMenuBar1 = new wxMenuBar();
	wxMenu *Menu_Plik = new wxMenu();
	WxMenuBar1->Append(Menu_Plik, _("&Plik"));
	Menu_Plik->Append(ID_MENU_NOWY_1007, _("&Nowy"), _(""), wxITEM_NORMAL);
	Menu_Plik->AppendSeparator();
	Menu_Plik->Append(ID_MENU_ZAKONCZ_1009, _("&Zakoñcz"), _(""), wxITEM_NORMAL);

	wxMenu *Menu_About = new wxMenu();
	WxMenuBar1->Append(Menu_About, _("&About"));
	Menu_About->Append(ID_MENU_OPCJA_1_1010, _("Opcja &1"), _(""), wxITEM_CHECK);
	Menu_About->Check(ID_MENU_OPCJA_1_1010, true);
	Menu_About->Append(ID_MENU_OPCJA_2_1011, _("Opcja &2"), _(""), wxITEM_CHECK);
	Menu_About->Check(ID_MENU_OPCJA_2_1011, false);
	Menu_About->AppendSeparator();
	Menu_About->Append(ID_MENU_WYBOR_A_1013, _("Wybór A"), _(""), wxITEM_RADIO);
	Menu_About->Check(ID_MENU_WYBOR_A_1013, true);
	Menu_About->Append(ID_MENU_WYBOR_B_1014, _("Wybór B"), _(""), wxITEM_RADIO);
	Menu_About->Check(ID_MENU_WYBOR_B_1014, false);

	SetMenuBar(WxMenuBar1); //Tells the frame to show the given menu bar.

	WxTimer1 = new wxTimer();
	WxTimer1->SetOwner(this, ID_WXTIMER1);

	WxCheckBox1 = new wxCheckBox(this, ID_WXCHECKBOX1, _("W³¹cz &zegarek"), wxPoint(70, 273), wxSize(112, 20), 0, wxDefaultValidator, _("WxCheckBox1"));

	WxStaticText1 = new wxStaticText(this, wxID_ANY, _("WxStaticText1"), wxPoint(125, 152), wxDefaultSize, 0, _("WxStaticText1"));
	WxStaticText1->SetFont(wxFont(25, wxSWISS, wxNORMAL, wxBOLD, false, _("Tahoma")));

	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent &) { WxStaticText1->SetLabel("Wybrano: NOWY"); }, ID_MENU_NOWY_1007);
	this->Bind(wxEVT_MENU, [&, this](wxCommandEvent &) { Close(); }, ID_MENU_ZAKONCZ_1009);
	Bind(wxEVT_TIMER, &MyFrame::Timer1_Timer, this, ID_WXTIMER1);
	Bind(wxEVT_CHECKBOX, &MyFrame::CheckBox1_Click, this, ID_WXCHECKBOX1);

	// DRAWING FUNCTIONS
	Bind(wxEVT_MOTION, &MyFrame::Mouse_Move, this);
	Bind(wxEVT_PAINT, &MyFrame::Form_Paint, this);
	this->Bind(wxEVT_LEFT_DOWN, [&, this](wxMouseEvent &e) { DrawFlag = true; });
	this->Bind(wxEVT_LEFT_UP, [&, this](wxMouseEvent &e) { DrawFlag = false; });
	DrawFlag = false;
}
}

// EVENT HANDLING - definition examples
void MyFrame::OnExit(wxCloseEvent & e)
{
	if (wxMessageDialog(NULL, "Czy na pewno chcesz zamkn¹æ?", "Pytanie", wxOK | wxCANCEL).ShowModal() == wxID_OK) Destroy();
}

void MyFrame::Form_Resize(wxSizeEvent & e)
{
	this->SetTitle("Zmieniono rozmiar okna: X=" + wxString::Format("%d", e.GetSize().GetWidth()) + "   Y=" + wxString::Format("%d", e.GetSize().GetHeight()));
}

void MyFrame::Mouse_Move(wxMouseEvent & e)
{
	this->SetTitle("Przesuniêto myszkê: X=" + wxString::Format("%d", e.m_x) + "   Y=" + wxString::Format("%d", e.m_y));
}
// CONTROLS - definition examples
void MyFrame::WxButton1_Click(wxCommandEvent &e)
{
	wxMessageDialog(NULL, "Wciœniêto przycisk", "Uwaga", wxOK).ShowModal();
}

void MyFrame::WxEdit1_Updated(wxCommandEvent &e)
{
	if (WxEdit1) WxStaticText1->SetLabel("Wpisano: " + WxEdit1->GetValue());
}

// MENU, RESOURCES, TIMER - definition examples
void MyFrame::Timer1_Timer(wxTimerEvent &e)
{
	wxDateTime now = wxDateTime::Now();
	WxStaticText1->SetLabel(wxString::Format("%d", now.GetHour()) + ":" + wxString::Format("%02d", now.GetMinute()) + ":" + wxString::Format("%02d", now.GetSecond()));
}

// DRWAING FUNCTINOS - definition examples
void MyFrame::Mouse_Move(wxMouseEvent & e)
{
	int x, y;
	if (DrawFlag)
	{
		wxClientDC MyDC(this);
		x = e.GetX();
		y = e.GetY();
		MyDC.SetPen(wxPen(*wxBLACK, 1));
		MyDC.DrawPoint(x, y);
	}
}