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

#define STAT_MOV  0//�н������谭
#define STAT_BITE 1//��ֲ��,ͣ������
#define STAT_WAIT 2//�н�ʬ,�ȴ�

//(5+1)*(8+1) --> (7+1)*(12+1)
inline short NormX(int x) { return x / 8;}
inline short NormY(int y) { return y / 13; }   //�����ĸ�����
inline short LatX(int x)  {return 8*x + 1;}
inline short LatY(int y)  {return 13*y + 1;}  //�����ĸ�����


//��ӡ��Ϣmessage_printf
#define mprintf(fmt) \
	HideCursor();\
	SetConsoleCursorPosition(hOut,PRINT_SPACE_MESSAGE);\
	printf(ANSI_GREEN_BG"[��Ϣ]: ");\
	printf(fmt);\
	printf(ANSI_RESET);\
	printf("                                                      ");\
	ShowCursor();\
	SetConsoleCursorPosition(hOut,nowcdn);


//��ӡ��Ϣwarning_printf
#define warprintf(fmt) \
	HideCursor();\
	SetConsoleCursorPosition(hOut,PRINT_SPACE_MESSAGE);\
	printf(ANSI_RED_BG"[��Ϣ]: ");\
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
extern bullet* brec[42][132];//�趨ͬһ������������һ����ʬ��һ��ֲ��,ͬһ�����ص�������һ���ӵ�
extern int sun ;
extern int point ;
extern int timect ;
extern int curPlantNum;

#define normalPea(x,y)           PEA("�㶹",x,y,1,2)
#define icePea(x,y)              ICEPEA("���㶹",x,y,1,2)

//name,x,y,health,cost,interval
#define sunFlower(x,y)			 SUNFLOWER("���տ�",x,y,8,50,30)
#define peaShooter(x,y)          PEASHOOTER("�㶹����",x,y,10,100,5)
#define wallNut(x,y)             WALLNUT("���",x,y,80,50,0)
#define icePeaShooter(x,y)       ICEPEASHOOTER("������",x,y,10,175,5)
#define doublePeaShooter(x,y)	 DOUBLEPEASHOOTER("˫������",x,y,10,200,5)
#define squash(x,y)              SQUASH("�ѹ�",x,y,10000,50,0)
#define highNut(x,y)			 HIGHNUT("�߼��",x,y,200,125,0)
#define cherryBomb(x,y)			 CHERRYBOMB("ӣ��ը��",x,y,10000,150,2)
#define garlic(x,y)				 GARLIC("����",x,y,20,50,0)
#define pumpkin(x,y)			 PUMPKIN("�Ϲ�ͷ",x,y,60,125,0)
//�ѹ�.ӣ��Ѫ�����õúܸ�����Ϊ���ǲ��ᱻ˲��е�

//name,x,y,k,health,attack,speed,bonus,(kind)
#define normalZombie(x,y,k)         zombie("��ʬ",x,y,k,10,1,2,1,0)
#define coneHeadZombie(x,y,k)       zombie("·�Ͻ�ʬ",x,y,k,20,1,2,2,0)
#define bucketHeadZombie(x,y,k)     zombie("��Ͱ��ʬ",x,y,k,40,1,2,3,0)//ǰ���ֿ���һ�ֽ�ʬ
#define newspaperZombie(x,y,k)	    NewspaperZombie("������ʬ",x,y,k,10,1,2,1)
#define poleVautingZombie(x,y,k)    PoleVaultingZombie("�Ÿ˽�ʬ",x,y,k,15,1,3,2)
#define clownZombie(x,y,k)		    ClownZombie("С��ʬ",x,y,k,20,1,2,3)
#define catapultZombie(x,y,k)	    CatapultZombie("Ͷ����ʬ",x,y,k,30,1000,1,3);
#define basketball(x,y,k,tarx,tary) Basketball("����",x,y,k,10000,3,4,0,tarx,tary);
enum{KIND_SF,KIND_PS,KIND_WN,KIND_IPS,KIND_DPS,KIND_SQ,KIND_HN,KIND_CB,KIND_GLC,KIND_PPK};
enum{KIND_NZ,KIND_NPZ,KIND_PVZ,KIND_CZ,KIND_CPZ,KIND_BB};
void spaceComplement(int slen);
void HideCursor();
void ShowCursor();
void fail();