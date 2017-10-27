#pragma once
#ifndef __HEALTH_H__
#define __HEALTH_H__

#include "GameObject.h"

class RoleHealth : public GameObject {
	int hp;
public:
	RoleHealth(HBITMAP hbmp);
	~RoleHealth() {};

	void setHP(int hp) { this->hp = hp; };
	int getHP() { return hp; };

	void drawMe(HDC hdc) override;
};

#endif // !__HEALTH_H__
