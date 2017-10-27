#ifndef GOODS_H
#define GOODS_H

#include "GameObject.h"

class Goods : public GameObject {
    /* 道具被取得或者到达边界消亡 */
    bool dead;
    /* 0~4-buff 5~9-药品 10~12-男鞋 13~15-女鞋 16~18-男防具 19~21-女防具
     * 22~23-姜武器 24~25-龙武器 26~27-蛮武器 28~29-唐武器 */
    /* buff: 随机效果 鞋: speed 防具: health 药品: hp 武器: damage */
    int type;
    float speed_x, speed_y;

public:
    Goods(QPixmap hbmp, QGraphicsScene *scene, int type);
    ~Goods() {}

    int getType() { return type; }
    bool isDead() { return dead; }
    void setDead(bool dead) { this->dead = dead; }

    void GoodsRun();
};

#endif // GOODS_H
