///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 23 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "BuildFrame.h"

///////////////////////////////////////////////////////////////////////////

BuildFrame::BuildFrame(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxSize(600, 400), wxDefaultSize);

	wxBoxSizer* topSizer;
	topSizer = new wxBoxSizer(wxHORIZONTAL);

	topSizer->SetMinSize(wxSize(600, 400));
	wxGridSizer* drawingGrid;
	drawingGrid = new wxGridSizer(0, 1, 0, 0);

	drawingGrid->SetMinSize(wxSize(400, 400));
	drawingPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
	drawingPanel->SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT));

	drawingGrid->Add(drawingPanel, 1, wxEXPAND | wxALL, 5);


	topSizer->Add(drawingGrid, 1, wxEXPAND, 5);

	wxGridSizer* controlGrid;
	controlGrid = new wxGridSizer(12, 1, 0, 0);

	controlGrid->SetMinSize(wxSize(-1, 400));
	btnSave = new wxButton(this, wxID_ANY, wxT("Zapis do pliku"), wxDefaultPosition, wxDefaultSize, 0);
	controlGrid->Add(btnSave, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 5);

	checkBoxBanana = new wxCheckBox(this, wxID_ANY, wxT("banan"), wxDefaultPosition, wxDefaultSize, 0);
	controlGrid->Add(checkBoxBanana, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	scrollBarBanana = new wxScrollBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSB_HORIZONTAL);
	scrollBarBanana->Enable(false);
	scrollBarBanana->SetMinSize(wxSize(180, -1));

	controlGrid->Add(scrollBarBanana, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	gaugeBanana = new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL);
	gaugeBanana->SetValue(0);
	gaugeBanana->SetMinSize(wxSize(180, -1));

	controlGrid->Add(gaugeBanana, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	btnStarColor = new wxButton(this, wxID_ANY, wxT("kolor gwiazdki"), wxDefaultPosition, wxDefaultSize, 0);
	controlGrid->Add(btnStarColor, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	textInput = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
	controlGrid->Add(textInput, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);

	wxString choiceShapeChoices[] = { wxT("gwiazdka"), wxT("ksiê¿yc"), wxT("s³onko") };
	int choiceShapeNChoices = sizeof(choiceShapeChoices) / sizeof(wxString);
	choiceShape = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, choiceShapeNChoices, choiceShapeChoices, 0);
	choiceShape->SetSelection(0);
	controlGrid->Add(choiceShape, 0, wxALL | wxALIGN_CENTER_HORIZONTAL, 5);


	topSizer->Add(controlGrid, 0, wxEXPAND, 5);


	this->SetSizer(topSizer);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	this->Connect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(BuildFrame::onUpdateUI));
	btnSave->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(BuildFrame::onClickSave), NULL, this);
	checkBoxBanana->Connect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(BuildFrame::onCheckBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_TOP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Connect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	btnStarColor->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(BuildFrame::onClickStarColor), NULL, this);
	textInput->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(BuildFrame::onTextInput), NULL, this);
	choiceShape->Connect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(BuildFrame::onChoiceShape), NULL, this);
}

BuildFrame::~BuildFrame()
{
	// Disconnect Events
	this->Disconnect(wxEVT_UPDATE_UI, wxUpdateUIEventHandler(BuildFrame::onUpdateUI));
	btnSave->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(BuildFrame::onClickSave), NULL, this);
	checkBoxBanana->Disconnect(wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(BuildFrame::onCheckBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_TOP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_BOTTOM, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_LINEUP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_PAGEUP, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	scrollBarBanana->Disconnect(wxEVT_SCROLL_CHANGED, wxScrollEventHandler(BuildFrame::onScrollBanana), NULL, this);
	btnStarColor->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(BuildFrame::onClickStarColor), NULL, this);
	textInput->Disconnect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(BuildFrame::onTextInput), NULL, this);
	choiceShape->Disconnect(wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler(BuildFrame::onChoiceShape), NULL, this);

}
