#include "controller.h"
#include "ui_pal_game.h"

Controller::Controller(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Controller),
    m_pScene(-10, -10, 900, 500),
    m_pImages(new Images())
{
    ui->setupUi(this);
    ui->RunningView->setScene(&m_pScene);

    ui->RunningView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->RunningView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    /* 实时刷新画面 */
    connect(&m_pTimer, SIGNAL(timeout()), this, SLOT(GameUpdate()));

    sndAvail = true;
    sndBackGround = new QSound(":/snd/snd/pal4-回梦游仙.wav");
//    sndBackGround = new QSound(":/snd/snd/pal5-心愿.wav");
    sndGame = new QSound(":/snd/snd/pal5-逐韵律.wav");
    sndGood = new QSound(":/snd/snd/getGood.wav");
    sndHurt_female = new QSound(":/snd/snd/受伤-female.wav");
    sndHurt_male = new QSound(":/snd/snd/受伤-male.wav");
    sndWin = new QSound(":/snd/snd/战斗胜利.wav");
    sndLost = new QSound(":/snd/snd/战斗失败.wav");

    init();
}

Controller::~Controller()
{
    delete ui;
}

void Controller::init() {
    m_pScene.clear();

    ui->StartWidget->setFocus();

    ui->Config->setEnabled(false);
    ui->Config->setVisible(false);

    ui->RunningView->setEnabled(false);
    ui->RunningView->setVisible(false);

    ui->Atribute->setEnabled(false);
    ui->Atribute->setVisible(false);

    ui->Continue->setEnabled(false);
    ui->Continue->setVisible(false);
    ui->GameOver->setEnabled(false);
    ui->GameOver->setVisible(false);
    ui->GamePass->setEnabled(false);
    ui->GamePass->setVisible(false);
    ui->GamePass->tabBar()->hide();

    ui->StartWidget->setEnabled(true);
    ui->StartWidget->setVisible(true);
    ui->InstructWindow->setCurrentIndex(0);
    ui->InstructWindow->setVisible(false);
    ui->InstructWindow->tabBar()->hide();
    ui->LastPage->setEnabled(false);
    ui->LastPage->setVisible(false);
    ui->NextPage->setEnabled(false);
    ui->NextPage->setVisible(false);
    ui->Close->setEnabled(false);
    ui->Close->setVisible(false);

    /* 游戏还没开始 */
    this->state = -1;

    if (sndAvail == true) {
        sndWin->stop();
        sndLost->stop();
        sndBackGround->play();
    }
}

void Controller::keyPressEvent(QKeyEvent *event) {
    int keyValue = event->key();
    switch(keyValue) {
    case Qt::Key_I:
        on_Instruction_clicked(); break;
    case Qt::Key_Q:
        if (ui->GameExit->isEnabled()) on_GameExit_clicked(); break;
    case Qt::Key_Y:
        if (ui->Continue->isEnabled()) on_Yes_clicked();
        else if (ui->Config->isEnabled()) on_confirmConfig_clicked();
        break;
    case Qt::Key_N:
        if (ui->Continue->isEnabled()) on_No_clicked();
        else if (ui->Config->isEnabled()) on_cancelConfig_clicked();
        break;
    case Qt::Key_R:
        if (ui->RunningView->isEnabled()) ResetRole(); break;
    case Qt::Key_C:
        if (state == -1 && ui->Config->isEnabled()) on_setConfig_clicked();
        break;
    case Qt::Key_Up:
        if (ui->RunningView->isEnabled()) {
            if (!event->isAutoRepeat()) setGoingUp(true);
        }
        else if (ui->Config->isEnabled()) {
            ui->openSound->setChecked(true);
            on_openSound_clicked();
        }
        break;
    case Qt::Key_Down:
        if (ui->RunningView->isEnabled()) {
            if (!event->isAutoRepeat()) setGoingDown(true);
        }
        else if (ui->Config->isEnabled()) {
            ui->closeSound->setChecked(true);
            on_closeSound_clicked();
        }
        break;
    case Qt::Key_Left:
        if (ui->InstructWindow->isEnabled()) on_LastPage_clicked();
        else
            if (ui->RunningView->isEnabled() && !event->isAutoRepeat()) setGoingLeft(true);
        break;
    case Qt::Key_Right:
        if (ui->InstructWindow->isEnabled()) on_NextPage_clicked();
        else
            if (ui->RunningView->isEnabled() && !event->isAutoRepeat()) setGoingRight(true);
        break;
    case Qt::Key_Space:
        if (ui->RunningView->isEnabled() && !event->isAutoRepeat()) setRoleFire(true);
        break;
    case Qt::Key_Escape:
        if (ui->Config->isEnabled() == true) on_cancelConfig_clicked();
        else if (ui->InstructWindow->isEnabled() == true) on_Close_clicked();
        else if (state == 1) GamePause();
        break;
    case Qt::Key_Return:
        if (ui->GameStart->isEnabled()) on_GameStart_clicked();
        else if (state == 2) on_No_clicked();
        break;
    }
}

