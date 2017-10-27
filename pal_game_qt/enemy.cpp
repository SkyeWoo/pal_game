#include "enemy.h"

#include "Bullet.h"

Enemy::Enemy(QPixmap pixmap, QGraphicsScene *scene, Controller *pController, int health, int type)
    : GameObject(pixmap, scene) {
    this->setX((float)(rand() % 600 + 100));
    this->setY(1);
    this->setDead(false);
    this->speed_x = rand() % 5 - 2;
    /* 小怪速度较快 */
    if (type == 0) this->speed_y = rand() % 5 + 1;
    else this->speed_y = rand() % 2 + 1;
    this->health = health;
    m_pController = pController;
    this->scene = scene;
    this->type = type;
//    this->m_bullet = m_pController->getImages()->hImgEnemyBullet;
    if (type == 0) {
        /* 小怪 伤害值2 */
//		setFireMode(m_pController->getImages()->hImgEnemyBullet[rand() % ENEMYBULLETNUM], 2, rand() % 7);
        setFireMode(m_pController->getImages()->hImgEnemyBullet, 2, rand() % 7);
        score = 50;
    }
    else {
        /* boss 伤害值3~7 */
//		setFireMode(m_pController->getImages()->hImgEnemyBullet[rand() % ENEMYBULLETNUM], rand() % 5 + 3, rand() % 7);
        setFireMode(m_pController->getImages()->hImgEnemyBullet, rand() % 5 + 3, rand() % 7);
        score = 100;
    }
}

void Enemy::Fire() {
    if (type == 0)
//        m_pController->m_pEnemyBulletList->append(new Bullet(this->x() + getWidth() / 4, this->y() + getHeight() / 2, m_bullet, scene, damage, (BulletDirection)(rand() % 7 + 7)));
        m_pController->m_pEnemyBulletList->append(new Bullet(this->x() + getWidth() / 4, this->y() + getHeight() / 2, m_bullet, this->scene, damage, BulletDirection::D, this->speed_y + 1));
    else
//        m_pController->m_pEnemyBulletList->append(new Bullet(this->x() + getWidth() / 4, this->y() + getHeight() / 2, m_bullet, scene, damage, (BulletDirection)(BulletType + 7)));
        m_pController->m_pEnemyBulletList->append(new Bullet(this->x() + getWidth() / 4, this->y() + getHeight() / 2, m_bullet, this->scene, damage, BulletDirection::D));
}

void Enemy::setFireMode(QPixmap pixmap, int damage, int type) {
    this->m_bullet = pixmap;
    this->damage = damage;
    this->BulletType = type;
}

void Enemy::EnemyRun() {
    if (type == 0) {
        if (rand() % 100 == 1)
            this->setX(this->x() + speed_x);
        else
            this->setX(this->x() - speed_x);
        setY(this->y() + speed_y);

        if (isOutWindow()) {
            /* 超出界面范围的怪无效 分值为0 死亡不计分 */
            score = 0; setDead(true);
        }

        /* enemy进攻 */
        if (rand() % 100 > 98) Fire();
    }

    else {
        /* boss会转变下降轨迹 */
        if (rand() % 100 == 1) speed_x = -speed_x;
        this->setX(this->x() + speed_x);
        this->setY(this->y() + speed_y);
        if (this->x() < 0) setX(1);
        if (this->x() > 800 - getWidth()) setX(800 - getWidth());
//        if (this->y() > 50) setY(50);
        /* boss有更大的几率进攻 */
        if (rand() % 100 > 96) Fire();
    }
}

void Enemy::beHit(Role *role) {
    /* 遍历role的子弹链表 */
    for (auto &i : *(role->m_pRoleBulletList)) {
        if (i->isCollision(this)) {
            /* 子弹射中enemy 子弹自身消亡 enemy血量减少 */
            addHealth(-i->getDamage());
            i->setDead(true);
        }
    }
}

void Enemy::addHealth(int health) {
    this->health += health;
    if (this->health <= 0)
        this->dead = true;
}
