#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QTimer>
#include <QSound>

#include "image.h"
#include "gameobject.h"
#include "life.h"
#include "role.h"
#include "enemy.h"
#include "health.h"
#include "goods.h"
#include "explode.h"

namespace Ui {
class Controller;
}

class Enemy;
class Explode;
class Controller : public QMainWindow
{
    Q_OBJECT

public:
    bool flag_win;

    explicit Controller(QWidget *parent = 0);
    ~Controller();

    void init();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    void GameStart();
    void GamePause();
    void GameEnd();
    void GameWaitReset();
    void ResetRole();

    int getState() { return state; }
    Images *getImages() { return m_pImages; }
    QGraphicsScene *getScene() { return &m_pScene; }
    Role *getRole() { return m_pRole; }
    QTimer *getTimer() { return &m_pTimer; }

    void setGoingUp(bool up) { isGoingUp = up; }
    void setGoingDown(bool down) { isGoingDown = down; }
    void setGoingLeft(bool left) { isGoingLeft = left; }
    void setGoingRight(bool right) { isGoingRight = right; }
    void setRoleFire(bool fire) { isFire = fire; }
    void setRoleFireMode(int type, int damage);

    QList<Enemy*> *m_pEnemyList;
    QList<Bullet*> *m_pEnemyBulletList;
    QList<Explode*> *m_pExplodeList;
    QList<Goods*> *m_pGoodsList;

    bool tempAvail, sndAvail;
    QSound *sndHurt_male, *sndHurt_female;
    QSound *sndBackGround;
    QSound *sndGame;
    QSound *sndGood;
    QSound *sndWin, *sndLost;

    void addEnemy();
    void addGoods();
    void allRun();
    void allEnemyRun();
    void allEnemyBulletRun();
    void allGoodsRun();

    void updateScore();
    void updateAttribute();
    void updateAllExplode();
    void updateAllGoods();

private slots:
    void on_Instruction_clicked();

    void on_GameExit_clicked();

    void on_Close_clicked();

    void on_LastPage_clicked();

    void on_NextPage_clicked();

    void on_GameStart_clicked();

    void on_Yes_clicked();

    void on_No_clicked();

    void GameUpdate();

    void on_GamePassConfirm_1_clicked();

    void on_GamePassConfirm_2_clicked();

    void on_GamePassConfirm_3_clicked();

    void on_GamePassConfirm_4_clicked();

    void on_Confirm_clicked();

    void on_setConfig_clicked();

    void on_openSound_clicked();

    void on_closeSound_clicked();

    void on_confirmConfig_clicked();

    void on_cancelConfig_clicked();

private:
    Ui::Controller *ui;

    QGraphicsScene m_pScene;


    /* 游戏状态 -1:游戏未开始 0:暂停 1:运行 2:结束 3:Hero死亡 */
    int  state;

    /* 定时器 */
    QTimer m_pTimer;
    Images *m_pImages;

    /* 角色 */
    Role *m_pRole;
    /* 角色移动及是否开火状态 */
    bool isGoingUp, isGoingDown, isGoingLeft, isGoingRight;
    bool isFire;
    /* 角色当前伤害值 */
    int RoleCurrentDamage;
    /* 角色移动和开火控制 */
    void RoleRun();
    /* 角色hp */
    RoleHealth *m_pRoleHealth;

    /* 生命板 生命数 */
    RoleLife *m_pRoleLife;

    /* 总得分 */
    int totScore;
    /* 得分板 */
    QGraphicsPixmapItem *m_pScore;
    QGraphicsPixmapItem *m_ScoreNum[5];
    QGraphicsPixmapItem *m_HPNum[3];
    QGraphicsPixmapItem *m_damage[3];
    QGraphicsPixmapItem *m_protect;
    QGraphicsPixmapItem *m_speed;
};

#endif // CONTROLLER_H
