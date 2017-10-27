#pragma once
#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <windows.h>
#include <list>

#include "Images.h"
#include "BackGround.h"
#include "Role.h"
#include "Health.h"
#include "Life.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Explode.h"
#include "Goods.h"

class Enemy;
class Controller {
	HWND m_hWnd;				// 保存窗口句柄
	HINSTANCE m_hInst;			// 保存程序实例
	Images *m_pImages;			// 所有资源图片句柄
	BackGround *m_pBackGround;	// 游戏物体-背景
	Role *m_pRole;				// 游戏物体-Role
	RoleHealth *m_pRoleHealth;	// 游戏物体-Role HP
	RoleLife *m_pRoleLife;		// 游戏物体-Role生命数

	int  state;
	/* 游戏状态 -1:游戏未开始 0:暂停 1:运行 2:结束 3:Hero死亡 */
	bool isGoingUp, isGoingDown, isGoingLeft, isGoingRight;
	bool isFire;
	int totScore;
	int RoleCurrentDamage;

	void RoleRun();

public:
	Controller(HWND hwnd);
	~Controller() {};

	/* 是否查看说明面板 */
	int flag_intr;
	bool flag_win;

	Images *getImages() { return m_pImages; }
	list<Enemy> *m_pEnemyList;
	list<Bullet> *m_pEnemyBulletList;
	list<Explode> *m_pExplodeList;
	list<Goods> *m_pGoodsList;

	void GameStart();
	void GamePause();
	void GameEnd();
	void GameWaitReset();
	void ResetRole();
	void RenderScene();		//渲染场景

	int getState() { return state; };

	void setGoingUp(bool up) { isGoingUp = up; };
	void setGoingDown(bool down) { isGoingDown = down; };
	void setGoingLeft(bool left) { isGoingLeft = left; };
	void setGoingRight(bool right) { isGoingRight = right; };
	void setRoleFire(bool fire) { isFire = fire; };
	void setRoleFireMode(int type, int damage);

	void addEnemy();
	void addGoods();
	void drawAllEnemy(HDC hdc);
	void drawAllEnemyBullet(HDC hdc);
	void drawAllExplode(HDC hdc);
	void drawAllGoods(HDC hdc);

	void drawStartBackGround(HDC hdc);
	void drawGameContinue(HDC hdc);
	void drawGameOver(HDC hdc);
	void drawScore(HDC hdc);
	//void drawAttribute(HDC hdc);
	void drawIntroduction(HDC hdc, int page);
	void drawGamePass(HDC hdc, int key);

	void allRun();
	void allEnemyBulletRun();
	void allEnemyRun();
	void allGoodsRun();
};

#endif