void Controller::keyReleaseEvent(QKeyEvent *event) {
    int keyValue = event->key();
    switch(keyValue) {
    case Qt::Key_Up:
        if (!event->isAutoRepeat() && isGoingUp) setGoingUp(false);
        break;
    case Qt::Key_Down:
        if (!event->isAutoRepeat() && isGoingDown) setGoingDown(false);
        break;
    case Qt::Key_Left:
        if (!event->isAutoRepeat() && isGoingLeft) setGoingLeft(false);
        break;
    case Qt::Key_Right:
        if (!event->isAutoRepeat() && isGoingRight) setGoingRight(false);
        break;
    case Qt::Key_Space:
        if (!event->isAutoRepeat() && isFire) setRoleFire(false);
    }
}

void Controller::on_GameExit_clicked()
{
    this->close();
}

void Controller::on_Instruction_clicked()
{
    ui->InstructWindow->setEnabled(true);
    ui->InstructWindow->setVisible(true);
    ui->NextPage->setVisible(true);
    ui->LastPage->setVisible(true);
    ui->NextPage->setEnabled(true);
    ui->LastPage->setEnabled(true);
    ui->Close->setEnabled(true);
    ui->Close->setVisible(true);
    ui->GameStart->setEnabled(false);
    ui->GameExit->setEnabled(false);
    ui->Config->setEnabled(false);
}

void Controller::on_Close_clicked()
{
    ui->GameStart->setEnabled(true);
    ui->GameExit->setEnabled(true);
    ui->Config->setEnabled(true);
    ui->InstructWindow->setEnabled(false);
    ui->InstructWindow->setVisible(false);
    ui->LastPage->setEnabled(false);
    ui->LastPage->setVisible(false);
    ui->NextPage->setEnabled(false);
    ui->NextPage->setVisible(false);
    ui->Close->setEnabled(false);
    ui->Close->setVisible(false);
}

void Controller::on_LastPage_clicked()
{
    int index = ui->InstructWindow->currentIndex();
    int count = ui->InstructWindow->count();
    ui->InstructWindow->setCurrentIndex((index + count - 1) % count);
}

void Controller::on_NextPage_clicked()
{
    int index = ui->InstructWindow->currentIndex();
    int count = ui->InstructWindow->count();
    ui->InstructWindow->setCurrentIndex((index + 1) % count);
}

void Controller::on_Yes_clicked()
{
    state = 1;
    ui->Continue->setEnabled(false);
    ui->Continue->setVisible(false);
    ui->RunningView->setEnabled(true);
    m_pTimer.start(1000 / 24);
    if (sndAvail) sndGame->play();
}

void Controller::on_No_clicked()
{
    state = -1;
    init();
}

void Controller::on_GameStart_clicked()
{
    GameStart();
}

void Controller::on_Confirm_clicked()
{
    on_No_clicked();
}

void Controller::on_GamePassConfirm_1_clicked()
{
    on_No_clicked();
}

void Controller::on_GamePassConfirm_2_clicked()
{
    on_No_clicked();
}

void Controller::on_GamePassConfirm_3_clicked()
{
    on_No_clicked();
}

void Controller::on_GamePassConfirm_4_clicked()
{
    on_No_clicked();
}

void Controller::on_setConfig_clicked()
{
    ui->Config->setEnabled(true);
    ui->Config->setVisible(true);

    ui->GameStart->setEnabled(false);
    ui->Instruction->setEnabled(false);
    ui->GameExit->setEnabled(false);
}

