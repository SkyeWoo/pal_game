#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include "GameObject.h"

class BackGround : public GameObject {
public:
	BackGround(HBITMAP hbmp) : GameObject(hbmp) {};
	virtual ~BackGround() {};
	void drawMe(HDC hdc) override;
};

#endif // !__BACKGROUND_H__
