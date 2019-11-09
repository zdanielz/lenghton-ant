//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <windows.h>
#include <iostream>
#include <time.h>
#include "lenghtonAnt.h"
using namespace std;

int main(void) {
	srand(time(NULL));
	COLORREF mainColor;

	mainColor = RGB(50, 50, 50);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	int SizeOfPart = 3;
	int padding = 1;

	int c = 0;
	double x_ = width / (SizeOfPart + padding), y_ = height / (SizeOfPart + padding);
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

	HDC maindc = GetDC(NULL);
	HWND hWnd = GetDesktopWindow();


	HDC buferDc = CreateCompatibleDC(maindc);
	HBITMAP Bitmap = CreateCompatibleBitmap(maindc, width, height);

	SelectObject(buferDc, Bitmap);

	HBRUSH hBrush;
	//color = RGB(226, 124, 62);
	hBrush = CreateSolidBrush(mainColor);
	SelectObject(buferDc, hBrush);

	for (size_t y = 0; y < y_; y++) {
		for (size_t x = 0; x < x_; x++) {
			if((x > x_ / 6) & (x < x_ / 6 * 4) & (y > y_ / 6) & (y < y_ / 6 * 4) & 
				((x - 2 < x_ / 6) | (x + 2 > x_ / 6 * 4) | (y - 2 < y_ / 6) | (y + 2 > y_ / 6 * 4))){
				COLORREF color = RGB(226, 124, 62);
				hBrush = CreateSolidBrush(color);
				SelectObject(buferDc, hBrush);
				CreatRect(buferDc, x, y, SizeOfPart, width, height, padding, Bitmap);
				DeleteObject(hBrush);
			}
			else {
				hBrush = CreateSolidBrush(mainColor);
				SelectObject(buferDc, hBrush);
				CreatRect(buferDc, x, y, SizeOfPart, width, height, padding, Bitmap);
				DeleteObject(hBrush);
			}
		}
	}

	lengtonAnt Ant(maindc, buferDc, Bitmap, x_ / 2.5, y_ / 2.5, x_, y_, vect_mov, width, height, padding, SizeOfPart, mainColor);

	while (Ant.makeMov()) {}

	DeleteDC(buferDc);
	DeleteObject(Bitmap);
	return 0;
}
