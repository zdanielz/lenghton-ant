//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include <windows.h>
#include <iostream>
#include <time.h>
#include "lenghtonAnt.h"
using namespace std;

int main(void) {
	srand(time(NULL));

	int CountOfStep = 1000;

	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);

	int SizeOfPart = 5;
	int padding = 0;
	int c = 0;

	int x_ = width / (SizeOfPart + padding), y_ = height / (SizeOfPart + padding);

	while (((width % (SizeOfPart + padding)) != 0) & ((height % (SizeOfPart + padding)) != 0)) {
		SizeOfPart -= 1;
		cout << SizeOfPart << endl;
	}

	HDC dc = GetDC(NULL);
	HWND hWnd = GetDesktopWindow();


	HDC dcCompatible = CreateCompatibleDC(dc);
	HBITMAP hbm = CreateCompatibleBitmap(dc, width, height);

	SelectObject(dcCompatible, hbm);

	COLORREF color;
	HBRUSH hBrush;

	//color = RGB(226, 124, 62);
	color = RGB(50, 50, 50);
	hBrush = CreateSolidBrush(color);
	SelectObject(dcCompatible, hBrush);

	for (size_t y = 0; y < y_; y++) {
		for (size_t x = 0; x < x_; x++) {
			CreatRect(dcCompatible, x, y, SizeOfPart, width, height, padding, hbm);
		}
	}

	vectorAnt vect_mov;
	vect_mov.x = -1;
	vect_mov.y = 0;
	lengtonAnt Ant(dc, dcCompatible, hbm, x_ / 2.5, y_ / 2.5, vect_mov, width, height, padding, SizeOfPart);

	for (int i = 0; i < 100 / (SizeOfPart / 2); i++) {
		BitBlt(dc, 0, 0, width, height, dcCompatible, 0, 0, SRCCOPY);
	}

	for (int i = 0; i < CountOfStep; i++) {
		Ant.makeMov();
	}

	return 0;
}
