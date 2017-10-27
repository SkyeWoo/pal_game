#include "Explode.h"
//#include <thread>

Explode::Explode(HBITMAP *hbmp, float x, float y, int num) : GameObject(hbmp[0]) {
	/* 加载爆炸图标 */
	for (int i = 0; i < num; i++) explode[i] = hbmp[i];
	state = 0;
	setX(x); setY(y);
	dead = false;
}

HBITMAP Explode::getExplodeHBitMap() {
	BITMAP bmp;
	HBITMAP hbmp;
	if (state >= 0 && state < EXPLODENUM) hbmp = explode[state];
	else hbmp = explode[EXPLODENUM - 1];
	GetObject(hbmp, sizeof(bmp), &bmp);
	setWidth(bmp.bmWidth);
	setHeight(bmp.bmHeight);
	return hbmp;
}

void Explode::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getExplodeHBitMap());

		TransparentBlt(hdc, getX(), getY(), getWidth(), getHeight(), hdcsrc, 0, 0, getWidth(), getHeight(), RGB(255, 255, 255));
		DeleteDC(hdcsrc);
	}

	/* 多张静态图模拟动态图显示 */
	if (++state >= EXPLODENUM - 1) {
		dead == true; setVisible(false);
	}
}