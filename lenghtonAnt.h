#pragma once
#include <windows.h>
using namespace std;

struct vectorAnt {
	int x;
	int y;
};

void CreatRect(HDC dc, int nx, int ny, int SizeOfPart, int width, int height, int padding, HBITMAP hbm) {
	const int size = 4;
	POINT p[size];

	p[0] = { nx + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[1] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + (padding * ny + ny * SizeOfPart) };
	p[2] = { nx + SizeOfPart + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };
	p[3] = { nx + (padding * nx + nx * SizeOfPart), ny + SizeOfPart + (padding * ny + ny * SizeOfPart) };

	Polygon(dc, p, size);
}

class lengtonAnt {
public:
	lengtonAnt(HDC mainDc_, HDC buferDC_, HBITMAP hbm_, int xn_, int yn_, int max_x_, int max_y_, vectorAnt vect_, int width_, int height_, int padding_, int sizeOfPart, COLORREF MainColor) {
		mainDc = mainDc_;
		buferDC = buferDC_;
		hbm = hbm_;
		xn = xn_;
		yn = yn_;
		width = width_;
		height = height_;
		padding = padding_;
		SizeOfPart = sizeOfPart;
		vect = vect_;
		mainColor = MainColor;
		max_x = max_x_;
		max_y = max_y_;
	}
	bool makeMov() {
			cout << "==============" << endl;
			if (WhatColor()) {
				SelectObject(buferDC, hbm);

				color = RGB(226, 124, 62);
				hBrush = CreateSolidBrush(color);
				SelectObject(buferDC, hBrush);

				CreatRect(buferDC, xn, yn, SizeOfPart, width, height, padding, hbm);
				cout << "right" << endl;

				switch (vect.x) {
				case -1:
					vect.x = 0;
					vect.y = -1;
					break;
				case 1:
					vect.x = 0;
					vect.y = 1;
					break;
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

				switch (vect.x) {
				case -1:
					xn -= 1;
					break;
				case 1:
					xn += 1;
					break;
				case 0:
					switch (vect.y) {
					case -1:
						yn -= 1;
						break;
					case 1:
						yn += 1;
						break;
					}
				}

				cout << "vect.x = " << vect.x << endl;
				cout << "vect.y = " << vect.y << endl;
				cout << "x = " << xn << " ; y = " << yn << endl;
				cout << "wh = " << WhatColor() << endl;
				cout << "==============" << endl;

				BitBlt(mainDc, 0, 0, width, height, buferDC, 0, 0, SRCCOPY);
				if (((xn == max_x) & (yn == max_y)) | ((xn == 0) & (yn == 0))) { return 0; }
				else { return 1; }
			}
			else {
				SelectObject(buferDC, hbm);

				color = mainColor;
				hBrush = CreateSolidBrush(color);
				SelectObject(buferDC, hBrush);

				CreatRect(buferDC, xn, yn, SizeOfPart, width, height, padding, hbm);
				cout << "left" << endl;

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
				switch (vect.x) {
				case -1:
					xn -= 1;
					break;
				case 1:
					xn += 1;
					break;
				case 0:
					switch (vect.y) {
					case -1:
						yn -= 1;
						break;
					case 1:
						yn += 1;
						break;
					}
				}

				cout << "vect.x = " << vect.x << endl;
				cout << "vect.y = " << vect.y << endl;
				cout << "x = " << xn << " ; y = " << yn << endl;
				cout << "wh = " << WhatColor() << endl;
				cout << "==============" << endl;

				while (BitBlt(mainDc, 0, 0, width, height, buferDC, 0, 0, SRCCOPY) == 0) {}
				if (((xn == max_x) & (yn == max_y)) | ((xn == 0) & (yn == 0))) { return 0; }
				else { return 1; }
			}
	}

private:
	HDC mainDc;
	HDC buferDC;
	HBITMAP hbm;
	COLORREF color, mainColor;
	HBRUSH hBrush;
	vectorAnt vect;
	int xn, yn, width, height, padding, SizeOfPart, max_x, max_y;
	bool WhatColor() {
		if (GetPixel(buferDC, xn + (SizeOfPart - SizeOfPart / 2) + (padding * xn + xn * SizeOfPart), yn + (SizeOfPart - SizeOfPart / 2) + (padding * yn + yn * SizeOfPart)) == mainColor) {
			return 1;
		}
		else { return 0; }
	}
};
