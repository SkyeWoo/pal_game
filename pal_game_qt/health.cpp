#include "health.h"

RoleHealth::RoleHealth(const int roleHP, QPixmap pixmap, QGraphicsScene *scene)
    : GameObject(pixmap, scene) {
    // 显示在顶层
    setZValue(1);
    this->roleHP = roleHP;
    this->setPos(600, 65);
}

void RoleHealth::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) {
    qreal width = (qreal)hp / roleHP * pixmap().width();
    painter->drawPixmap(this->x(), this->y(), width, pixmap().height(), pixmap());
}
