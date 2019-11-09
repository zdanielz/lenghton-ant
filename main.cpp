#include <windows.h>
#include <iostream>
#include <time.h>
#include "lenghtonAnt.h"
using namespace std;

int main(void) {
	srand(time(NULL));
	COLORREF mainColor;

	mainColor = RGB(50, 50, 50);

	int width = GetSystemMetrics(SM_CXSCREEN) / 2;
	int height = GetSystemMetrics(SM_CYSCREEN) / 2;

	int SizeOfPart = 5;
	int padding = 1;

	int c = 0;
	int x_ = width / (SizeOfPart + padding), y_ = height / (SizeOfPart + padding);
	vectorAnt vect_mov;
	vect_mov.x = -1;
	vect_mov.y = 0;
	int buferSizeOfPart = SizeOfPart;

	while (((width % (SizeOfPart + padding)) != 0) & ((height % (SizeOfPart + padding)) != 0)) {
		if (SizeOfPart == 0) { break; }
		SizeOfPart -= 1;
	}
	if (SizeOfPart == 0) {
		while (((width % (SizeOfPart + padding)) != 0) & ((height % (SizeOfPart + padding)) != 0)) {
			if ((SizeOfPart == (SizeOfPart * 2))) { break; }
			SizeOfPart += 1;
		}
	}

	HDC mainDc = GetDC(NULL);

	HDC buferDc = CreateCompatibleDC(mainDc);
	HBITMAP Bitmap = CreateCompatibleBitmap(mainDc, width, height);

	SelectObject(mainDc, Bitmap);
	SelectObject(buferDc, Bitmap);

	HBRUSH hBrush;
	//color = RGB(226, 124, 62);
	hBrush = CreateSolidBrush(mainColor);

	SelectObject(buferDc, hBrush);

	for (size_t y = 0; y < y_; y++) {
		for (size_t x = 0; x < x_; x++) {
			CreatRect(buferDc, x, y, SizeOfPart, width, height, padding, Bitmap);
		}
	}

	BitBlt(mainDc, 0, 0, width, height, buferDc, 0, 0, SRCCOPY);

	lengtonAnt Ant(mainDc, buferDc, Bitmap, x_ / 2.5, y_ / 2.5, x_, y_, vect_mov, width, height, padding, SizeOfPart, mainColor);

	int i = 1;
	while(i) { i = Ant.makeMov(); }

	DeleteDC(buferDc);
	DeleteObject(Bitmap);
	return 0;
}
