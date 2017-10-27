#include "Goods.h"

Goods::Goods(HBITMAP hbmp, int type) : GameObject(hbmp) {
	setX(rand() & 600 + 100);
	setY(0);
	dead = false;
	speed_x = rand() % 5 - 2;
	speed_y = rand() % 2 + 1;
	if (speed_x == 0 && speed_y == 1)
		speed_x = 1;
	this->type = type;
}

void Goods::GoodsRun() {
	if (rand() % 100 == 1) setX(getX() + speed_x);
	else setX(getX() - speed_x);
	setY(getY() + speed_y);

	if (isOutWindow()) dead = true;
}

void Goods::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());

		TransparentBlt(hdc, getX(), getY(), getWidth(), getHeight(), hdcsrc, 0, 0, getWidth(), getHeight(), RGB(255, 255, 255));
		DeleteDC(hdcsrc);
	}
}