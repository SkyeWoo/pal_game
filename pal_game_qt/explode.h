#ifndef EXPLODE_H
#define EXPLODE_H

#include <QGraphicsOpacityEffect>
#include <QTimer>
#include "controller.h"

class Controller;
class Explode : public QObject, public QGraphicsPixmapItem {
    int hurt, count;
    /* 是否已经完成爆炸 */
    bool dead;
    qreal state;

    Controller *controller;

    /* delNum */
    QGraphicsPixmapItem *explode[3];

    Q_OBJECT
public slots:
    void fade();

public:
    Explode(int hurt, QPixmap d, QPixmap pixmap[], Controller *controller, QGraphicsScene *scene);
    ~Explode() {}

    bool isDead() { return dead; }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // EXPLODE_H
