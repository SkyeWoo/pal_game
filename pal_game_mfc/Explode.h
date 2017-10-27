#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "GameObject.h"

const int EXPLODENUM = 15;

class Explode : public GameObject {
	/* ��ըͼ�� */
	HBITMAP explode[EXPLODENUM];
	/* stateά����ը�̶� 0~EXPLODENUM-1 */
	int state;
	/* �Ƿ��Ѿ���ɱ�ը */
	bool dead;

public:
	Explode(HBITMAP *hbmp, float x, float y, int num = EXPLODENUM);
	~Explode() {};
	
	bool isDead() { return dead; };
	/* ����state���ű�ըͼ�� */
	HBITMAP getExplodeHBitMap();

	virtual void drawMe(HDC HDC) override;
};

#endif