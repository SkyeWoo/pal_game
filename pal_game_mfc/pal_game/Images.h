#pragma once
#ifndef __IMAGES_H__
#define __IMAGES_H__

#include <Windows.h>
#include "common.h"

class Images
{
public:
	HBITMAP hImgMap;
	HBITMAP hImgStartBg;
	HBITMAP hImgContinue;
	HBITMAP hImgGameOver;
	HBITMAP hImgScore;
	HBITMAP hImgNum[10];
	HBITMAP hImgRole[ROLENUM];
	HBITMAP hImgBullet[ROLENUM];
	HBITMAP hImgEnemy[ENEMYNUM];
	HBITMAP hImgEnemyBullet[ENEMYBULLETNUM];
	HBITMAP hImgHealth;
	HBITMAP hImgLife[ROLENUM];
	HBITMAP hImgExplode[15];
	HBITMAP hImgGoods[GOODSNUM];
	HBITMAP hImgIntroduction[11];
	HBITMAP hImgPass[ROLENUM];

	Images(HINSTANCE hInst);
	~Images() {};
};

#endif // !__IMAGE_H__

