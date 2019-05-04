#include "GUIMyFrame.h"
#include "CImg.h"
#include "FreeImage.h"
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/dcmemory.h>
#include <wx/filedlg.h>
#include <wx/window.h>
#include <wx/wfstream.h>
#include <wx/image.h>
#include <wx/gdicmn.h>
#include <wx/log.h>
#include <iostream>
#include <string>

using namespace cimg_library;

GUIMyFrame::GUIMyFrame( wxWindow* parent )
:
TopFrame( parent )
{
	wxImage::AddHandler(new wxJPEGHandler);
}

GUIMyFrame::~GUIMyFrame(void) {
	//
}

void GUIMyFrame::TopFrameOnUpdateUI(wxUpdateUIEvent& event) {
	repaint();
	return;
}
void GUIMyFrame::m_button_loadOnButtonClick(wxCommandEvent& event) {
	wxFileDialog openFileDialog(this, _("Open image file"), ".", "",
		"Image files (*.jpg)|*.jpg", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
	if (openFileDialog.ShowModal() == wxID_CANCEL) {
		return;
	}
	wxFileInputStream input_stream(openFileDialog.GetPath());
	if (!input_stream.IsOk())
	{
		wxLogError("Cannot open file '%s'.", openFileDialog.GetPath());
		return;
	}
	wxString fileName = openFileDialog.GetPath();
	img.LoadFile(fileName, wxBITMAP_TYPE_JPEG);
	sourceImg.LoadFile(fileName, wxBITMAP_TYPE_JPEG);

	m_textCtrl->Clear();
	std::string metaData = "";

	FIBITMAP *dib = FreeImage_Load(FIF_JPEG, fileName, JPEG_DEFAULT);
	FITAG *tag = nullptr;

	metaData += "Rozmiar obrazka : " + std::to_string(img.GetSize().x) + "*" + std::to_string(img.GetSize().y) + "\n";
	metaData += "EXIF Info \n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Artist", &tag);
	metaData += "Artist: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "Copyright", &tag);
	metaData += "Copyright: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "ResolutionUnit", &tag);
	metaData += "ResolutionUnit: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "XResolution", &tag);
	metaData += "XResolution: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YCbCrPositioning", &tag);
	metaData += "YCbCrPositioning: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	FreeImage_GetMetadata(FIMD_EXIF_MAIN, dib, "YResolution", &tag);
	metaData += "YResolution: " + std::string(FreeImage_TagToString(FIMD_EXIF_MAIN, tag)) + "\n";

	m_textCtrl->AppendText(metaData);
	FreeImage_Unload(dib);
	repaint();
}
void GUIMyFrame::m_button_censorOnButtonClick(wxCommandEvent& event) {
	if (img.IsOk()) {
		img = sourceImg.Copy();
		int BlurWidth = 0.15*img.GetWidth();
		int BlurHeight = 0.15*img.GetHeight();
		int xStart = 0.57 * img.GetWidth();
		int yStart = 0.02 * img.GetHeight();
		//Copy image fragment
		CImg<unsigned char> cImage(BlurWidth, BlurHeight, 1, 3);
		for (int x = 0; x < BlurWidth; x++) {
			for (int y = 0; y < BlurHeight; y++) {
				cImage(x, y, 0) = img.GetRed(xStart + x, yStart + y);
				cImage(x, y, 1) = img.GetGreen(xStart + x, yStart + y);
				cImage(x, y, 2) = img.GetBlue(xStart + x, yStart + y);
			}
		}
		//Blur image fragment
		cImage.blur(4);
		//Overwrite image fragment
		for (int x = 0; x < BlurWidth; x++) {
			for (int y = 0; y < BlurHeight; y++) {
				img.SetRGB(xStart + x, yStart + y, cImage(x, y, 0), cImage(x, y, 1), cImage(x, y, 2));
			}
		}
		repaint();
	}
	return;
} 
void GUIMyFrame::m_button_erodeOnButtonClick(wxCommandEvent& event) {
	if (img.IsOk()) {
		img = sourceImg.Copy();
		int width = img.GetWidth();
		int height = img.GetHeight();
		CImg<unsigned char> cImage(width, height, 1, 3);
		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				cImage(x, y, 0) = img.GetRed(x, y);
				cImage(x, y, 1) = img.GetGreen(x, y);
				cImage(x, y, 2) = img.GetBlue(x, y);
			}
		}
		cImage.erode(5);
		for (int x = 0; x <width; x++) {
			for (int y = 0; y <height; y++) {
				img.SetRGB(x, y, cImage(x, y, 0), cImage(x, y, 1), cImage(x, y, 2));
			}
		}
		repaint();
	}
}
void GUIMyFrame::m_checkBox_animationOnCheckBox(wxCommandEvent& event) {
	//TODO
	event.Skip();
}

void GUIMyFrame::repaint(void) {
	wxClientDC dcc(m_panel_image);
	wxBufferedDC dc(&dcc);
	//dc.Clear();
	if (img.IsOk()) {
		//img.Resize(wxSize(dc.GetSize().x, dc.GetSize().y), wxPoint(0,0) );
		img.Rescale(dcc.GetSize().x, dcc.GetSize().y);
		//auto debugStr = L"" + std::to_string(dcc.GetSize().x);
		//OutputDebugString(debugStr);
		wxBitmap bitmap(img);
		dc.DrawBitmap(bitmap, 0, 0);
	}
	return;
}