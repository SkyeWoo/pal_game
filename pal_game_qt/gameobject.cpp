#include "gameobject.h"
#include "common.h"

bool GameObject::isCollision(GameObject *gobj) {
    if (gobj == nullptr) return false;

    float h1, h2, w1, w2, r1, r2;
    h1 = this->getHeight();
    h2 = gobj->getHeight();
    w1 = this->getWidth();
    w2 = gobj->getWidth();

    r1 = sqrt(h1 * h1 + w1 * w1) / 6;
    r2 = sqrt(h2 * h2 + w2 * w2) / 6;

    float x1, y1, x2, y2;
    x1 = this->x() + this->getWidth() / 2;
    x2 = gobj->x() + gobj->getWidth() / 2;
    y1 = this->y() + this->getHeight() / 2;
    y2 = gobj->y() + gobj->getHeight() / 2;

    float dis = sqrt(pow(abs(x1 - x2), 2) + pow(abs(y1 - y2), 2));
    if (dis < r1 + r2) return true;
    else return false;
}

bool GameObject::isOutWindow() {
//    if ((this->x() + this->getWidth() <= 0) || this->x() >= this->scene->width())
    if ((this->x() + this->getWidth() <= 0) || this->x() >= 500)
        return true;
//    if ((this->y() + this->getHeight() <= 0) || this->y() >= this->scene->height())
    if ((this->y() + this->getHeight() <= 0) || this->y() >= 320)
        return true;
    return false;
}

void GameObject::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    painter->drawPixmap(this->x(), this->y(), pixmap().width(), pixmap().height(), pixmap());
}
