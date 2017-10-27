#pragma once
#ifndef __ROLE_H__
#define __ROLE_H__

#include "GameObject.h"
#include "Bullet.h"
#include "common.h"

class Role : public GameObject {
	/* 武器的图像 不同角色有不同武器 */
	HBITMAP hbmpOfFire;
	bool dead;
	/* 角色伤害值(相撞伤害) 武器伤害值(子弹伤害) 生命值 速度 */
	int damage, BulletDamage, health, speed;
	/* 角色攻击类型 数值越大攻击范围越大 */
	int type;
	/* 当前角色得分 得分到一定程度type会升级 */
	int score;
	/* 角色键值 根据key值判断是哪个角色 */
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
	void Role::drawAllRoleBullet(HDC hdc);		// 渲染所有RoleBullet
	void allRoleBulletRun();
	void drawMe(HDC hdc) override;

	std::list<Bullet>* m_pRoleBulletList;		// Role子弹链表
};
#endif // !__ROLE_H__