void Controller::GameStart() {
    m_pScene.clear();
    ui->RunningView->setFocus();
    m_pTimer.start(1000/24);

    if (sndAvail) {
        sndBackGround->stop();
        sndGame->play();
        sndGame->setLoops(-1);
    }

    if (state == -1) state = 1;
    ui->RunningView->setEnabled(true);
    ui->RunningView->setVisible(true);

    ui->Atribute->setEnabled(true);
    ui->Atribute->setVisible(true);

    ui->StartWidget->setEnabled(false);
    ui->StartWidget->setVisible(false);

    /* ScoreBoard */
    m_pScore = new QGraphicsPixmapItem(m_pImages->hImgScore);
    /* 显示在顶层 */
    m_pScore->setZValue(1);
    m_pScene.addItem(m_pScore);
    m_pScore->setPos(5, 5);
    for (int i = 0; i < 5; i++) {
        m_ScoreNum[i] = new QGraphicsPixmapItem(m_pImages->hImgNum[0]);
        m_pScene.addItem(m_ScoreNum[i]);
        m_ScoreNum[i]->setPos(35 * i + 100, 22);
        /* 显示在得分板上面 */
        m_ScoreNum[i]->setZValue(2);
    }

    /* LifeBoard */
    m_pRoleLife = new RoleLife(m_pImages->hImgLife, &m_pScene);

    /* 角色初始子弹伤害值为2 */
    RoleCurrentDamage = 2;
    flag_win = false;

    /* 创建角色 默认为姜云凡 */
    m_pRole = new Role(m_pImages->hImgRole[0], &m_pScene, 0);
    m_pRoleHealth = new RoleHealth(HEALTH[0], m_pImages->hImgHealth, &m_pScene);
    /* 角色初始化 */
    ResetRole();

    /* AttributeBoard */
    m_HPNum[2] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[m_pRoleHealth->getHP() % 10]);
    m_HPNum[1] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[(m_pRoleHealth->getHP() / 10) % 10]);
    m_HPNum[0] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[(m_pRoleHealth->getHP() / 100) % 10]);
    for (int i = 0; i < 3; i++) {
        m_pScene.addItem(m_HPNum[i]);
        m_HPNum[i]->setPos(1330 + 16 * i, 125);
        m_HPNum[i]->setZValue(1);
    }
    m_damage[2] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[m_pRole->getDamage() % 10]);
    m_damage[1] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[(m_pRole->getDamage() / 10) % 10]);
    m_damage[0] = new QGraphicsPixmapItem(m_pImages->hImgAttNum[(m_pRole->getDamage() / 100) % 10]);
    for (int i = 0; i < 3; i++) {
        m_pScene.addItem(m_damage[i]);
        m_damage[i]->setPos(1330 + 16 * i, 177);
        m_damage[i]->setZValue(1);
    }
    m_protect = new QGraphicsPixmapItem(m_pImages->hImgAttNum[m_pRole->getProtect()]);
    m_pScene.addItem(m_protect);
    m_protect->setPos(1330, 215);
    m_protect->setZValue(1);
    m_speed = new QGraphicsPixmapItem(m_pImages->hImgAttNum[m_pRole->getSpeed()]);
    m_pScene.addItem(m_speed);
    m_speed->setPos(1330, 253);
    m_speed->setZValue(1);

    m_pEnemyList = new QList<Enemy*>();
    m_pEnemyBulletList = new QList<Bullet*>();
    m_pExplodeList = new QList<Explode*>();
    m_pGoodsList = new QList<Goods*>();
    this->totScore = 0;
}

void Controller::GamePause() {
    if (state == 0) {
        state = 1;
        if (sndAvail) sndGame->play();
    }
    else if (state == 1) {
        state = 0;
        m_pTimer.stop();
        if (sndAvail) sndGame->stop();
    }

    ui->RunningView->setEnabled(false);
    ui->Continue->setEnabled(true);
    ui->Continue->setVisible(true);
}

void Controller::GameEnd() {
    state = 2;
    m_pTimer.stop();
    sndGame->stop();
    ui->RunningView->setEnabled(false);
    if (flag_win == true) {
        if (sndAvail) sndWin->play();
        ui->GamePass->setCurrentIndex(m_pRole->getKey());
        ui->GamePass->setEnabled(true);
        ui->GamePass->setVisible(true);
    }
    else {
        if (sndAvail) sndLost->play();
        ui->GameOver->setEnabled(true);
        ui->GameOver->setVisible(true);
    }
}

void Controller::GameWaitReset() {
    state = 3;
    m_pTimer.stop();
    sndGame->stop();
    ResetRole();
    ui->RunningView->setEnabled(false);
    ui->Continue->setEnabled(true);
    ui->Continue->setVisible(true);
}

