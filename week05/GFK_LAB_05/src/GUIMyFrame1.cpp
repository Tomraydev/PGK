#include "GUIMyFrame1.h"
#include <vector>
#include <fstream>
#include "vecmat.h"

struct Point {
 float x, y, z;
 Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

struct Color {
 int R, G, B;
 Color(int _R, int _G, int _B) : R(_R), G(_G), B(_B) {}
};

struct Segment {
 Point begin, end;
 Color color;
 Segment(Point _begin, Point _end, Color _color) : begin(_begin), end(_end), color(_color) {}
};

std::vector<Segment> data;

GUIMyFrame1::GUIMyFrame1( wxWindow* parent ) : MyFrame1( parent )
{
 m_button_load_geometry->SetLabel(_("Wczytaj Geometri\u0119"));
 m_staticText25->SetLabel(_("Obr\u00F3t X:"));
 m_staticText27->SetLabel(_("Obr\u00F3t Y:"));
 m_staticText29->SetLabel(_("Obr\u00F3t Z:"));

 WxSB_TranslationX->SetRange(0, 200); WxSB_TranslationX->SetValue(100);
 WxSB_TranslationY->SetRange(0, 200); WxSB_TranslationY->SetValue(100);
 WxSB_TranslationZ->SetRange(0, 200); WxSB_TranslationZ->SetValue(100);

 WxSB_RotateX->SetRange(0, 360); WxSB_RotateX->SetValue(0);
 WxSB_RotateY->SetRange(0, 360); WxSB_RotateY->SetValue(0);
 WxSB_RotateZ->SetRange(0, 360); WxSB_RotateZ->SetValue(0);

 WxSB_ScaleX->SetRange(1, 200); WxSB_ScaleX->SetValue(100);
 WxSB_ScaleY->SetRange(1, 200); WxSB_ScaleY->SetValue(100);
 WxSB_ScaleZ->SetRange(1, 200); WxSB_ScaleZ->SetValue(100);
}

void GUIMyFrame1::WxPanel_Repaint( wxUpdateUIEvent& event )
{
 Repaint();
}

void GUIMyFrame1::m_button_load_geometry_click( wxCommandEvent& event )
{
 wxFileDialog WxOpenFileDialog(this, wxT("Choose a file"), wxT(""), wxT(""), wxT("Geometry file (*.geo)|*.geo"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);

 if (WxOpenFileDialog.ShowModal() == wxID_OK)
 {
  double x1, y1, z1, x2, y2, z2;
  int r, g, b;

  std::ifstream in(WxOpenFileDialog.GetPath().ToAscii());
  if (in.is_open())
  {
   data.clear();
   while (!in.eof())
   {
    in >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> r >> g >> b;
    data.push_back(Segment(Point(x1, y1, z1), Point(x2, y2, z2), Color(r, g, b)));
   }
   in.close();
  }
 }
}

void GUIMyFrame1::m_button_reset_click(wxCommandEvent& event) {
	WxSB_TranslationX->SetValue(100);
	WxSB_TranslationY->SetValue(100);
	WxSB_TranslationZ->SetValue(100);

	WxSB_RotateX->SetValue(0);
	WxSB_RotateY->SetValue(0);
	WxSB_RotateZ->SetValue(0);

	WxSB_ScaleX->SetValue(100);
	WxSB_ScaleY->SetValue(100);
	WxSB_ScaleZ->SetValue(100);

	Scrolls_Updated(wxScrollEvent());
}

void GUIMyFrame1::Scrolls_Updated( wxScrollEvent& event )
{
WxST_TranslationX->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationX->GetValue() - 100) / 50.0));
WxST_TranslationY->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationY->GetValue() - 100) / 50.0));
WxST_TranslationZ->SetLabel(wxString::Format(wxT("%g"), (WxSB_TranslationZ->GetValue() - 100) / 50.0));

WxST_RotateX->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateX->GetValue()));
WxST_RotateY->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateY->GetValue()));
WxST_RotateZ->SetLabel(wxString::Format(wxT("%d"), WxSB_RotateZ->GetValue()));

WxST_ScaleX->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleX->GetValue() / 100.0));
WxST_ScaleY->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleY->GetValue() / 100.0));
WxST_ScaleZ->SetLabel(wxString::Format(wxT("%g"), WxSB_ScaleZ->GetValue() / 100.0));


Repaint();
}


