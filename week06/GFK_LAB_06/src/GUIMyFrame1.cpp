#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{
 m_staticText1->SetLabel(_(L"Jasno\u015B\u0107"));
 m_b_threshold->SetLabel(_(L"Pr\u00F3g 128"));
 this->SetBackgroundColour(wxColor(192, 192, 192));
 m_scrolledWindow->SetScrollbars(25, 25, 52, 40);
 m_scrolledWindow->SetBackgroundColour(wxColor(192, 192, 192));
 clearImage = false;
}

void GUIMyFrame1::m_scrolledWindow_update( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_b_grayscale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().ConvertToGreyscale();
}

void GUIMyFrame1::m_b_blur_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Blur(5);
}

void GUIMyFrame1::m_b_mirror_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Mirror();
}

void GUIMyFrame1::m_b_replace_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.Replace(254, 0, 0, 0, 0, 255);
}

void GUIMyFrame1::m_b_rescale_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Rescale(320, 240);
	clearImage = true;
}

void GUIMyFrame1::m_b_rotate_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy().Rotate(30* M_PI / 180, wxPoint(Img_Org.GetWidth() / 2, Img_Org.GetHeight() / 2));
}

void GUIMyFrame1::m_b_rotate_hue_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.RotateHue(0.5);
}

void GUIMyFrame1::m_b_mask_click( wxCommandEvent& event )
{
	clearImage = true;
	Img_Cpy = Img_Org.Copy();
	Img_Cpy.SetMaskFromImage(Img_Mask, 0, 0, 0);
}

void GUIMyFrame1::m_s_brightness_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Brightness(...), ktora zmienia jasnosc. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Brightness(...)
Brightness(m_s_brightness->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_s_contrast_scroll( wxScrollEvent& event )
{
// Tutaj, w reakcji na zmiane polozenia suwaka, wywolywana jest funkcja
// Contrast(...), ktora zmienia kontrast. W tym miejscu nic nie
// zmieniamy. Do uzupelnienia pozostaje funkcja Contrast(...)
Contrast(m_s_contrast->GetValue() - 100);
Repaint();
}

void GUIMyFrame1::m_b_prewitt_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* data = Img_Cpy.GetData();
	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	unsigned char* old = new unsigned char[size];
	int row = Img_Cpy.GetWidth()*3;

	for (int i = 0; i < size; i++){
		old[i] = data[i];
	}

	for (int i = 1; i < Img_Cpy.GetHeight() - 1; i++) {
		for (int j = 1; j < Img_Cpy.GetWidth() - 1; j++) {
			for (int k = 0; k < 3; k++) {
				int val = 0;
				val += -old[k + (i - 1) * row + (j - 1) * 3];
				val += old[k + (i - 1) * row + (j + 1) * 3];
				val += -old[k + i * row + (j - 1) * 3];
				val += old[k + i * row + (j + 1) * 3];
				val += -old[k + (i + 1) * row + (j - 1) * 3];
				val += old[k + (i + 1) * row + (j + 1) * 3];

				data[k + i * row + j * 3] = fabs(val)/3.0;
			}
		}
	}
	delete[] old;
	return;
}

void GUIMyFrame1::m_b_threshold_click( wxCommandEvent& event )
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* data = Img_Cpy.GetData();
	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	for (int i = 0; i < size; i++) {
		data[i] = data[i] > 128 ? 255 : 0;
	}
	return;
}


void GUIMyFrame1::Contrast(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* data = Img_Cpy.GetData();
	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	double a = (value + 100.0) / (101.0 - value);
	for (int i = 0; i < size; i++) {
		int tmp = a * (data[i] - 128) + 128;
		if (tmp > 255) {
			data[i] = 255;
		}
		else if (tmp < 0) {
			data[i] = 0;
		}
		else {
			data[i] = tmp;
		}
	}
}

void GUIMyFrame1::Repaint()
{
 wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
 wxClientDC dc(m_scrolledWindow);   // Pobieramy kontekst okna
 m_scrolledWindow->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
 if (clearImage) {
	 dc.Clear();
	 clearImage = false;
 }
 dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}

void GUIMyFrame1::Brightness(int value)
{
	Img_Cpy = Img_Org.Copy();
	unsigned char* data = Img_Cpy.GetData();
	int size = Img_Cpy.GetWidth() * Img_Cpy.GetHeight() * 3;
	for (int i = 0; i < size; i++) {
		int tmp = data[i] + value;
		if (tmp > 255) {
			data[i] = 255;
		}
		else if (tmp < 0) {
			data[i] = 0;
		}
		else {
			data[i] = tmp;
		}
	}
	return;
}