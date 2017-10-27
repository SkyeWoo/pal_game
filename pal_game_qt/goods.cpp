#include "goods.h"

Goods::Goods(QPixmap hbmp, QGraphicsScene *scene, int type)
    : GameObject(hbmp, scene) {
    this->setX(rand() % 1440 + 100);
    this->setY(0);
    dead = false;
    speed_x = rand() % 5 - 2;
    speed_y = rand() % 2 + 1;
//	if (speed_x == 0 && speed_y == 1)
//		speed_x = 1;
    this->type = type;
}

void Goods::GoodsRun() {
    if (rand() % 100 == 1) setX(this->x() + speed_x);
    else setX(this->x() - speed_x);
    setY(this->y() + speed_y);

    if (isOutWindow()) dead = true;
}
