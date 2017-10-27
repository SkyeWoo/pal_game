#ifndef BULLET_H
#define BULLET_H

#include "gameobject.h"
#include "common.h"

class Bullet : public GameObject {
    int damage;
    int speed;
    bool dead;
    enum BulletDirection bulletDir;

public:
    Bullet(float x, float y, QPixmap pixmap, QGraphicsScene *scene, int damage, enum BulletDirection dir, int speed = 3, QGraphicsItem *parent = 0);
    virtual ~Bullet() {}
    int getDamage() { return damage; }
    bool isDead() { return dead; }
    void setDead(bool dead) { this->dead = dead; }
    void BulletRun();
};

#endif // BULLET_H
