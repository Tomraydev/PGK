#include <wx/dc.h>
#include <memory>

#include "ChartClass.h"
#include "vecmat.h"

ChartClass::ChartClass(std::shared_ptr<ConfigClass> c) // DEFAULT
{
    cfg= std::move(c);
    x_step=200;
}

void ChartClass::Set_Range() // DEFAULT
{
 double xmin=9999.9,xmax=-9999.9,ymin=9999.9,ymax=-9999.9;
 double x,y,step;
 int i;

 xmin=cfg->Get_x_start();
 xmax=cfg->Get_x_stop();

 step=(cfg->Get_x_stop()-cfg->Get_x_start())/(double)x_step;
 x=cfg->Get_x_start();

 for (i=0;i<=x_step;i++)
  {
   y=GetFunctionValue(x);
   if (y>ymax) ymax=y;
   if (y<ymin) ymin=y;
   x=x+step;
  }

 y_min=ymin;
 y_max=ymax;
 x_min=xmin;
 x_max=xmax;
}


double ChartClass::GetFunctionValue(double x)  // DEFAULT
{
 if (cfg->Get_F_type()==1) return x*x;
 if (cfg->Get_F_type()==2) return 0.5*exp(4*x-3*x*x);
 return x+sin(x*4.0);
}

double ChartClass::Get_Y_min() // DEFAULT
{
	Set_Range();
	return y_min;
}

double ChartClass::Get_Y_max() // DEFAULT
{
	Set_Range();
	return y_max;
}

void ChartClass::Draw(wxDC *dc, int w, int h) // ok
{
 dc->SetBackground(wxBrush(RGB(255, 255, 255)));
 dc->Clear();
 dc->SetPen(wxPen(RGB(255, 0, 0)));
 dc->DrawRectangle(10, 10, w - 20 , h - 20);
 /////////////////////////////////////////////
 dc->SetClippingRegion(wxRect(10, 10, w - 20, h - 20));
 dc->SetFont(*wxNORMAL_FONT);
 dc->SetPen(wxPen(RGB(0, 0, 255)));
 double x_center = -((w - 20) / (cfg->Get_x1() - cfg->Get_x0() )) * cfg->Get_x0();
 double y_center = -((h - 20) / (cfg->Get_y1() - cfg->Get_y0() )) * cfg->Get_y0();
 Matrix final_transformation;
 
 if (cfg->RotateScreenCenter()) {
	 final_transformation =
		get_translation(x_center, y_center)
		* get_rotation(w,h)
		* get_translation(cfg->Get_dX(), cfg->Get_dY())
		* get_scale(w,h);
 }
 else {
	 final_transformation =
		get_translation(x_center, y_center)
		* get_translation(cfg->Get_dX(), cfg->Get_dY() )
		* get_rotation(w, h)
		* get_scale(w, h);
 }
 
 draw_axes(dc, final_transformation, w, h);

 // drawing function values
 dc->SetPen(wxPen(RGB(0, 255, 0)));
 double dx = (cfg->Get_x1() - cfg->Get_x0()) / x_step;
 for (double x = cfg->Get_x_start(); x < cfg->Get_x_stop(); x += dx)
 {
	 line2d(dc, final_transformation, x, GetFunctionValue(x), x + dx, GetFunctionValue(x + dx), h);
 }
 
}

void ChartClass::line2d(wxDC *dc, Matrix t, double x1, double y1, double x2, double y2, int h) // ok
{
	Vector start(x1, y1);
	start = t * start;
	Vector end(x2, y2);
	end = t * end;
	dc->DrawLine(start.GetX(), h - start.GetY(), end.GetX(), h - end.GetY());
	return;
}

void ChartClass::draw_axes(wxDC *dc, Matrix t, int w, int h) {// ok
	double arrow = 0.05;
	double bar = 0.05;
	line2d(dc, t, cfg->Get_x_start(), 0, cfg->Get_x_stop(), 0, h); // horizontal axis
	line2d(dc, t, 0, Get_Y_min(), 0, Get_Y_max(), h); // vertical axis
	// horizontal arrowhead
	line2d(dc, t, cfg->Get_x_stop() - arrow, arrow, cfg->Get_x_stop(), 0, h);
	line2d(dc, t, cfg->Get_x_stop() - arrow, -arrow, cfg->Get_x_stop(), 0, h);
	// vertical arrowhead
	line2d(dc, t, -arrow, Get_Y_max() - arrow, 0, Get_Y_max(), h);
	line2d(dc, t, arrow, Get_Y_max() - arrow, 0, Get_Y_max(), h);
	// horizontal bars
	for (double x = x_min; x < x_max; x += (x_max - x_min) / 3)
	{
		line2d(dc, t, x, -bar, x, bar, h);
		Vector position(x, -bar);
		position = t * position;
		dc->DrawRotatedText(wxString::Format(wxT("%.2lf"), x), position.GetX(), h - position.GetY(), cfg->Get_Alpha());
	}
	// vertical bars
	for (double y = y_min; y < y_max; y += (y_max - y_min) / 3)
	{
		line2d(dc, t, -bar, y, bar, y, h);
		Vector position(bar, y);
		position = t * position;
		dc->DrawRotatedText(wxString::Format(wxT("%.2lf"), y), position.GetX(), h - position.GetY(), cfg->Get_Alpha());
	}

	return;
}

Matrix ChartClass::get_translation(double x, double y) { //ok
	Matrix t;
	t.data[0][0] = 1;
	t.data[1][1] = 1;
	t.data[0][2] = x;
	t.data[1][2] = y;
	return t;
}

Matrix ChartClass::get_scale(int w, int h) { // ok
	Matrix t;
	t.data[0][0] = (w-20) / (cfg->Get_x1() - cfg->Get_x0() );
	t.data[1][1] = (h-20) / (cfg->Get_y1() - cfg->Get_y0() );
	return t;
}

Matrix ChartClass::get_rotation(int w, int h) { // ok
	Matrix t;
	double alfa = cfg->Get_Alpha() / 180.0 * M_PI; // degrees to radians
	t.data[0][0] = cos(alfa);
	t.data[0][1] = -sin(alfa);
	t.data[1][0] = sin(alfa);
	t.data[1][1] = cos(alfa);
	return t;
}

