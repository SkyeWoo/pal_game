#include "BackGround.h"

void BackGround::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());
		BitBlt(hdc, getX(), getY() - 600, getWidth(), getHeight(), hdcsrc, 0, 0, SRCCOPY);
		BitBlt(hdc, getX(), getY(), getWidth(), getHeight(), hdcsrc, 0, 0, SRCCOPY);

		DeleteDC(hdcsrc);
	}
}