#include "bullet.h"

Bullet::Bullet(float x, float y, QPixmap pixmap, QGraphicsScene *scene, int damage, enum BulletDirection dir, int speed, QGraphicsItem *parent)
    : GameObject(pixmap, scene, parent) {
    this->setPos(x - this->getWidth() / 2, y - this->getHeight() / 2);
    this->damage = damage;
    this->dead = false;
    this->speed = speed;
    this->bulletDir = dir;
}

void Bullet::BulletRun() {
    if (bulletDir == BulletDirection::D)
        setY(this->y() + speed);
    else if (bulletDir == BulletDirection::U)
        setY(this->y() - speed);
    else if (bulletDir == BulletDirection::L)
        setX(this->x() - speed);
    else if (bulletDir == BulletDirection::R)
        setX(this->x() + speed);
    else if (bulletDir == BulletDirection::LD)
        setPos(this->x() - speed, this->y() + speed);
    else if (bulletDir == BulletDirection::LU)
        setPos(this->x() - speed, this->y() - speed);
    else if (bulletDir == BulletDirection::RD)
        setPos(this->x() + speed, this->y() + speed);
    else if (bulletDir == BulletDirection::RU)
        setPos(this->x() + speed, this->y() - speed);
    else if (bulletDir == BulletDirection::LDD)
        setPos(this->x() - speed, this->y() + 2 * speed);
    else if (bulletDir == BulletDirection::LLD)
        setPos(this->x() - 2 * speed, this->y() + speed);
    else if (bulletDir == BulletDirection::LLU)
        setPos(this->x() - 2 * speed, this->y() - speed);
    else if (bulletDir == BulletDirection::LUU)
        setPos(this->x() - speed, this->y() - 2 * speed);
    else if (bulletDir == BulletDirection::RDD)
        setPos(this->x() + speed, this->y() + 2 * speed);
    else if (bulletDir == BulletDirection::RRD)
        setPos(this->x() + 2 * speed, this->y() + speed);
    else if (bulletDir == BulletDirection::RRU)
        setPos(this->x() + 2 * speed, this->y() - speed);
    else if (bulletDir == BulletDirection::RUU)
        setPos(this->x() + speed, this->y() - 2 * speed);

    if (isOutWindow() == true) setDead(true);
}
