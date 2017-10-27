#include "explode.h"

Explode::Explode(int hurt, QPixmap d, QPixmap pixmap[], Controller *controller, QGraphicsScene *scene)
    : QGraphicsPixmapItem(d) {
    scene->addItem(this);
    this->hurt = hurt;
    this->controller = controller;

    state = 1.0;

    count = 0;
    while (hurt > 0) {
        explode[count++] = new QGraphicsPixmapItem(pixmap[hurt % 10]);
        hurt /= 10;
    }

    this->dead = false;

    /* 淡出效果 */
    connect(controller->getTimer(), SIGNAL(timeout()), this, SLOT(fade()));
}

void Explode::fade() {
    if (state <= 0.0)
        this->dead = true;
    else {
        this->setOpacity(state);
        for (int i = 0; i < count; i++)
            explode[i]->setOpacity(state);
    }
    state -= 0.1;
}

void Explode::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    if (dead == false) {
        qreal x = controller->getRole()->x();
        qreal y = controller->getRole()->y();
        if (count > 0) painter->drawPixmap(2 * x - this->pixmap().width() + 45, y + 90, this->pixmap());
        for (int i = 0; i < count; i++)
            painter->drawPixmap(2 * x + (count - i - 1) * 35 + 45, y + 90, explode[i]->pixmap());
    }
}
