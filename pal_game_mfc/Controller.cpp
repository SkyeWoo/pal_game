#include "Controller.h"

Controller::Controller(HWND hwnd) {
	m_hWnd = hwnd;
	m_hInst = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
	m_pImages = new Images(m_hInst);
	m_pBackGround = new BackGround(m_pImages->hImgMap);

	/* 角色初始子弹伤害值为2 */
	RoleCurrentDamage = 2;
	flag_intr = -1;
	flag_win = false;

	/* 创建角色 默认为姜云凡 */
	m_pRole = new Role(m_pImages->hImgRole[0], 0);
	m_pRoleHealth = new RoleHealth(m_pImages->hImgHealth);
	m_pRoleLife = new RoleLife(m_pImages->hImgLife);
	/* 角色初始化 */
	ResetRole();
	m_pEnemyBulletList = new list<Bullet>();
	m_pEnemyList = new list<Enemy>();
	m_pExplodeList = new list<Explode>();
	m_pGoodsList = new list<Goods>();
	this->totScore = 0;
	/* 游戏还没开始 */
	this->state = -1;
}

void Controller::GameStart() {
	if (state == -1) state = 1;
	else if (state == 3) ResetRole();
}

void Controller::GamePause() {
	if (state == 1) state = 0;
	else if (state == 0) state = 1;
}

void Controller::GameEnd() {
	state = 2;
}

void Controller::GameWaitReset() {
	state = 3;
}

void Controller::ResetRole() {
	if (m_pRoleLife->getLifeNum() > 0) {
		m_pRole->Reset();

		m_pRoleHealth->setHP(m_pRole->getHealth());					// 获取生命值
		m_pRoleLife->setLifeNum(m_pRoleLife->getLifeNum() - 1);		// 初始设置生命数

		/* 更换角色 */
		BITMAP bmp;
		int key = ROLENUM - 1 - m_pRoleLife->getLifeNum();
		m_pRole->setHBitMap(m_pImages->hImgRole[key]);
		m_pRole->setKey(key);
		GetObject(m_pRole->getHBitMap(), sizeof(bmp), &bmp);
		m_pRole->setWidth(bmp.bmWidth);
		m_pRole->setHeight(bmp.bmHeight);
		m_pRole->setFireMode(m_pImages->hImgBullet[key], RoleCurrentDamage, 0);

		/* 游戏恢复运行 */
		this->state = 1;
	}
}

void Controller::setRoleFireMode(int type, int damage) {
	if (m_pRole != nullptr)
		m_pRole->setFireMode(m_pImages->hImgBullet[m_pRole->getKey()], damage, type);
}

void Controller::allRun() {
	if (!m_pRole->isDead()) RoleRun();
	/* 所有角色发出的子弹移动 */
	m_pRole->allRoleBulletRun();
	allEnemyRun();
	/* 所有enemy发出的子弹移动 */
	allEnemyBulletRun();
	allGoodsRun();
}

/* 控制角色移动 */
void Controller::RoleRun() {
	if (m_pRole == nullptr) return;

	if (isGoingUp) m_pRole->up();
	if (isGoingDown) m_pRole->down();
	if (isGoingLeft) m_pRole->left();
	if (isGoingRight) m_pRole->right();

	if (isFire) m_pRole->Fire();
}

void Controller::allEnemyBulletRun() {
	for (auto &i : *m_pEnemyBulletList) {
		i.BulletRun();

		/* Role is hit */
		if (!m_pRole->isDead() && i.isCollision(m_pRole)) {
			m_pRole->addHealth(-i.getDamage());
			/* Role is dead, explode */
			if (m_pRole->isDead()) {
				m_pExplodeList->push_back(Explode(this->getImages()->hImgExplode, m_pRole->getX(), m_pRole->getY()));
				m_pRole->setVisible(false);
				if (m_pRoleLife->getLifeNum() > 0)
					GameWaitReset();
				else GameEnd();
			}

			m_pRoleHealth->setHP(m_pRole->getHealth());
			i.setDead(true);		/* 子弹用过消亡 */
		}
	}

	for (std::list<Bullet>::iterator i = m_pEnemyBulletList->begin(); i != m_pEnemyBulletList->end(); )
		if (i->isDead())
			i = m_pEnemyBulletList->erase(i);
		else i++;
}

void Controller::addEnemy() {
	static int i = 0;
	static int count = 1;
	i++;
	if (i == 6000) {
		count++; i = 0;
	}
	if (m_pEnemyList->size() < 10 && rand() % 100 > 95)
		/* enemy的生命值会随count递增 时间越长 enemy生命值越高 */
		m_pEnemyList->push_back(Enemy(m_pImages->hImgEnemy[rand() % ENEMYNUM], this, count * 20));
}