void GUIMyFrame1::Repaint()
{
	wxClientDC dc(WxPanel);
	wxBufferedDC dcBuff(&dc);
	int w, h;
	WxPanel->GetSize(&w, &h);
	dcBuff.SetBackground(wxBrush(RGB(255, 255, 255)));
	dcBuff.Clear();

	Matrix4 tCenter = getCenter();
	Matrix4 transform;
	Matrix4 tScale = getScale(WxSB_ScaleX->GetValue() / 100.0, WxSB_ScaleY->GetValue() / 100.0, WxSB_ScaleZ->GetValue() / 100.0);
	Matrix4 tTranslate = getTranslation((WxSB_TranslationX->GetValue() - 100.0) / 50.0, (WxSB_TranslationY->GetValue() - 100.0) / 50.0 , (WxSB_TranslationZ->GetValue() - 100.0) / 50.0 +2 );
	Matrix4 tRotX = getRotationX(WxSB_RotateX->GetValue());
	Matrix4 tRotY = getRotationY(WxSB_RotateY->GetValue());
	Matrix4 tRotZ = getRotationZ(WxSB_RotateZ->GetValue());
	Matrix4 tRot = tRotX * tRotY * tRotZ;
	transform = tTranslate * tRot * tScale;

	//Coloring
	double z_max = 0;
	double z_min = 0;
	for (unsigned int i = 0; i < data.size(); i++) {
		double z = (data[i].begin.z + data[i].end.z) / 2;
		if (z > z_max) {
			z_max = z;
		}
		else if (z < z_min) {
			z_min = z;
		}
	}
	int color_r[10000];// wiem ze to jest zle
	int color_b[10000];// wiem ze to jest zle
	for (unsigned int i = 0; i < data.size(); i++) {
		double z = (data[i].begin.z + data[i].end.z) / 2;
		color_r[i] = (z - z_min) / (z_max - z_min) * 255.0;
		color_b[i] = 255.0 - color_r[i];
	}


	for (unsigned int i = 0; i < data.size(); i++)
	{
		// Load
		Vector4 start(
			data[i].begin.x,
			data[i].begin.y,
			data[i].begin.z
		);

		Vector4 stop(
			data[i].end.x,
			data[i].end.y,
			data[i].end.z
		);

		// Transform
		start = transform * start;
		stop = transform * stop;

		if (start.GetZ() < 0 && stop.GetZ() < 0) {
			continue;
		}
		if (start.GetZ() < 0 && stop.GetZ() > 0) {
			Vector4 diff = stop - start;
			double step = fabs((start.data[2] / diff.data[2])); // to nie dziala tak jak trzeba
			start.data[0] = start.data[0] + step * diff.data[0];
			start.data[1] = start.data[1] + step * diff.data[1];
			start.data[2] = 0;
		}
		if (start.GetZ() > 0 && stop.GetZ() < 0) {
			Vector4 diff = start - stop;
			double step = fabs((stop.data[2] / diff.data[2])); // to nie dziala tak jak trzeba
			stop.data[0] = stop.data[0] + step * diff.data[0];
			stop.data[1] = stop.data[1] + step * diff.data[1];
			stop.data[2] = 0;
		}

		// Projection
		start.Set(start.GetX() / start.GetZ(), start.GetY() / start.GetZ(), start.GetZ());
		stop.Set(stop.GetX() / stop.GetZ(), stop.GetY() / stop.GetZ(), stop.GetZ());

		// Move the projection to the center
		start = tCenter * start;
		stop = tCenter * stop;

		// Draw
		dcBuff.SetPen(wxPen(wxColor(color_r[i], data[i].color.G, color_b[i])));
		//dcBuff.SetPen(wxPen(wxColor(data[i].color.R, data[i].color.G, data[i].color.B)));
		dcBuff.DrawLine(start.GetX() * w, start.GetY() * h, stop.GetX() * w, stop.GetY() * h);
	}
}

Matrix4 GUIMyFrame1::getCenter(void) {
	Matrix4 t;
	t.data[0][3] = 0.5;
	t.data[1][3] = 0.5;
	t.data[2][3] = 0.0;
	return t;
}

Matrix4 GUIMyFrame1::getScale(double xs, double ys, double zs) {
	Matrix4 t;
	t.data[0][0] = xs;
	t.data[1][1] = -ys;
	t.data[2][2] = zs;
	return t;
}

Matrix4 GUIMyFrame1::getTranslation(double xt, double yt, double zt) {
	Matrix4 t;
	t.data[0][3] = xt;
	t.data[1][3] = -yt;
	t.data[2][3] = zt;
	return t;
}

Matrix4 GUIMyFrame1::getRotationX(double angle) {
	Matrix4 t;
	double a = -angle / 180 * M_PI; // in radians
	t.data[1][1] = cos(a);
	t.data[1][2] = -sin(a);
	t.data[2][1] = sin(a);
	t.data[2][2] = cos(a);
	return t;
}

Matrix4 GUIMyFrame1::getRotationY(double angle) {
	Matrix4 t;
	double a = -angle / 180 * M_PI; // in radians
	t.data[0][0] = cos(a);
	t.data[0][2] = sin(a);
	t.data[2][0] = -sin(a);
	t.data[2][2] = cos(a);
	return t;
}

Matrix4 GUIMyFrame1::getRotationZ(double angle) {
	Matrix4 t;
	double a = -angle / 180 * M_PI; // in radians
	t.data[0][0] = cos(a);
	t.data[0][1] = -sin(a);
	t.data[1][0] = sin(a);
	t.data[1][1] = cos(a);
	return t;
}