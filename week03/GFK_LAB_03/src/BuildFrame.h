///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 23 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/panel.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/scrolbar.h>
#include <wx/gauge.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class BuildFrame
///////////////////////////////////////////////////////////////////////////////
class BuildFrame : public wxFrame
{
private:

protected:
	wxPanel* drawingPanel;
	wxButton* btnSave;
	wxCheckBox* checkBoxBanana;
	wxScrollBar* scrollBarBanana;
	wxGauge* gaugeBanana;
	wxButton* btnStarColor;
	wxTextCtrl* textInput;
	wxChoice* choiceShape;

	// Virtual event handlers, overide them in your derived class
	virtual void onUpdateUI(wxUpdateUIEvent& event) { event.Skip(); }
	virtual void onClickSave(wxCommandEvent& event) { event.Skip(); }
	virtual void onCheckBanana(wxCommandEvent& event) { event.Skip(); }
	virtual void onScrollBanana(wxScrollEvent& event) { event.Skip(); }
	virtual void onClickStarColor(wxCommandEvent& event) { event.Skip(); }
	virtual void onTextInput(wxCommandEvent& event) { event.Skip(); }
	virtual void onChoiceShape(wxCommandEvent& event) { event.Skip(); }


public:

	BuildFrame(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("GFK LAB 03 - Tomasz Rajchel"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(500, 300), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~BuildFrame();

};

