#pragma once
#ifndef __Bullet_H__
#define __Bullet_H__

#include "GameObject.h"

class Bullet : public GameObject {
	int damage;
	int speed;
	bool dead;			/* bullet是否已经被使用 */
	enum BulletDirection bulletDir;

public:
	Bullet(float x, float y, HBITMAP hbmp, int damage, enum BulletDirection dir, int speed = 3);
	virtual ~Bullet() {};
	int getDamage() { return damage; };
	bool isDead() { return dead; };
	void setDead(bool dead) { this->dead = dead; };
	void BulletRun();
	virtual void drawMe(HDC hdc) override;
};

#endif