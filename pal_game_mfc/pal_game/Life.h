#pragma once
#ifndef __LIFE_H__
#define __LIFE_H__

#include "GameObject.h"
#include "common.h"

class RoleLife {
	/* 存储不同角色的包子图像 */
	HBITMAP hbmp[ROLENUM];
	float height[ROLENUM], width[ROLENUM];
	/* life面板的坐标 */
	float x, y;
	bool isVisible;
	int numOfLife;

public:
	RoleLife(HBITMAP hbmp[]);
	~RoleLife() {};

	void setVisible(bool visible) { this->isVisible = visible; };
	bool getVisible() { return isVisible; };
	int getLifeNum() { return numOfLife; };
	void setLifeNum(int numOfLife) { this->numOfLife = numOfLife; };

	void drawMe(HDC hdc);
};

#endif // !__LIFE_H__