void Controller::ResetRole() {
    if (m_pRoleLife->getLifeNum() > 0) {
        m_pRoleLife->setLifeNum(m_pRoleLife->getLifeNum() - 1);		// 初始设置生命数

        /* 更换角色 */
        int key = ROLENUM - 1 - m_pRoleLife->getLifeNum();

        m_pRole->setKey(key);
        m_pRole->Reset();
        m_pRole->setPixmap(m_pImages->hImgRole[key]);
        m_pRole->setFireMode(m_pImages->hImgBullet[key], RoleCurrentDamage, 0);
        isGoingUp = isGoingDown = isGoingLeft = isGoingRight = false;
        isFire = false;

        m_pRoleHealth->setHP(m_pRole->getHealth());					// 获取生命值

        /* 游戏恢复运行 */
        this->state = 1;
    }
}

void Controller::setRoleFireMode(int type, int damage) {
    if (m_pRole != nullptr)
        m_pRole->setFireMode(m_pImages->hImgBullet[m_pRole->getKey()], damage, type);
}


void Controller::addEnemy() {
    static int i = 0;
    static int life_count = 1, type_count = 1;
    i++;
    if (i % 50 == 0 && type_count < 4) type_count += 1;
    if (i == 6000) {
        life_count++; i = 0;
    }
    if (m_pEnemyList->size() < 10 && rand() % 100 > 95)
        /* enemy的生命值会随count递增 时间越长 enemy生命值越高 type取值范围也越大 */
        m_pEnemyList->append(new Enemy(m_pImages->hImgEnemy[rand() % ENEMYNUM], &m_pScene, this, life_count * 20, rand() % type_count));
}

void Controller::addGoods() {
    if (m_pGoodsList->size() < 30 && rand() % 1000 > 990) {
        int type = rand() % 30;
        m_pGoodsList->append(new Goods(m_pImages->hImgGoods[type], &m_pScene, type));
    }
}

void Controller::allEnemyRun() {
    addEnemy();

    for (auto &i : *m_pEnemyList) {
        i->EnemyRun();
        /* 判断enemy是否被role击中 */
        i->beHit(m_pRole);

        /* enemy与role相撞 */
        if (!m_pRole->isDead() && i->isCollision(m_pRole)) {
            /* role血量减少 */
            m_pRole->addHealth(-i->getDamage());
            if (sndAvail) {
                if (m_pRole->getKey() < 2) sndHurt_male->play();
                else sndHurt_female->play();
            }
            m_pExplodeList->append(new Explode(i->getDamage(), getImages()->hImgMinus, getImages()->hImgDelNum, this, &m_pScene));

            /* 如果role死亡 爆炸 */
            if (m_pRole->isDead()) {
                if (m_pRoleLife->getLifeNum() > 0) GameWaitReset();
                else GameEnd();
            }
            m_pRoleHealth->setHP(m_pRole->getHealth());

            /* enemy血量减少 */
            i->addHealth(-m_pRole->getDamage());
        }
    }

    for (QList<Enemy*>::iterator i = m_pEnemyList->begin(); i != m_pEnemyList->end();) {
        if ((*i)->isDead()) {
            /* 得到enemy相应分值 */
            totScore += (*i)->getScore();
            if (totScore >= WINSCORE) {
                flag_win = true; state = 2; GameEnd();
            }
            m_pRole->setScore((*i)->getScore());
            m_pRole->changeType();
            m_pScene.removeItem(*i);
            i = m_pEnemyList->erase(i);		/* 消除该enemy对象 */
        }
        else i++;
    }
}

void Controller::allRun() {
    /* 所有角色发出的子弹移动 */
    if (m_pRole->isDead() == false) RoleRun();
    m_pRole->allRoleBulletRun();
    /* 所有enemy发出的子弹移动 */
    allEnemyRun();
    allEnemyBulletRun();
    allGoodsRun();

    updateScore();
}

void Controller::RoleRun() {
    if (m_pRole == nullptr) return;

    if (isFire) m_pRole->Fire();
    if (isGoingUp) m_pRole->up();
    if (isGoingDown) m_pRole->down();
    if (isGoingLeft) m_pRole->left();
    if (isGoingRight) m_pRole->right();
}

