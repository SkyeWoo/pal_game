#ifndef HEALTH_H
#define HEALTH_H

#include "gameobject.h"

class RoleHealth : public GameObject {
    int hp, roleHP;
public:
    RoleHealth(const int roleHP, QPixmap pixmap, QGraphicsScene *scene);
    ~RoleHealth() {}

    void setHP(int hp) { this->hp = hp; }
    int getHP() { return hp; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // HEALTH_H
