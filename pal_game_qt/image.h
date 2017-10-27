#ifndef IMAGE_H
#define IMAGE_H

#include "common.h"

class Images
{
public:
    //TODO!
    QPixmap hImgGameOver;
    QPixmap hImgScore;
    QPixmap hImgNum[10];
    QPixmap hImgAttNum[10];
    QPixmap hImgMinus;
    QPixmap hImgPlus;
    QPixmap hImgDelNum[10];
    QPixmap hImgIncreNum[10];
    QPixmap hImgRole[ROLENUM];
    QPixmap hImgBullet[ROLENUM];
    QPixmap hImgEnemy[ENEMYNUM];
//    QPixmap hImgEnemyBullet[ENEMYBULLETNUM];
    QPixmap hImgEnemyBullet;
    QPixmap hImgHealth;
    QPixmap hImgLife[ROLENUM];
    QPixmap hImgExplode[15];
    QPixmap hImgGoods[GOODSNUM];
    QPixmap hImgPass[ROLENUM];

    Images();
    ~Images() {}
};


#endif // IMAGE_H
