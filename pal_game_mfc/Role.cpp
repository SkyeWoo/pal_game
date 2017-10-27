#include "common.h"
#include "Role.h"

Role::Role(HBITMAP hbmp, int key) : GameObject(hbmp) {
	this->key = key;
	this->damage = DAMAGE[key];
	this->health = HEALTH[key];
	this->speed = SPEED[key];
	this->BulletDamage = BULLETDAMAGE[key];
	this->score = 0;
	this->dead = false;

	setX(800 - getWidth() / 2);
	setY(500);
	m_pRoleBulletList = new list<Bullet>();
}

Role::~Role() {
	if (m_pRoleBulletList != nullptr)
		delete m_pRoleBulletList;
}

void Role::left() {
	float x = getX() - speed;
	if (x <= 0) setX(0);
	else setX(x);
}

void Role::right() {
	float x = getX() + speed;
	if (x >= (800 - getWidth()))
		setX(800 - getWidth());
	else setX(x);
}

void Role::up() {
	float y = getY() - speed;
	if (y <= 0) setY(0);
	else setY(y);
}

void Role::down() {
	float y = getY() + speed;
	if (y >= (600 - getHeight()))
		setY(600 - getHeight());
	else setY(y);
}

void Role::setHealth(int health) {
	if (health >= HEALTH[key]) this->health = HEALTH[key];
	else this->health = health;
}

void Role::addHealth(int health) {
	this->health += health;
	if (this->health <= 0) this->dead = true;
}

void Role::Reset() {
	this->score = this->type = 0;
	this->health = HEALTH[key];
	this->speed = SPEED[key];
	this->damage = DAMAGE[key];
	this->BulletDamage = 2;

	this->dead = false;
	setX((800 - this->getWidth()) / 2);
	setY(500);
	setVisible(true);
}

void Role::setFireMode(HBITMAP hbmp, int damage, int type) {
	this->hbmpOfFire = hbmp;
	this->BulletDamage = damage;
	this->type = type;
}

void Role::changeType() {
	if (type == 3 || score < 1000) return;
	else if (type == 2 && score >= 5000) type = 3;
	else if (type == 1 && score >= 1000) type = 2;
}

void Role::Fire() {
	static int i = 0;
	++i;
	if (i % 5 == 0) {
		if (i % 2 == 0) {
			if (type == 0)
				/* 普通模式 */
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::U, 20));
			else if (type == 1) {
				/* 双发模式 */
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2 - 10, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::U, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2 + 10, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::U, 20));
			}
			else if (type == 2)
			{
				/* 三发模式 */
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::U, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::LU, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::RU, 20));
			}
			else if (type == 3)
			{
				/* 五发模式 */
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::U, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::LLU, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::LU, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::RRU, 20));
				m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage, BulletDirection::RU, 20));
			}
		}

		if (type == 4)
			/* 重击模式 */
			m_pRoleBulletList->push_back(Bullet(this->getX() + this->getWidth() / 2, this->getY(), this->hbmpOfFire, this->BulletDamage * 6, BulletDirection::U, 20));
	}
}

void Role::drawMe(HDC hdc) {
	if (getVisible() == true) {
		HDC hdcsrc = CreateCompatibleDC(hdc);
		SelectObject(hdcsrc, getHBitMap());

		TransparentBlt(hdc, (int)getX(), (int)getY(), (int)getWidth(), (int)getHeight(), hdcsrc, 0, 0, (int)getWidth(), (int)getHeight(), RGB(255, 255, 255));
		DeleteDC(hdcsrc);
	}
	drawAllRoleBullet(hdc);
}

void Role::drawAllRoleBullet(HDC hdc) {
	for (auto &i : *m_pRoleBulletList)
		i.drawMe(hdc);

	for (std::list<Bullet>::iterator i = m_pRoleBulletList->begin(); i != m_pRoleBulletList->end(); ) {
		/* 子弹打中或者到边界 消亡 */
		if (i->isDead() == true)
			i = m_pRoleBulletList->erase(i);
		else i++;
	}
}

void Role::allRoleBulletRun() {
	for (auto &i : *m_pRoleBulletList)
		i.BulletRun();
}

