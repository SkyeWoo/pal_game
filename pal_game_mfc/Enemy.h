#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "common.h"
#include "GameObject.h"
#include "Controller.h"
#include "Role.h"

class Controller;
class Enemy : public GameObject {
	int speed_x, speed_y;
	int score;
	/* 1:boss1  2:boss2 3:boss3 4:boss4 0:小怪 */
	int type;
	int health;
	int damage;
	int BulletType;
	bool dead;
	HBITMAP hbmpOfFire;
	Controller *m_pController;

public:
	Enemy(HBITMAP hbmp, Controller *pController, int health, int type = 0);
	virtual ~Enemy() {};
	virtual void Fire();
	virtual void drawMe(HDC hdc) override;
	bool isDead() { return dead; };
	void setDead(bool dead) { this->dead = dead; };
	int getScore() { return score; };
	int getDamage() { return damage; };
	void addHealth(int health);
	void setFireMode(HBITMAP hbmpOfFire, int damage, int BulletType);
	void EnemyRun();
	/* 判断是否被击中 */
	void beHit(Role *role);
};

#endif // !__ENEMY_H__
