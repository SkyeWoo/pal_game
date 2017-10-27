#include "life.h"

RoleLife::RoleLife(QPixmap pixmap[], QGraphicsScene *scene) {
    for (int i = 0; i < ROLENUM; i++) {
        m_life[i] = new QGraphicsPixmapItem(pixmap[i]);
        m_life[i]->setPos(1000 + 100 * i, 700);
        m_life[i]->setZValue(1);
        scene->addItem(m_life[i]);
    }

    numOfLife = ROLENUM;
}