void Controller::allEnemyRun() {
	addEnemy();

	for (auto &i : *m_pEnemyList) {
		i.EnemyRun();
		/* 判断enemy是否被role击中 */
		i.beHit(m_pRole);

		/* enemy与role相撞 */
		if (!m_pRole->isDead() && i.isCollision(m_pRole)) {
			/* role血量减少 */
			//m_pRole->addHealth(-5);
			m_pRole->addHealth(-i.getDamage());

			/* 如果role死亡 爆炸 */
			if (m_pRole->isDead()) {
				m_pExplodeList->push_back(Explode(getImages()->hImgExplode, m_pRole->getX(), m_pRole->getY()));
				m_pRole->setVisible(false);
				if (m_pRoleLife->getLifeNum() > 0) GameWaitReset();
				else GameEnd();
			}
			m_pRoleHealth->setHP(m_pRole->getHealth());

			/* enemy血量减少 */
			//i.addHealth(-100);
			i.addHealth(-m_pRole->getDamage());
		}
	}

	for (std::list<Enemy>::iterator i = m_pEnemyList->begin(); i != m_pEnemyList->end();) {
		if (i->isDead()) {
			totScore += i->getScore();		/* 得到enemy相应分值 */
			if (totScore >= WINSCORE) {
				state = 2; flag_win = true;
			}
			m_pRole->setScore(i->getScore());
			m_pRole->changeType();
			i = m_pEnemyList->erase(i);		/* 消除该enemy对象 */
		}
		else i++;
	}
}

void Controller::addGoods() {
	if (m_pGoodsList->size() < 30 && rand() % 1000 > 990) {
		int type = rand() % 30;
		m_pGoodsList->push_back(Goods(m_pImages->hImgGoods[type], type));
	}
}

void Controller::allGoodsRun() {
	addGoods();

	for (auto &i : *m_pGoodsList) {
		i.GoodsRun();

		/* role得到物品 */
		if (!m_pRole->isDead() && i.isCollision(m_pRole)) {
			/* 物品效果 */
			if (i.getType() < 5) {
				/* random buff */
				int temp = rand() % 4;
				switch (temp) {
				case 0: // hp
					m_pRoleHealth->setHP(m_pRoleHealth->getHP() + 10);
					break;
				case 1: // speed
					m_pRole->setSpeed(m_pRole->getSpeed() + 1);
					break;
				case 2: // health(满血)
					if (m_pRole->getHealth() != HEALTH[m_pRole->getKey()]) {
						m_pRole->setHealth(HEALTH[m_pRole->getKey()]);
						m_pRoleHealth->setHP(m_pRole->getHealth());
					}
					break;
				case 3: // damage
					RoleCurrentDamage += 1;
					break;
				}
			}
			else if (i.getType() < 10)	// hp
				m_pRoleHealth->setHP(m_pRoleHealth->getHP() + 10);
			// speed
			else if (i.getType() < 13) {
				if (m_pRole->getKey() < 2)	// male
					m_pRole->setSpeed(m_pRole->getSpeed() + 1);
			}
			else if (i.getType() < 16) {
				if (m_pRole->getKey() >= 2)
					m_pRole->setSpeed(m_pRole->getSpeed() + 1);
			}
			// health(满血)
			else if (i.getType() < 19) {
				if (m_pRole->getKey() < 2)
					if (m_pRole->getHealth() != HEALTH[m_pRole->getKey()]) {
						m_pRole->setHealth(HEALTH[m_pRole->getKey()]);
						m_pRoleHealth->setHP(m_pRole->getHealth());
					}
			}
			else if (i.getType() < 22) {
				if (m_pRole->getKey() >= 2)
					if (m_pRole->getHealth() != HEALTH[m_pRole->getKey()]) {
						m_pRole->setHealth(HEALTH[m_pRole->getKey()]);
						m_pRoleHealth->setHP(m_pRole->getHealth());
					}
			}
			// damage
			else if (i.getType() < 24) {
				if (m_pRole->getKey() == 0) // 姜
					RoleCurrentDamage += 1;
			}
			else if (i.getType() < 26) {
				if (m_pRole->getKey() == 1) // 龙
					RoleCurrentDamage += 1;
			}
			else if (i.getType() < 28) {
				if (m_pRole->getKey() == 2) // 蛮
					RoleCurrentDamage += 1;
			}
			else {
				if (m_pRole->getKey() == 3) // 唐
					RoleCurrentDamage += 1;
			}

			i.setDead(true);
		}
	}

	for (std::list<Goods>::iterator i = m_pGoodsList->begin(); i != m_pGoodsList->end();) {
		if (i->isDead() == true) i = m_pGoodsList->erase(i);
		else i++;
	}
}

void Controller::drawAllEnemy(HDC hdc) {
	for (auto &i : *m_pEnemyList)
		i.drawMe(hdc);
}

void Controller::drawAllEnemyBullet(HDC hdc) {
	for (auto &i : *m_pEnemyBulletList)
		i.drawMe(hdc);
}

void Controller::drawAllExplode(HDC hdc) {
	for (auto &i : *m_pExplodeList)
		i.drawMe(hdc);
	for (std::list<Explode>::iterator i = m_pExplodeList->begin(); i != m_pExplodeList->end();)
		if (i->isDead())
			i = m_pExplodeList->erase(i);
		else i++;
}