void Controller::allEnemyBulletRun() {
    /* 遍历enemy子弹链表 */
    for (auto &i : *m_pEnemyBulletList) {
        i->BulletRun();

        /* Role is hit */
        if (!m_pRole->isDead() && i->isCollision(m_pRole)) {
            if (i->getDamage() - m_pRole->getProtect() > 0) {
                m_pRole->addHealth(-(i->getDamage() - m_pRole->getProtect()));
                if (sndAvail) {
                    if (m_pRole->getKey() < 2) sndHurt_male->play();
                    else sndHurt_female->play();
                }
                m_pExplodeList->append(new Explode(i->getDamage() - m_pRole->getProtect(), getImages()->hImgMinus, getImages()->hImgDelNum, this, &m_pScene));
            }
            /* Role is dead, explode */
            if (m_pRole->isDead()) {
                m_pRole->setVisible(false);
                if (m_pRoleLife->getLifeNum() > 0) GameWaitReset();
                else GameEnd();
            }

            m_pRoleHealth->setHP(m_pRole->getHealth());
            i->setDead(true);		/* 子弹用过消亡 */
        }
    }

    for (QList<Bullet*>::iterator i = m_pEnemyBulletList->begin(); i != m_pEnemyBulletList->end(); )
        if ((*i)->isDead()) {
            m_pScene.removeItem(*i);
            i = m_pEnemyBulletList->erase(i);
        }
        else i++;
}

void Controller::allGoodsRun() {
    addGoods();

    for (auto &i : *m_pGoodsList) {
        i->GoodsRun();

        /* role得到物品 */
        if (!m_pRole->isDead() && i->isCollision(m_pRole)) {
            /* 物品效果 */
            if (sndAvail) sndGood->play();
            if (i->getType() < 5) {
                /* random buff */
                int temp = rand() % 4;
                switch (temp) {
                case 0: // hp
                    if (m_pRoleHealth->getHP() + 10  <= HEALTH[m_pRole->getKey()]) {
                        m_pRoleHealth->setHP(m_pRoleHealth->getHP() + 10);
                        m_pExplodeList->append(new Explode(10, getImages()->hImgPlus, getImages()->hImgIncreNum, this, &m_pScene));
                    }
                    break;
                case 1: // speed
                    // speed上限为8
                    if (m_pRole->getSpeed() + 1 < 9)
                        m_pRole->setSpeed(m_pRole->getSpeed() + 1);
                    break;
                case 2: // protect
                    // protect上限为5
                    if (m_pRole->getProtect() + 1 < 6)
                        m_pRole->setProtect(m_pRole->getProtect() + 1);
                    break;
                case 3: // damage
                    // damage上限为250
                    if (m_pRole->getDamage() + 10 <= 250)
                        m_pRole->setDamage(m_pRole->getDamage() + 10);
                    RoleCurrentDamage += 1;
                    break;
                }
            }
            else if (i->getType() < 10)	{// hp
                if (m_pRoleHealth->getHP() + 10  <= HEALTH[m_pRole->getKey()]) {
                    m_pRoleHealth->setHP(m_pRoleHealth->getHP() + 10);
                    m_pExplodeList->append(new Explode(10, getImages()->hImgPlus, getImages()->hImgIncreNum, this, &m_pScene));
                }
            }
            // speed
            else if (i->getType() < 13) {
                if (m_pRole->getKey() < 2)	// male
                    if (m_pRole->getSpeed() + 1 < 9)
                        m_pRole->setSpeed(m_pRole->getSpeed() + 1);
            }
            else if (i->getType() < 16) {
                if (m_pRole->getKey() >= 2)
                    if (m_pRole->getSpeed() + 1 < 9)
                        m_pRole->setSpeed(m_pRole->getSpeed() + 1);
            }
            // protect
            else if (i->getType() < 19) {
                if (m_pRole->getKey() < 2)
                    if (m_pRole->getProtect() + 1 < 6)
                        m_pRole->setProtect(m_pRole->getProtect() + 1);
            }
            else if (i->getType() < 22) {
                if (m_pRole->getKey() >= 2)
                    if (m_pRole->getProtect() + 1 < 6)
                        m_pRole->setProtect(m_pRole->getProtect() + 1);
            }
            // damage
            else if (i->getType() < 24) {
                if (m_pRole->getKey() == 0) {// 姜
                    if (m_pRole->getDamage() + 10 <= 250)
                        m_pRole->setDamage(m_pRole->getDamage() + 10);
                    RoleCurrentDamage += 1;
                }
            }
            else if (i->getType() < 26) {
                if (m_pRole->getKey() == 1) {// 龙
                    if (m_pRole->getDamage() + 10 <= 250)
                        m_pRole->setDamage(m_pRole->getDamage() + 10);
                    RoleCurrentDamage += 1;
                }
            }
            else if (i->getType() < 28) {
                if (m_pRole->getKey() == 2) {// 蛮
                    if (m_pRole->getDamage() + 10 <= 250)
                        m_pRole->setDamage(m_pRole->getDamage() + 10);
                    RoleCurrentDamage += 1;
                }
            }
            else {
                if (m_pRole->getKey() == 3) {// 唐
                    if (m_pRole->getDamage() + 10 <= 250)
                        m_pRole->setDamage(m_pRole->getDamage() + 10);
                    RoleCurrentDamage += 1;
                }
            }

            i->setDead(true);
        }
    }

    updateAttribute();

    for (QList<Goods*>::iterator i = m_pGoodsList->begin(); i != m_pGoodsList->end();) {
        if ((*i)->isDead() == true) {
            m_pScene.removeItem(*i);
            i = m_pGoodsList->erase(i);
        }
        else i++;
    }
}
void Controller::GameUpdate() {
    allRun();

    updateAllExplode();
    updateAllGoods();

    m_pScene.update();
}

