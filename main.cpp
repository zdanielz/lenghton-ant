#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <windows.h>
#include <iostream>
#include <time.h>
#include "lenghtonAnt.h"
using namespace std;

int main(void) {
	srand(time(NULL));
	COLORREF mainColor;

	int CountOfStep = 15000;
	mainColor = RGB(50, 50, 50);

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	int SizeOfPart = 3;
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

	HDC dc = GetDC(NULL);
	HWND hWnd = GetDesktopWindow();


	HDC dcCompatible = CreateCompatibleDC(dc);
	HBITMAP hbm = CreateCompatibleBitmap(dc, width, height);

	SelectObject(dcCompatible, hbm);

	HBRUSH hBrush;
	//color = RGB(226, 124, 62);
	hBrush = CreateSolidBrush(mainColor);
	SelectObject(dcCompatible, hBrush);

	for (size_t y = 0; y < y_; y++) {
		for (size_t x = 0; x < x_; x++) {
			CreatRect(dcCompatible, x, y, SizeOfPart, width, height, padding, hbm);
		}
	}

	lengtonAnt Ant(dc, dcCompatible, hbm, x_ / 2.5, y_ / 2.5, vect_mov, width, height, padding, SizeOfPart, mainColor);

	for (int i = 0; i < 100 / (SizeOfPart / 2); i++) {
		BitBlt(dc, 0, 0, width, height, dcCompatible, 0, 0, SRCCOPY);
	}

	for (int i = 0; i < CountOfStep; i++) {
		Ant.makeMov();
	}

	return 0;
}
