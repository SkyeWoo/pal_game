#pragma once
#ifndef __GOODS_H__
#define __GOODS_H__

#include "GameObject.h"

class Goods : public GameObject {
	/* ���߱�ȡ�û��ߵ���߽����� */
	bool dead;
	/* 0~4-buff 5~9-ҩƷ 10~12-��Ь 13~15-ŮЬ 16~18-�з��� 19~21-Ů����
	 * 22~23-������ 24~25-������ 26~27-������ 28~29-������ */
	/* buff: ���Ч�� Ь: speed ����: health ҩƷ: hp ����: damage */
	int type;
	float speed_x, speed_y;

public:
	Goods(HBITMAP hbmp, int type);
	~Goods() {};

	int getType() { return type; };
	bool isDead() { return dead; };
	void setDead(bool dead) { this->dead = dead; };

	void GoodsRun();

	virtual void drawMe(HDC hdc) override;
};

#endif // !__GOODS_H__