void Controller::drawAllGoods(HDC hdc) {
	for (auto &i : *m_pGoodsList)
		i.drawMe(hdc);

	for (std::list<Goods>::iterator i = m_pGoodsList->begin(); i != m_pGoodsList->end();) {
		if (i->isDead())
			i = m_pGoodsList->erase(i);
		else i++;
	}
}

void Controller::RenderScene() {
	HDC hdc = GetDC(m_hWnd);
	HDC hdcBuffer = CreateCompatibleDC(hdc);
	HBITMAP hBitmapBuf = CreateCompatibleBitmap(hdc, 800, 600);
	SelectObject(hdcBuffer, hBitmapBuf);

	if (state == -1) {
		/* 进入游戏界面 */
		drawStartBackGround(hdcBuffer);
		if (flag_intr != -1)
			drawIntroduction(hdcBuffer, flag_intr);
	}
	else {
		if (state != 0) allRun();

		m_pBackGround->drawMe(hdcBuffer);
		m_pRoleHealth->drawMe(hdcBuffer);
		m_pRoleLife->drawMe(hdcBuffer);
		m_pRole->drawMe(hdcBuffer);

		/* 绘制属性面板 */
		//drawAttribute(hdcBuffer);
		drawScore(hdcBuffer);
		drawAllEnemy(hdcBuffer);
		drawAllEnemyBullet(hdcBuffer);
		drawAllExplode(hdcBuffer);
		drawAllGoods(hdcBuffer);

		if (state == 2) {
			if (flag_win == false) drawGameOver(hdcBuffer);
			else drawGamePass(hdcBuffer, m_pRole->getKey());
		}
		else if (state == 3) drawGameContinue(hdcBuffer);
	}

	BitBlt(hdc, 0, 0, 800, 600, hdcBuffer, 0, 0, SRCCOPY);

	DeleteObject(hBitmapBuf);
	DeleteDC(hdcBuffer);
	ReleaseDC(m_hWnd, hdc);
}

void Controller::drawStartBackGround(HDC hdc) {
	HBITMAP tmpHbmp = m_pImages->hImgStartBg;
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	BitBlt(hdc, 0, 0, 800, 600, hdcsrc, 0, 0, SRCCOPY);
	DeleteDC(hdcsrc);
}

void Controller::drawGameContinue(HDC hdc) {
	HBITMAP tmpHbmp = m_pImages->hImgContinue;
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	TransparentBlt(hdc, (800 - bmp.bmWidth) / 2, (600 - bmp.bmHeight) / 2, bmp.bmWidth, bmp.bmHeight, hdcsrc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
	DeleteDC(hdcsrc);
}

void Controller::drawIntroduction(HDC hdc, int page) {
	HBITMAP tmpHbmp = m_pImages->hImgIntroduction[page];
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	BitBlt(hdc, (800 - bmp.bmWidth) / 2, (600 - bmp.bmHeight) / 2, bmp.bmWidth, bmp.bmHeight, hdcsrc, 0, 0, SRCCOPY);
	DeleteDC(hdcsrc);
}

void Controller::drawGamePass(HDC hdc, int key) {
	HBITMAP tmpHbmp = m_pImages->hImgPass[key];
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	BitBlt(hdc, 0, 0, 800, 600, hdcsrc, 0, 0, SRCCOPY);
	DeleteDC(hdcsrc);
}

void Controller::drawGameOver(HDC hdc) {
	HBITMAP tmpHbmp = m_pImages->hImgGameOver;
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	//BitBlt(hdc, 0, 0, 800, 600, hdcsrc, 0, 0, SRCCOPY);
	TransparentBlt(hdc, 0, 0, 800, 600, hdcsrc, 0, 0, 800, 600, RGB(255, 255, 255));
	DeleteDC(hdcsrc);
}

void Controller::drawScore(HDC hdc) {
	HBITMAP tmpHbmp = m_pImages->hImgScore;
	HDC hdcsrc = CreateCompatibleDC(hdc);
	SelectObject(hdcsrc, tmpHbmp);
	BITMAP bmp;
	GetObject(tmpHbmp, sizeof(bmp), &bmp);
	TransparentBlt(hdc, 5, 5, bmp.bmWidth, bmp.bmHeight, hdcsrc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(0, 0, 255));

	int num[5] = { 0 };
	num[4] = totScore % 10;
	num[3] = (totScore / 10) % 10;
	num[2] = (totScore / 100) % 10;
	num[1] = (totScore / 1000) % 10;
	num[0] = (totScore / 10000) % 10;

	for (int i = 0; i < 5; i++) {
		tmpHbmp = m_pImages->hImgNum[num[i]];
		SelectObject(hdcsrc, tmpHbmp);
		GetObject(tmpHbmp, sizeof(bmp), &bmp);
		TransparentBlt(hdc, 65 + 12 * i, 25, bmp.bmWidth, bmp.bmHeight, hdcsrc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));
	}

	DeleteDC(hdcsrc);
}

//void Controller::drawAttribute(HDC hdc) {
//}