#pragma once
#include "BuildFrame.h"
#include <wx/dcbuffer.h>
#include <wx/filedlg.h>

class MyFrame : public BuildFrame {
public:
	MyFrame();

	void draw(wxClientDC &dcClient);
	virtual void onUpdateUI(wxUpdateUIEvent& event);
	virtual void onClickSave(wxCommandEvent& event) {}
	virtual void onCheckBanana(wxCommandEvent& event);
	virtual void onScrollBanana(wxScrollEvent& event);
	virtual void onClickStarColor(wxCommandEvent& event) {}
	virtual void onTextInput(wxCommandEvent& event);
	virtual void onChoiceShape(wxCommandEvent& event);

private:
	wxColor *starColor;
	int chosenShape;
	wxPoint starVertices[5];
	bool bananaActive;
	int bananaPosition;
	wxBitmap * bitmapBanana;
	wxBitmap * bitmapSave;
	wxString text;
	wxImageHandler * imageHandler;
	wxImage * imgBanana;
};