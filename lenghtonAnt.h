#pragma once
#include <windows.h>
using namespace std;

void CreatRect(HDC dc, int nx, int ny, int SizeOfPart, int width, int height, int padding, HBITMAP hbm) {
	const int size = 4;
	POINT p[size];

	p[0] = { nx + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[1] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[2] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };
	p[3] = { nx + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };

	Polygon(dc, p, size);
}

struct vectorAnt {
	int x;
	int y;
};

class lengtonAnt {
	public:
		lengtonAnt(HDC mainDc_, HDC buferDC_, HBITMAP hbm_, int xn, int yn, vectorAnt vect_, int width_, int height_, int padding_, int sizeOfPart) {
			mainDc = mainDc_;
			buferDC = buferDC_;
			hbm = hbm_;
			x = xn;
			y = yn;
			width = width_;
			height = height_;
			padding = padding_;
			SizeOfPart = sizeOfPart;
			vect = vect_;
		}
		void makeMov() {
			if (WhatColor()) {

				switch (vect.x) {
				case -1:
					vect.x = 0;
					vect.y = -1;
					break;
				case 1:
					vect.x = 0;
					vect.y = 1;
				case 0:
					switch (vect.y) {
					case -1:
						vect.y = 0;
						vect.x = 1;
						break;
					case 1:
						vect.y = 0;
						vect.x = -1;
						break;
					}
				}

				SelectObject(buferDC, hbm);

				color = RGB(226, 124, 62);
				hBrush = CreateSolidBrush(color);

				SelectObject(buferDC, hBrush);

				CreatRect(buferDC, x, y, SizeOfPart, width, height, padding, hbm);
				
				switch (vect.x) {
				case -1:
					x -= 1;
					break;
				case 1:
					x += 1;
					break;
				case 0:
					switch (vect.y) {
					case -1:
						y -= 1;
						break;
					case 1:
						y += 1;
						break;
					}
				}
			}
			else {
				switch (vect.x) {
				case -1:
					vect.x = 0;
					vect.y = 1;
					break;
				case 1:
					vect.x = 0;
					vect.y = -1;
					break;
				case 0:
					switch (vect.y) {
					case -1:
						vect.y = 0;
						vect.x = -1;
						break;
					case 1:
						vect.y = 0;
						vect.x = 1;
						break;
					}
				}

				SelectObject(buferDC, hbm);

				color = RGB(50, 50, 50);
				hBrush = CreateSolidBrush(color);

				SelectObject(buferDC, hBrush);

				CreatRect(buferDC, x, y, SizeOfPart, width, height, padding, hbm);

				switch (vect.x) {
				case -1:
					x -= 1;
					break;
				case 1:
					x += 1;
					break;
				case 0:
					switch (vect.y) {
					case -1:
						y -= 1;
						break;
					case 1:
						y += 1;
						break;
					}
				}
			}
			BitBlt(mainDc, 0, 0, width, height, buferDC, 0, 0, SRCCOPY);
		}

	private:
		HDC mainDc;
		HDC buferDC;
		HBITMAP hbm;
		COLORREF color;
		HBRUSH hBrush;
		vectorAnt vect;
		int x, y, width, height, padding, SizeOfPart;
		bool WhatColor() {
			if ((GetPixel(mainDc, x + (SizeOfPart / 2) + (padding * x + x * SizeOfPart), y + (SizeOfPart / 2) + (padding * y + y * SizeOfPart)) == RGB(50, 50, 50)) |
				(GetPixel(buferDC, x + (SizeOfPart / 2) + (padding * x + x * SizeOfPart), y + (SizeOfPart / 2) + (padding * y + y * SizeOfPart)) == RGB(50, 50, 50))) { return 1; }
			else { return 0; }
		}
};
