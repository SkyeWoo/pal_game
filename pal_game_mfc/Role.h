#pragma once
#ifndef __ROLE_H__
#define __ROLE_H__

#include "GameObject.h"
#include "Bullet.h"
#include "common.h"

class Role : public GameObject {
	/* ������ͼ�� ��ͬ��ɫ�в�ͬ���� */
	HBITMAP hbmpOfFire;
	bool dead;
	/* ��ɫ�˺�ֵ(��ײ�˺�) �����˺�ֵ(�ӵ��˺�) ����ֵ �ٶ� */
	int damage, BulletDamage, health, speed;
	/* ��ɫ�������� ��ֵԽ�󹥻���ΧԽ�� */
	int type;
	/* ��ǰ��ɫ�÷� �÷ֵ�һ���̶�type������ */
	int score;
	/* ��ɫ��ֵ ����keyֵ�ж����ĸ���ɫ */
	int key;

public:
	Role(HBITMAP hbmp, int key);
	~Role();
	void left();
	void right();
	void up();
	void down();
	bool isDead() { return dead; };

	int getKey() { return key; };
	int getScore() { return score; };
	int getType() { return type; };
	int getHealth() { return health; };
	int getDamage() { return damage; };
	int getSpeed() { return speed; };

	void addHealth(int health);
	void setHealth(int health);
	void setKey(int key) { this->key = key; };
	void setScore(int score) { this->score = score; };
	void setType(int type) { this->type = type; };
	void setDamage(int damage) { this->damage = damage; };
	void setSpeed(int speed) { this->speed = speed; };

	void Reset();
	void Fire();
	void changeType();
	void setFireMode(HBITMAP hbmp, int damage, int type);
	void Role::drawAllRoleBullet(HDC hdc);		// ��Ⱦ����RoleBullet
	void allRoleBulletRun();
	void drawMe(HDC hdc) override;

	std::list<Bullet>* m_pRoleBulletList;		// Role�ӵ�����
};
#endif // !__ROLE_H__
