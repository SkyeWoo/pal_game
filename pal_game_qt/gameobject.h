#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QPixmap>
#include <QPainter>

class GameObject : public QObject, public QGraphicsPixmapItem {
public:
    GameObject(QPixmap pixmap, QGraphicsScene *scene, QGraphicsItem *parent = 0)
        : QGraphicsPixmapItem(pixmap, parent) {
        this->scene = scene;
        scene->addItem(this);
    }
    QGraphicsScene *scene;
    QRect boundingRect() { return QRect(0, 0, scene->width(), scene->height()); }
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    int getHeight() { return this->pixmap().height(); }
    int getWidth() { return this->pixmap().width(); }

    bool isCollision(GameObject *gobj);
    bool isOutWindow();
};

#endif // GAMEOBJECT_H
