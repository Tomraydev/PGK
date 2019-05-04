#pragma once

#include "GUI.h"

#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>


/** Implementing MyFrame */
class GUIMyFrame : public TopFrame
{
	protected:
		wxImage img;
		wxImage sourceImg;
		// Handlers for TopFrame events.
		void TopFrameOnUpdateUI(wxUpdateUIEvent& event);
		void m_button_loadOnButtonClick(wxCommandEvent& event);
		void m_button_censorOnButtonClick(wxCommandEvent& event);
		void m_button_erodeOnButtonClick(wxCommandEvent& event);
		void m_checkBox_animationOnCheckBox(wxCommandEvent& event);
		void repaint();

	public:
		/** Constructor */
		GUIMyFrame( wxWindow* parent );
		/** Destructor */
		~GUIMyFrame(void);
};

