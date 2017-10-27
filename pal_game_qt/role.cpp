#include "role.h"

Role::Role(QPixmap pixmap, QGraphicsScene *scene, int key)
    : GameObject(pixmap, scene) {
    this->scene = scene;
    this->key = key;
    this->damage = DAMAGE[key];
    this->protect = PROTECT[key];
    this->health = HEALTH[key];
    this->speed = SPEED[key];
    this->BulletDamage = BULLETDAMAGE[key];
    this->score = 0;
    this->dead = false;
//    this->setPos(scene->width() / 2 - this->getWidth() / 2, 300);
    this->setPos(scene->width() / 2 - this->getWidth() / 2, scene->height() / 2- this->getHeight() / 2);

    m_pRoleBulletList = new QList<Bullet*>();
}

Role::~Role() {
    if (m_pRoleBulletList != nullptr)
        delete m_pRoleBulletList;
}

void Role::left() {
    float x = this->x() - speed;
    if (x <= 0) setX(0);
    else setX(x);
}

void Role::right() {
    float x = this->x() + speed;
    if (x >= (scene->width() - getWidth()))
        setX(scene->width() - getWidth());
    else setX(x);
}

void Role::up() {
    float y = this->y() - speed;
    if (y <= 0) setY(0);
    else setY(y);
}

void Role::down() {
    float y = this->y() + speed;
    if (y >= (scene->height() - getHeight()))
        setY(scene->height() - getHeight());
    else setY(y);
}

void Role::setHealth(int health) {
    if (health >= HEALTH[key]) this->health = HEALTH[key];
    else this->health = health;
}

void Role::addHealth(int health) {
    this->health += health;
    if (this->health <= 0) {
        this->dead = true;
        this->health = 0;
    }
}

void Role::Reset() {
    this->score = this->type = 0;
    this->health = HEALTH[key];
    this->speed = SPEED[key];
    this->damage = DAMAGE[key];
    this->protect = PROTECT[key];
    this->BulletDamage = BULLETDAMAGE[key];

    this->dead = false;
    setPos(scene->width() / 2 - this->getWidth() / 2, 300);
}

void Role::setFireMode(QPixmap pixmap, int damage, int type) {
    this->m_bullet = pixmap;
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
                m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::U, 20));
          else if (type == 1) {
                            /* 双发模式 */
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4 - 10, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::U, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4 + 10, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::U, 20));
                        }
                        else if (type == 2)
                        {
                            /* 三发模式 */
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::U, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::LU, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::RU, 20));
                        }
                        else if (type == 3)
                        {
                            /* 五发模式 */
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::U, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::LLU, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::LU, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::RRU, 20));
                            m_pRoleBulletList->append(new Bullet(this->x() + pixmap().width() / 4, this->y(), this->m_bullet, this->scene, this->BulletDamage, BulletDirection::RU, 20));
                        }
                    }

                    if (type == 4)
                        /* 重击模式 */
                        m_pRoleBulletList->append(new Bullet(this->x(), this->y(), this->m_bullet, this->scene, this->BulletDamage * 6, BulletDirection::U, 20));
    }
}

void Role::updateAllRoleBullet() {
    for (QList<Bullet*>::iterator i = m_pRoleBulletList->begin(); i != m_pRoleBulletList->end(); ) {

        if ((*i)->isDead() == true) {
            this->scene->removeItem(*i);
            i = m_pRoleBulletList->erase(i);
        }

        else i++;
    }
}

void Role::allRoleBulletRun() {
    for (auto &i : *m_pRoleBulletList)
        i->BulletRun();
}
