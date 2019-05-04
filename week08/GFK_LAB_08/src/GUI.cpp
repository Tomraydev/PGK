///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 23 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "GUI.h"

///////////////////////////////////////////////////////////////////////////

TopFrame::TopFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_button_load = new wxButton( this, wxID_ANY, wxT("Wczytaj obrazek"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button_load, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button_censor = new wxButton( this, wxID_ANY, wxT("Cenzura"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button_censor, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_button_erode = new wxButton( this, wxID_ANY, wxT("Erode"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_button_erode, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_checkBox_animation = new wxCheckBox( this, wxID_ANY, wxT("Animacja"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer4->Add( m_checkBox_animation, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );

	m_gauge1 = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL );
	m_gauge1->SetValue( 0 );
	m_gauge1->Hide();

	bSizer4->Add( m_gauge1, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer2->Add( bSizer4, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_textCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 300,200 ), wxTE_MULTILINE );
	bSizer5->Add( m_textCtrl, 0, wxALL, 5 );


	bSizer2->Add( bSizer5, 0, wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_panel_image = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 800,533 ), wxTAB_TRAVERSAL );
	m_panel_image->SetBackgroundColour( wxColour( 0, 0, 0 ) );

	bSizer3->Add( m_panel_image, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	bSizer1->Fit( this );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( TopFrame::TopFrameOnUpdateUI ) );
	m_button_load->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_loadOnButtonClick ), NULL, this );
	m_button_censor->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_censorOnButtonClick ), NULL, this );
	m_button_erode->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_erodeOnButtonClick ), NULL, this );
	m_checkBox_animation->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TopFrame::m_checkBox_animationOnCheckBox ), NULL, this );
}

TopFrame::~TopFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( TopFrame::TopFrameOnUpdateUI ) );
	m_button_load->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_loadOnButtonClick ), NULL, this );
	m_button_censor->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_censorOnButtonClick ), NULL, this );
	m_button_erode->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( TopFrame::m_button_erodeOnButtonClick ), NULL, this );
	m_checkBox_animation->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( TopFrame::m_checkBox_animationOnCheckBox ), NULL, this );

}
