#ifndef __EXPLODE_H__
#define __EXPLODE_H__

#include "GameObject.h"

const int EXPLODENUM = 15;

class Explode : public GameObject {
	/* 爆炸图像 */
	HBITMAP explode[EXPLODENUM];
	/* state维护爆炸程度 0~EXPLODENUM-1 */
	int state;
	/* 是否已经完成爆炸 */
	bool dead;

public:
	Explode(HBITMAP *hbmp, float x, float y, int num = EXPLODENUM);
	~Explode() {};
	
	bool isDead() { return dead; };
	/* 根据state播放爆炸图像 */
	HBITMAP getExplodeHBitMap();

	virtual void drawMe(HDC HDC) override;
};

#endif