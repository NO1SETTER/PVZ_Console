#pragma once
#include "Common.h"

class zombie
{
protected:
	int x, y, k;//zrec[x][y]的第k个僵尸
	int health;
	int speed;//僵尸的速度是以像素点记的,坐标也是用像素点记的,但是输出时需要进行转化格子显示
	int attack;
	int kind;
	//也即[像素点区间]--->某一个y
	const int bonus;//击杀奖励
public:
	zombie();
	zombie(const char* _name, int _x, int _y,int _k,int _health, int _attack, int _speed,int _bonus,int kind);
	~zombie();

	virtual void bite(plant* plt);//hurt有可能更新地图
	virtual void hurt(int damage);
	virtual void move();
	virtual bool func() {
		return 0;
	}//返回func是否发动了技能
	virtual void dead();
	void decelerate(int val, int mode);
	void accelerate(int val, int mode);

	void printHP();
	void printID();
	void printStatus();
	void printPos();
	int  getHealth() const{ return health; }
	const char* name;
	const int id;//随机产生的编号,用于标识
	int status;//STAT_MOV,STAT_BITE
	

	friend class bullet;
	friend class PEA;
	friend class ICEPEA;
};

class NewspaperZombie:public zombie
{
public:
	bool func();
	NewspaperZombie(const char* _name, int _x, int _y, int _k, int _health, int _attack, int _speed, int _bonus) :
		zombie(_name,_x,_y,_k,_health,_attack,_speed,_bonus,1)
	{
		activated = 0;
	}
private:
	int activated;
};

class PoleVaultingZombie :public zombie
{
public:
	bool func();
	PoleVaultingZombie(const char* _name, int _x, int _y, int _k, int _health, int _attack, int _speed, int _bonus) :
		zombie(_name, _x, _y, _k, _health, _attack, _speed, _bonus,2)
	{
		activated = 0;
	}
private:
	int activated;
};

class  ClownZombie:public zombie
{
public:
	ClownZombie(const char* _name, int _x, int _y, int _k, int _health, int _attack, int _speed, int _bonus) :
		zombie(_name, _x, _y, _k, _health, _attack, _speed, _bonus,3)
	{
	}
	bool func();
	void dead();
};


class CatapultZombie:public zombie
{
public:
	CatapultZombie(const char* _name, int _x, int _y, int _k, int _health, int _attack, int _speed, int _bonus) :
		zombie(_name, _x, _y, _k, _health, _attack, _speed, _bonus,4)
	{
		status = STAT_WAIT;//投篮僵尸初始状态是wait
		ballNum = 10;
		counter = 6;
		tarX = _x;
		tarY = 0;//默认投掷目标
	}
	bool func();
private:
	int ballNum;
	int counter;
	int tarX, tarY;
};

class Basketball :public zombie//把投篮僵尸产生的篮球视作也是一种僵尸
{
public:
	Basketball(const char* _name, int _x, int _y, int _k, int _health, int _attack, int _speed, int _bonus,int _tarX,int _tarY) :
		zombie(_name, _x, _y, _k, _health, _attack, _speed, _bonus,5)
	{
		tarX = _tarX;
		tarY = _tarY;
	}
	bool func();
private:
	int tarX,tarY;//锁定目标
};

#define MODE_CHG 0
#define MODE_SET 1

zombie* generateZombies(int freq, int mode, int row, int k);
const char* decideColor(int health);
int findZombieSpace(int x, int y);//在[x][y]中找到一个空格子
int findZombie(int x, int y);//在[x][y]中找到一个最小有僵尸的k