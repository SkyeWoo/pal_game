#ifndef ENEMY_H
#define ENEMY_H

#include "common.h"
#include "gameobject.h"
#include "controller.h"
#include "role.h"

class Controller;
class Enemy : public GameObject {
    int speed_x, speed_y;

    /* 击杀enemy可获得的分值 */
    int score;

    /* 1:boss1  2:boss2 3:boss3 4:boss4 0:小怪 */
    int type;
    int health;
    int damage;
    int BulletType;
    bool dead;
    QPixmap m_bullet;
    Controller *m_pController;
//    QGraphicsScene *scene;

public:
    /* 默认构造小怪 */
    Enemy(QPixmap pixmap, QGraphicsScene *scene, Controller *pController, int health, int type = 0);
    virtual ~Enemy() {}
    virtual void Fire();
    bool isDead() { return dead; }
    void setDead(bool dead) { this->dead = dead; }
    int getScore() { return score; }
    int getDamage() { return damage; }
    void addHealth(int health);
    void setFireMode(QPixmap pixmap, int damage, int BulletType);
    void EnemyRun();
    /* 判断是否被击中 */
    void beHit(Role *role);
};

#endif // ENEMY_H
