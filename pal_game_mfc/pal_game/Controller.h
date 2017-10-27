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
	HWND m_hWnd;				// ���洰�ھ��
	HINSTANCE m_hInst;			// �������ʵ��
	Images *m_pImages;			// ������ԴͼƬ���
	BackGround *m_pBackGround;	// ��Ϸ����-����
	Role *m_pRole;				// ��Ϸ����-Role
	RoleHealth *m_pRoleHealth;	// ��Ϸ����-Role HP
	RoleLife *m_pRoleLife;		// ��Ϸ����-Role������

	int  state;
	/* ��Ϸ״̬ -1:��Ϸδ��ʼ 0:��ͣ 1:���� 2:���� 3:Hero���� */
	bool isGoingUp, isGoingDown, isGoingLeft, isGoingRight;
	bool isFire;
	int totScore;
	int RoleCurrentDamage;

	void RoleRun();

public:
	Controller(HWND hwnd);
	~Controller() {};

	/* �Ƿ�鿴˵����� */
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
	void RenderScene();		//��Ⱦ����

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
