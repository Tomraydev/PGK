#include "MyFrame.h"
#include <wx/wxprec.h>
#include <wx/colordlg.h>
#include <wx/wfstream.h>
#include <wx/dcclient.h>
#include <wx/gdicmn.h>
#include <iostream>
#include <wx/dcmemory.h>
#include <wx/filedlg.h>
#include <wx/image.h>
#include <wx/dcbuffer.h>

MyFrame::MyFrame() : BuildFrame(nullptr) {
	SetIcon(wxIcon(wxString("favicon.ico")));
	for (int i = 0; i < 5; i++)
	{
		starVertices[i] = wxPoint(0, 0);
	}
	chosenShape = 0;

	imageHandler = new wxPNGHandler();
	wxImage::AddHandler(imageHandler);
	imgBanana = new wxImage(wxSize(50, 38));
	imgBanana->LoadFile(wxString("banan.png"), wxBITMAP_TYPE_PNG);
	bitmapBanana = new wxBitmap(*imgBanana);

	text = "text";
	bananaPosition = 0;
	bananaActive = false;
	scrollBarBanana->SetScrollbar(0, 1, 100, 1);
	scrollBarBanana->Enable(false);
}

void MyFrame::onUpdateUI(wxUpdateUIEvent& event) {
	wxClientDC dcClient(drawingPanel);
	draw(dcClient);
}

void MyFrame::draw(wxClientDC &dcClient) {
	wxBufferedDC dcBuffer(&dcClient);
	PrepareDC(dcBuffer);

	dcBuffer.Clear();

	wxSize c = drawingPanel->GetVirtualSize();
	int x = c.GetWidth() / 2;
	int y = c.GetHeight() / 2;
	int r = 20;

	dcBuffer.SetPen(wxPen(wxColor(0, 0, 0), 1));
	dcBuffer.DrawCircle(x, y - r - 5, r); //head
	dcBuffer.DrawEllipse(x - 10 -5, y - 12 - r + 3, 10, 6); //horizontal eye
	dcBuffer.DrawEllipse(x + 10 - 3, y - 12 - r, 6, 10); //vertical eye
	// smile/frown depending on banana

	dcBuffer.DrawLine(x, y - 5, x, y + 60); //body
	dcBuffer.DrawLine(x, y + 60, x + 30, y + r + 90); //right leg
	dcBuffer.DrawLine(x, y + 60, x - 30, y + r + 90); //left leg
	dcBuffer.DrawLine(x, y + 10, x + 30, y + r + 30); //right arm
	// left arm depending on banana

	starVertices[0] = wxPoint(x - 70, y - 100 + 10);
	starVertices[1] = wxPoint(x - 70 + 15, y - 100 + 50);
	starVertices[2] = wxPoint(x - 70 - 25, y - 100 + 25);
	starVertices[3] = wxPoint(x - 70 + 25, y - 100 + 25);
	starVertices[4] = wxPoint(x - 70 - 15, y - 100 + 50);

	if (chosenShape == 0) {
		dcBuffer.DrawPolygon(5, starVertices, wxWINDING_RULE);
	}
	else if (chosenShape == 1) {
		dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
		dcBuffer.SetBrush(wxBrush(*wxGREY_BRUSH));
		dcBuffer.DrawCircle(wxPoint(x - 70, y - 90 + r), r);
		dcBuffer.SetPen(wxPen(*wxWHITE_PEN));
		dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
		dcBuffer.DrawCircle(wxPoint(x - 70 - 15, y - 90 - 15 + r), r+5);

		dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
	}
	else {
		dcBuffer.SetPen(wxPen(*wxYELLOW_PEN));
		dcBuffer.SetBrush(wxBrush(*wxYELLOW_BRUSH));
		dcBuffer.DrawCircle(wxPoint(x - 70, y - 90 + r), r);
		dcBuffer.SetPen(wxPen(*wxBLACK_PEN));
	}

	if (bananaActive) {
		if (bitmapBanana) {
			dcBuffer.DrawBitmap(*bitmapBanana, x - 30 - 25, y +10+30 -bananaPosition / 2 - 25);
		}

		dcBuffer.SetBrush(wxBrush(*wxWHITE_BRUSH));
		dcBuffer.DrawEllipticArc(x - 5, y - 5 - r / 2, 10, 5, 0, -180); // smile
		dcBuffer.DrawLine(x, y + 10, x - 30, y + r + 30 - bananaPosition/2); //left arm

	}
	else {
		dcBuffer.DrawLine(x, y + 10, x - 30, y + r + 30); //left arm
		dcBuffer.DrawEllipticArc(x - 5, y - 5 - r / 2, 10, 5, 0, 180); // frown
	}

	//TEXT
	dcBuffer.SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL));
	dcBuffer.DrawText(text, x - 100, y + 120);
	dcBuffer.SetFont(wxFont(25, wxFONTFAMILY_DECORATIVE, wxFONTSTYLE_ITALIC,wxFONTWEIGHT_BOLD ));
	dcBuffer.DrawRotatedText(text, x + 100, y + 120, 90);
}

void MyFrame::onChoiceShape(wxCommandEvent& event) {
	chosenShape = event.GetSelection();
	Refresh();
}

void MyFrame::onCheckBanana(wxCommandEvent& event) {
	bananaActive = event.IsChecked();
	if (bananaActive) {
		scrollBarBanana->Enable(true);
	}
	else {
		scrollBarBanana->Enable(false);
	}
	Refresh();
}

void MyFrame::onScrollBanana(wxScrollEvent& event) {
	//text = std::to_string(event.GetPosition());
	bananaPosition = event.GetPosition();
	gaugeBanana->SetValue(event.GetPosition());
	Refresh();
}

void MyFrame::onTextInput(wxCommandEvent& event) {
	text = event.GetString();
	Refresh();
}