#include "GameObject.h"
#include "common.h"

GameObject::GameObject(HBITMAP hbmp) {
	BITMAP bmp;
	this->hbmp = hbmp;
	GetObject(hbmp, sizeof(bmp), &bmp);
	this->x = this->y = 0;
	this->width = bmp.bmWidth;
	this->height = bmp.bmHeight;
	this->setVisible(true);
}

bool GameObject::isCollision(GameObject *gobj) {
	if (gobj == nullptr) return false;

	float h1, h2, w1, w2, r1, r2;
	h1 = this->getHeight();
	h2 = gobj->getHeight();
	w1 = this->getWidth();
	w2 = gobj->getWidth();

	r1 = sqrt(h1 * h1 + w1 * w1) / 2;
	r2 = sqrt(h2 * h2 + w2 * w2) / 2;

	float x1, y1, x2, y2;
	x1 = this->getX() + this->getWidth() / 2;
	x2 = gobj->getX() + gobj->getWidth() / 2;
	y1 = this->getY() + this->getHeight() / 2;
	y2 = gobj->getY() + gobj->getHeight() / 2;

	float dis = sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
	if (dis < r1 + r2) return true;
	else return false;
}

bool GameObject::isOutWindow() {
	if ((this->getX() + this->getWidth() <= 0) || this->getX() >= 800)
		return true;
	if ((this->getY() + this->getHeight() <= 0) || this->getY() >= 600)
		return true;
	return false;
}