void Controller::updateScore() {
    int num[5] = { 0 };
    num[4] = totScore % 10;
    num[3] = (totScore / 10) % 10;
    num[2] = (totScore / 100) % 10;
    num[1] = (totScore / 1000) % 10;
    num[0] = (totScore / 10000) % 10;

    for (int i = 0; i < 5; i++)
        m_ScoreNum[i]->setPixmap(m_pImages->hImgNum[num[i]]);
}

void Controller::updateAttribute() {
    int hp = m_pRoleHealth->getHP();
    m_HPNum[2]->setPixmap(m_pImages->hImgAttNum[hp % 10]);
    m_HPNum[1]->setPixmap(m_pImages->hImgAttNum[(hp / 10) % 10]);
    m_HPNum[0]->setPixmap(m_pImages->hImgAttNum[(hp / 100) % 10]);
    m_damage[2]->setPixmap(m_pImages->hImgAttNum[m_pRole->getDamage() % 10]);
    m_damage[1]->setPixmap(m_pImages->hImgAttNum[(m_pRole->getDamage() / 10) % 10]);
    m_damage[0]->setPixmap(m_pImages->hImgAttNum[(m_pRole->getDamage() / 100) % 10]);
    m_protect->setPixmap(m_pImages->hImgAttNum[m_pRole->getProtect()]);
    m_speed->setPixmap(m_pImages->hImgAttNum[m_pRole->getSpeed()]);
}

void Controller::updateAllExplode() {
    for (QList<Explode*>::iterator i = m_pExplodeList->begin(); i != m_pExplodeList->end();)
        if ((*i)->isDead()) {
            m_pScene.removeItem(*i);
            i = m_pExplodeList->erase(i);
        }
        else i++;
}

void Controller::updateAllGoods() {
    for (QList<Goods*>::iterator i = m_pGoodsList->begin(); i != m_pGoodsList->end();)
        if ((*i)->isDead()) {
            m_pScene.removeItem(*i);
            i = m_pGoodsList->erase(i);
        }
        else i++;
}

void Controller::on_openSound_clicked()
{
    tempAvail = true;
}

void Controller::on_closeSound_clicked()
{
    tempAvail = false;
}

void Controller::on_confirmConfig_clicked()
{
    if (tempAvail == false) sndBackGround->stop();
    else if (sndAvail == false && tempAvail == true) sndBackGround->play();
    sndAvail = tempAvail;
    ui->Config->setEnabled(false);
    ui->Config->setVisible(false);

    ui->GameStart->setEnabled(true);
    ui->Instruction->setEnabled(true);
    ui->GameExit->setEnabled(true);
}

void Controller::on_cancelConfig_clicked()
{
    if (sndAvail == true) ui->openSound->setChecked(true);
    else ui->closeSound->setChecked(true);
    ui->Config->setEnabled(false);
    ui->Config->setVisible(false);

    ui->GameStart->setEnabled(true);
    ui->Instruction->setEnabled(true);
    ui->GameExit->setEnabled(true);
}
