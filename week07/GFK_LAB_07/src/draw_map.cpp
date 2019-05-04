#include <wx/wx.h>
#include "GUIMyFrame1.h"
// UWAGA: TO JEST JEDYNY PLIK, KTORY NALEZY EDYTOWAC **************************

inline float approximate(int N, float d[100][3], float x, float y) {
	float numerator = 0;
	float denominator = 0;
	float w = 1;
	for (int i = 0; i < N; i++) {
		w = 1.0 / fabs((x - d[i][0])*(x - d[i][0]) + (y - d[i][1])*(y - d[i][1]));
		numerator += w * d[i][2];
		denominator += w;
	}
	return numerator / denominator;
}


void GUIMyFrame1::DrawMap(int N, float d[100][3], bool Contour, int MappingType, int NoLevels, bool ShowPoints)
{
	wxMemoryDC memDC;
	memDC.SelectObject(MemoryBitmap);
	memDC.SetBackground(*wxWHITE_BRUSH);
	memDC.Clear();


	memDC.SetPen(*wxBLACK_PEN);
	memDC.SetBrush(*wxTRANSPARENT_BRUSH);


	double zMin{ d[0][2] };
	double zMax{ d[0][2] };
	double ** approx = new double*[500];
	for (int i = 0; i < 500; i++) {
		approx[i] = new double[500];
	}

	for (int i = 0; i < N; i++) {
		if (d[i][2] < zMin) { zMin = d[i][2]; }
		if (d[i][2] > zMax) { zMax = d[i][2]; }
	}


	#pragma omp parallel for
	for (int x = 0; x < 500; x++) {
		for (int y = 0; y < 500; y++) {
			approx[x][y] = approximate(N, d, (x / 100.0) - 2.5, (-y / 100.0) + 2.5);
		}
	}
	
	switch (MappingType) { //TODO
	   case 1: {
		   //Mapa niebiesko-czerwona...
		   for (int x = 0; x < 500; x++) {
			   for (int y = 0; y < 500; y++) {
				   unsigned char val = (approx[x][y] - zMin) * 255 / (zMax - zMin);
				   memDC.SetPen(wxColor(val, 0, 255 - val));
				   memDC.DrawPoint(wxPoint(x, y));
			   }
		   }
		   break;
		   }
	   case 2: {
		   //Mapa niebiesko-zielono-czerwona...
		   for (int x = 0; x < 500; x++) {
			   for (int y = 0; y < 500; y++) {
				   unsigned char val = (approx[x][y] - zMin) * 255 / (zMax - zMin);
				   if (val < 255. / 2.0) {
					   memDC.SetPen(wxColor(0, 2 * val, 255 - 2 * val));
				   }
				   else {
					   memDC.SetPen(wxColor(0.5*val, 2 * (255 - val), 0));
				   }
				   
				   memDC.DrawPoint(wxPoint(x, y));
			   }
		   }
		   break;
	   }
	   case 3: {
		   //Mapa Szara
		   for (int x = 0; x < 500; x++){
			   for (int y = 0; y < 500; y++) {
				   unsigned char val = (approx[x][y] - zMin)*255 / (zMax - zMin);
				   memDC.SetPen(wxColor(val, val, val));
				   memDC.DrawPoint(wxPoint(x, y));
			   }
		   }
		   break;
	   }
	   default: break;
	}
	 
	if (Contour) { //TODO
		//Kontury...
		memDC.SetPen(*wxBLACK_PEN);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);

		for (int l = 0; l < NoLevels; l++) {					//loop all levels
			float threshold = zMin + (l + 1) * (zMax - zMin) / (NoLevels + 1.0);
			for (int x = 0; x < 500; x++) {						//loop all pixels
				for (int y = 0; y < 500; y++) {					//loop all pixels
					if (approx[x][y] > threshold) {
						for (int i = -1; i <= 1; i+=2) {		//loop corners
							for (int j = -1; j <= 1; j+=2) {	//loop corners
								if ((x + i >= 0) && (x + i < 500) &&
									(y + j >= 0) && (y + j < 500) &&
									(approx[x +i][y + j] < threshold)
									) {
									memDC.DrawPoint(x,y);
								}
							}
						}
					}
				}
			}
		}
	}
	if (ShowPoints) {
		memDC.SetPen(*wxBLACK_PEN);
		memDC.SetBrush(*wxTRANSPARENT_BRUSH);
		//resized points
		double ds[100][3] = { 0 };
		for (int i = 0; i < N; i++)
		{
			ds[i][0] = (d[i][0] + 2.5) * 100;
			ds[i][1] = (-d[i][1] + 2.5) * 100;
			ds[i][2] = d[i][2];
		}
		for (int i = 0; i < N; i++) {
			memDC.DrawLine(wxPoint(ds[i][0] - 3, ds[i][1]), wxPoint(ds[i][0] + 4, ds[i][1]));
			memDC.DrawLine(wxPoint(ds[i][0], ds[i][1] - 3), wxPoint(ds[i][0], ds[i][1] + 4));
		}
	}

	for (int i = 0; i < 500; i++) {
		delete[] approx[i];
	}
	delete[] approx;
}

/*
auto str = L"" + std::to_string(d[i][0]) + "\t" + std::to_string(d[i][1]) + "\n";
OutputDebugString(str);
*/