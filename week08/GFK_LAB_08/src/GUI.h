///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Mar 23 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/button.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/checkbox.h>
#include <wx/gauge.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class TopFrame
///////////////////////////////////////////////////////////////////////////////
class TopFrame : public wxFrame
{
	private:

	protected:
		wxButton* m_button_load;
		wxButton* m_button_censor;
		wxButton* m_button_erode;
		wxCheckBox* m_checkBox_animation;
		wxGauge* m_gauge1;
		wxTextCtrl* m_textCtrl;
		wxPanel* m_panel_image;

		// Virtual event handlers, overide them in your derived class
		virtual void TopFrameOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void m_button_loadOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_censorOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_button_erodeOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_checkBox_animationOnCheckBox( wxCommandEvent& event ) { event.Skip(); }


	public:

		TopFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( -1,-1 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~TopFrame();

};

