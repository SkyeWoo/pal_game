#pragma once
#pragma comment(lib, "msimg32.lib")

#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <windows.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <list>
using namespace std;

const int WINSCORE = 10000;
const int ENEMYNUM = 14;
const int ENEMYBULLETNUM = 11;
const int GOODSNUM = 30;
const int ROLENUM = 4;
/* 姜 龙 蛮 唐 四人生命 伤害和速度 */
const int HEALTH[] = { 200, 180, 150, 130 };
const int DAMAGE[] = { 100, 120, 90, 80 };
const int SPEED[] = { 4, 4, 6, 5 };
const int BULLETDAMAGE[] = { 3, 3, 2, 2 };

enum BulletDirection { U, LUU, RUU, LU, LLU, RU, RRU, LD, LLD, RD, RRD, LDD, RDD, D, L, R };


#endif // !__COMMON_H__
