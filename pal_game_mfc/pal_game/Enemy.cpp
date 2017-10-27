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
		/* С�� �˺�ֵ2 */
		setFireMode(m_pController->getImages()->hImgEnemyBullet[rand() % ENEMYBULLETNUM], 2, rand() % 7);
		score = 50;
	}
	else {
		/* boss �˺�ֵ3~7 */
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
			/* �������淶Χ�Ĺ���Ч ��ֵΪ0 �������Ʒ� */
			score = 0; setDead(true);
		}

		/* enemy���� */
		if (rand() % 100 > 98) Fire();
	}

	else {
		if (rand() % 100 == 1) speed_x = -speed_x;
		setX(getX() + speed_x);
		setY(getY() + speed_y);
		if (getX() < 0) setX(1);
		if (getX() > 800 - getWidth()) setX(800 - getWidth());
		if (getY() > 50) setY(50);
		/* boss�и���ļ��ʽ��� */
		if (rand() % 100 > 96) Fire();
	}
}

void Enemy::beHit(Role *role) {
	/* ����role���ӵ����� */
	for (auto &i : *(role->m_pRoleBulletList)) {
		if (i.isCollision(this)) {
			/* �ӵ�����enemy �ӵ��������� enemyѪ������ */
			addHealth(-i.getDamage());
			i.setDead(true);
		}
	}
}

void Enemy::addHealth(int health) {
	this->health += health;
	if (this->health <= 0) {
		this->dead = true;

		/* enemy���� role��Ӧ�ؿɻ�ȡһЩ���� */
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