#include "Bullet.h"
#include "common.h"

Bullet::Bullet(float x, float y, HBITMAP hbmp, int damage, enum BulletDirection dir, int speed) : GameObject(hbmp) {
	this->setX(x - this->getWidth() / 2);
	this->setY(y - this->getHeight() / 2);
	this->damage = damage;
	this->dead = false;
	this->speed = speed;
	this->bulletDir = dir;
}

void Bullet::BulletRun() {
	if (bulletDir == BulletDirection::D)
		setY(getY() + speed);
	else if (bulletDir == BulletDirection::U)
		setY(getY() - speed);
	else if (bulletDir == BulletDirection::L)
		setX(getX() - speed);
	else if (bulletDir == BulletDirection::R)
		setX(getX() + speed);
	else if (bulletDir == BulletDirection::LD) {
		setY(getY() + speed);
		setX(getX() - speed);
	}
	else if (bulletDir == BulletDirection::LU) {
		setY(getY() - speed);
		setX(getX() - speed);
	}
	else if (bulletDir == BulletDirection::RD) {
		setY(getY() + speed);
		setX(getX() + speed);
	}
	else if (bulletDir == BulletDirection::RU) {
		setY(getY() - speed);
		setX(getX() + speed);
	}
	else if (bulletDir == BulletDirection::LDD) {
		setY(getY() + 2 * speed);
		setX(getX() - speed);
	}
	else if (bulletDir == BulletDirection::LLD) {
		setY(getY() + speed);
		setX(getX() - 2 * speed);
	}
	else if (bulletDir == BulletDirection::LLU) {
		setY(getY() - speed);
		setX(getX() - 2 * speed);
	}
	else if (bulletDir == BulletDirection::LUU) {
		setY(getY() - 2 * speed);
		setX(getX() - speed);
	}
	else if (bulletDir == BulletDirection::RDD) {
		setY(getY() + 2 * speed);
		setX(getX() + speed);
	}
	else if (bulletDir == BulletDirection::RRD) {
		setY(getY() + speed);
		setX(getX() + 2 * speed);
	}
	else if (bulletDir == BulletDirection::RRU) {
		setY(getY() - speed);
		setX(getX() + 2 * speed);
	}
	else if (bulletDir == BulletDirection::RUU) {
		setY(getY() - 2 * speed);
		setX(getX() + speed);
	}

	if (isOutWindow() == true) setDead(true);
}

void Bullet::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());

		TransparentBlt(hdc, (int)getX(), (int)getY(), (int)getWidth(), (int)getHeight(), hdcsrc, 0, 0, (int)getWidth(), (int)getHeight(), RGB(255, 255, 255));
		DeleteDC(hdcsrc);
	}
}