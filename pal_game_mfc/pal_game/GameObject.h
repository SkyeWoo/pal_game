#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include <windows.h>
#include "Images.h"

class GameObject {
	float x, y, height, width;		// ��������, �߶�, ��;
	bool isVisible;					// �Ƿ�ɼ�
	HBITMAP hbmp;					// λͼ���

public:
	GameObject() {};				// Ĭ�Ϲ��캯��
	GameObject(HBITMAP hbmp);		// ���캯��
	virtual ~GameObject() {};

	float getX() { return x; };
	float getY() { return y; };
	float getHeight() { return height; };
	float getWidth() { return width; };
	bool getVisible() { return isVisible; };
	HBITMAP getHBitMap() { return hbmp; };

	void setX(float x) { this->x = x; };
	void setY(float y) { this->y = y; };
	void setHeight(float height) { this->height = height; };
	void setWidth(float width) { this->width = width; };
	void setVisible(bool visible) { this->isVisible = visible; };
	void setHBitMap(HBITMAP hbmp) { this->hbmp = hbmp; };

	bool isCollision(GameObject *gobj);
	bool isOutWindow();
	virtual void drawMe(HDC hdc) = 0;	// ���麯��

};
#endif // !__GAMEOBJECT_H__
