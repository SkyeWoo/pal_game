#include "Enemy.h"
#include "Bullet.h"
#include "Explode.h"

Enemy::Enemy(HBITMAP hbmp, Controller *pController, int health, int type) : GameObject(hbmp) {
	this->setX((float)(rand() % 600 + 100));
	this->setY(1);
	this->setDead(false);
	this->speed_x = rand() % 5 - 2;
	this->speed_y = rand() % 2 + 1;
	this->health = health;
	if (this->speed_x == 0 && this->speed_y == 1)
		this->speed_x = 1;
	m_pController = pController;
	this->type = type;
	if (type == 0) {
		/* 小怪 伤害值2 */
		setFireMode(m_pController->getImages()->hImgEnemyBullet[rand() % ENEMYBULLETNUM], 2, rand() % 7);
		score = 50;
	}
	else {
		/* boss 伤害值3~7 */
		setFireMode(m_pController->getImages()->hImgEnemyBullet[rand() % ENEMYBULLETNUM], rand() % 5 + 3, rand() % 7);
		score = 100;
	}
}

void Enemy::Fire() {
	if (type == 0)
		m_pController->m_pEnemyBulletList->push_back(Bullet(getX() + getWidth() / 2, getY() + getHeight(), hbmpOfFire, damage, (BulletDirection)(rand() % 7 + 7)));
	else
		m_pController->m_pEnemyBulletList->push_back(Bullet(getX() + getWidth() / 2, getY() + getHeight(), hbmpOfFire, damage, (BulletDirection)(BulletType + 7)));
}

void Enemy::setFireMode(HBITMAP hbmpOfFire, int damage, int type) {
	this->hbmpOfFire = hbmpOfFire;
	this->damage = damage;
	this->BulletType = type;
}

void Enemy::EnemyRun() {
	if (type == 0) {
		if (rand() % 100 == 1)
			this->setX(this->getX() + speed_x);
		else
			this->setX(this->getX() - speed_x);
		setY(getY() + speed_y);

		if (isOutWindow()) {
			/* 超出界面范围的怪无效 分值为0 死亡不计分 */
			score = 0; setDead(true);
		}

		/* enemy进攻 */
		if (rand() % 100 > 98) Fire();
	}

	else {
		if (rand() % 100 == 1) speed_x = -speed_x;
		setX(getX() + speed_x);
		setY(getY() + speed_y);
		if (getX() < 0) setX(1);
		if (getX() > 800 - getWidth()) setX(800 - getWidth());
		if (getY() > 50) setY(50);
		/* boss有更大的几率进攻 */
		if (rand() % 100 > 96) Fire();
	}
}

void Enemy::beHit(Role *role) {
	/* 遍历role的子弹链表 */
	for (auto &i : *(role->m_pRoleBulletList)) {
		if (i.isCollision(this)) {
			/* 子弹射中enemy 子弹自身消亡 enemy血量减少 */
			addHealth(-i.getDamage());
			i.setDead(true);
		}
	}
}

void Enemy::addHealth(int health) {
	this->health += health;
	if (this->health <= 0) {
		this->dead = true;

		/* enemy死亡 role相应地可获取一些物资 */
		/*switch(this->type) {
		case 1:
			if (rand() % 100 > 49)
				m_pController->addGoods(1);
			break;
		case 2:
			if (rand() % 100 > 49)
				m_pController->addGoods(2);
			break;
		case 3:
			if (rand() % 100 > 49)
				m_pController->addGoods(3);
			break;
		case 4:
			if (rand() % 100 > 49)
				m_pController->addGoods(4);
		}*/
		m_pController->m_pExplodeList->push_back(Explode(m_pController->getImages()->hImgExplode, getX(), getY()));
	}
}

void Enemy::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());

		TransparentBlt(hdc, (int)getX(), (int)getY(), (int)getWidth(), (int)getHeight(), hdcsrc, 0, 0, (int)getWidth(), (int)getHeight(), RGB(255, 255, 255));
		DeleteDC(hdcsrc);
	}
}