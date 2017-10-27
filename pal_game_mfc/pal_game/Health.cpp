#include "Health.h"

RoleHealth::RoleHealth(HBITMAP hbmp) : GameObject(hbmp) {
	setX(20); setY(560); hp = 0;
}

void RoleHealth::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());
		for (int i = 0; i < hp; i++)
			BitBlt(hdc, getX() + i * 3, getY(), getWidth(), getHeight(), hdcsrc, 0, 0, SRCCOPY);
		DeleteDC(hdcsrc);
	}
}