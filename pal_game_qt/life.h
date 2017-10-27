#ifndef LIFE_H
#define LIFE_H

#include "common.h"

class RoleLife {
    int numOfLife;

public:
    RoleLife(QPixmap pixmap[], QGraphicsScene *scene);
    ~RoleLife() {}
    QGraphicsPixmapItem *m_life[ROLENUM];

    int getLifeNum() { return numOfLife; }
    void setLifeNum(int numOfLife) { this->numOfLife = numOfLife; }
};

#endif // LIFE_H
