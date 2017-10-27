#ifndef ROLE_H
#define ROLE_H

#include "gameobject.h"
#include "common.h"
#include "bullet.h"
#include <QList>

class Role : public GameObject {
    /* 武器的图像 不同角色有不同武器 */
    QPixmap m_bullet;
//    QGraphicsScene *scene;
    bool dead;
    /* 角色伤害值(相撞伤害) 武器伤害值(子弹伤害) 防御 生命值 速度 */
    int damage, BulletDamage, protect, health, speed;
    /* 角色攻击类型 数值越大攻击范围越大 */
    int type;
    /* 当前角色得分 得分到一定程度type会升级 */
    int score;
    /* 角色键值 根据key值判断是哪个角色 */
    int key;
public:
    Role(QPixmap pixmap, QGraphicsScene *scene, int key);
    ~Role();
    void left();
    void right();
    void up();
    void down();
    bool isDead() { return dead; }

    int getKey() { return key; }
    int getScore() { return score; }
    int getType() { return type; }
    int getHealth() { return health; }
    int getDamage() { return damage; }
    int getProtect() { return protect; }
    int getSpeed() { return speed; }

    void addHealth(int health);
    void setHealth(int health);
    void setKey(int key) { this->key = key; }
    void setScore(int score) { this->score = score; }
    void setType(int type) { this->type = type; }
    void setDamage(int damage) { this->damage = damage; }
    void setProtect(int protect) { this->protect = protect; }
    void setSpeed(int speed) { this->speed = speed; }
    void setDead(bool dead) { this->dead = dead; }

    void Reset();
    void Fire();
    void changeType();
    void setFireMode(QPixmap pixmap, int damage, int type);
    void updateAllRoleBullet();
    void allRoleBulletRun();

    QList<Bullet*> *m_pRoleBulletList;		// Role子弹链表
};

#endif // ROLE_H
