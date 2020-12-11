#pragma once
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"Color.h"

#define INRANGE(x,y) ((x>=0)&&(x<=4)&&(y>=0)&&(y<=9))
#define PRINT_SPACE_START {0,0}
#define PRINT_SPACE_SHOP  {0,42}
#define PRINT_SPACE_PLANT(x) {(short)plantNameLen[i],42}
#define PRINT_SPACE_CD(X)	 {(short)(plantNameLen[i]+1),43}
#define PRINT_SPACE_MESSAGE {0,44}
#define PRINT_SPACE_SUN {0,41}
#define PRINT_SPACE_POINT {30,41}
#define PRINT_SPACE_TIMECT {60,41}

#define KEY_CTRL -32
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13
#define KEY_BACKSPACE 8

#define STAT_MOV  0//行进且无阻碍
#define STAT_BITE 1//有植物,停下来吃
#define STAT_WAIT 2//有僵尸,等待

//(5+1)*(8+1) --> (7+1)*(12+1)
inline short NormX(int x) { return x / 8;}
inline short NormY(int y) { return y / 13; }   //属于哪个格子
inline short LatX(int x)  {return 8*x + 1;}
inline short LatY(int y)  {return 13*y + 1;}  //属于哪个格子


//打印消息message_printf
#define mprintf(fmt) \
	HideCursor();\
	SetConsoleCursorPosition(hOut,PRINT_SPACE_MESSAGE);\
	printf(ANSI_GREEN_BG"[消息]: ");\
	printf(fmt);\
	printf(ANSI_RESET);\
	printf("                                                      ");\
	ShowCursor();\
	SetConsoleCursorPosition(hOut,nowcdn);


//打印消息warning_printf
#define warprintf(fmt) \
	HideCursor();\
	SetConsoleCursorPosition(hOut,PRINT_SPACE_MESSAGE);\
	printf(ANSI_RED_BG"[消息]: ");\
	printf(fmt);\
	printf(ANSI_RESET);\
	printf("                                                      ");\
	ShowCursor();\
	SetConsoleCursorPosition(hOut,nowcdn);

class zombie;
class plant;
class bullet;

extern int plantNameLen[100];
extern zombie* zrec[5][10][7];
extern plant*  prec[5][10];
extern bullet* brec[42][132];//设定同一个格子至多有一个僵尸和一个植物,同一个像素点至多有一个子弹
extern int sun ;
extern int point ;
extern int timect ;
extern int curPlantNum;

#define normalPea(x,y)           PEA("豌豆",x,y,1,2)
#define icePea(x,y)              ICEPEA("冰豌豆",x,y,1,2)

//name,x,y,health,cost,interval
#define sunFlower(x,y)			 SUNFLOWER("向日葵",x,y,8,50,30)
#define peaShooter(x,y)          PEASHOOTER("豌豆射手",x,y,10,100,5)
#define wallNut(x,y)             WALLNUT("坚果",x,y,80,50,0)
#define icePeaShooter(x,y)       ICEPEASHOOTER("冰射手",x,y,10,175,5)
#define doublePeaShooter(x,y)	 DOUBLEPEASHOOTER("双发射手",x,y,10,200,5)
#define squash(x,y)              SQUASH("窝瓜",x,y,10000,50,0)
#define highNut(x,y)			 HIGHNUT("高坚果",x,y,200,125,0)
#define cherryBomb(x,y)			 CHERRYBOMB("樱桃炸弹",x,y,10000,150,2)
#define garlic(x,y)				 GARLIC("大蒜",x,y,20,50,0)
#define pumpkin(x,y)			 PUMPKIN("南瓜头",x,y,60,125,0)
//窝瓜.樱桃血量设置得很高是因为它们不会被瞬间啃掉

//name,x,y,k,health,attack,speed,bonus,(kind)
#define normalZombie(x,y,k)         zombie("僵尸",x,y,k,10,1,2,1,0)
#define coneHeadZombie(x,y,k)       zombie("路障僵尸",x,y,k,20,1,2,2,0)
#define bucketHeadZombie(x,y,k)     zombie("铁桶僵尸",x,y,k,40,1,2,3,0)//前三种看作一种僵尸
#define newspaperZombie(x,y,k)	    NewspaperZombie("读报僵尸",x,y,k,10,1,2,1)
#define poleVautingZombie(x,y,k)    PoleVaultingZombie("撑杆僵尸",x,y,k,15,1,3,2)
#define clownZombie(x,y,k)		    ClownZombie("小丑僵尸",x,y,k,20,1,2,3)
#define catapultZombie(x,y,k)	    CatapultZombie("投篮僵尸",x,y,k,30,1000,1,3);
#define basketball(x,y,k,tarx,tary) Basketball("篮球",x,y,k,10000,3,4,0,tarx,tary);
enum{KIND_SF,KIND_PS,KIND_WN,KIND_IPS,KIND_DPS,KIND_SQ,KIND_HN,KIND_CB,KIND_GLC,KIND_PPK};
enum{KIND_NZ,KIND_NPZ,KIND_PVZ,KIND_CZ,KIND_CPZ,KIND_BB};
void spaceComplement(int slen);
void HideCursor();
void ShowCursor();
void fail();