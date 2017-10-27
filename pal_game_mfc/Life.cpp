#include "Life.h"

RoleLife::RoleLife(HBITMAP hbmp[]) {
	/* 导入多个角色包子图像 */
	BITMAP bmp;
	for (int i = 0; i < ROLENUM; i++) {
		this->hbmp[i] = hbmp[i];
		GetObject(hbmp[i], sizeof(bmp), &bmp);
		this->width[i] = bmp.bmWidth;
		this->height[i] = bmp.bmHeight;
	}

	x = 550; y = 500;
	isVisible = true;
	numOfLife = ROLENUM;
}

void RoleLife::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		for (int i = 0; i <= numOfLife; i++) {
			int key = i + ROLENUM - numOfLife - 1;
			SelectObject(hdcsrc, hbmp[key]);

			TransparentBlt(hdc, x + i * 60, y, width[key], height[key], hdcsrc, 0, 0, width[key], height[key], RGB(255, 255, 255));
		}
		DeleteDC(hdcsrc);
	}
}