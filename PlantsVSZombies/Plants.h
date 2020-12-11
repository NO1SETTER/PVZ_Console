#pragma once
#include "Bullet.h"
#include "Common.h"

class PUMPKIN;
class plant
{
	
protected:
	const int  x, y;
	int health;

	const int interval;//作用间隔,如产生子弹,产生阳光
	int	counter;//对应interval的计数器
	
	PUMPKIN* ppk;//南瓜头指针
public:
	plant();
	plant(const char* _name,const char* _color,int _x,int _y,int _kind,int _health,int _cost,int _interval);
	~ plant();

	void hurt(int damage);//hurt有可能更新地图
	virtual void dead();
	virtual void func(){}
	void printHP();
	void printID();
	void printPos();

	const char* name;
	const char* color;
	const int  id;
	const int  cost;
	const int  kind;//用于指示派生类的类别

	bool addPumpkin(PUMPKIN* _ppk);
	PUMPKIN* getPumpkin();
	bool removePumpkin();
};

class SUNFLOWER : public plant
{
public:
	void func();
	SUNFLOWER(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name,ANSI_LIGHT_YELLOW, _x, _y, 0, _health, _cost, _interval)
	{
	}
};

class PEASHOOTER :public plant
{
public:
	void func();
	PEASHOOTER(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name,ANSI_GREEN, _x, _y, 1 ,_health,_cost,_interval)
	{
	}
};

class WALLNUT : public plant
{
public:
	WALLNUT(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name,ANSI_YELLOW, _x, _y, 2, _health, _cost, _interval)
	{
	}
};

class ICEPEASHOOTER :public plant
{
public:
	void func();
	ICEPEASHOOTER(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name,ANSI_LIGHT_BLUE, _x, _y, 3, _health, _cost, _interval)
	{
	}
};

class DOUBLEPEASHOOTER :public plant
{
public:
	void func();
	DOUBLEPEASHOOTER(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name,ANSI_GREEN, _x, _y, 4, _health, _cost, _interval)
	{
	}
};

class SQUASH : public plant
{
public:
	void func();
	SQUASH(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name, ANSI_LIGHT_CYAN, _x, _y, 5, _health, _cost, _interval)
	{
		attack = 80;
	}
private:
	int attack;
};

class HIGHNUT: public plant
{
public:
	HIGHNUT(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name, ANSI_YELLOW, _x, _y, 6, _health, _cost, _interval)
	{
	}
};

class CHERRYBOMB : public plant
{
public:
	void func();
	CHERRYBOMB(const char* _name, int _x, int _y, int _health, int _cost, int _interval):
		plant(_name, ANSI_RED, _x, _y, 7, _health, _cost, _interval)
	{
		attack = 80;
	}
private:
	int attack;
};


class GARLIC: public plant
{
public:
	GARLIC(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name, ANSI_LIGHT_CYAN, _x, _y, 8, _health, _cost, _interval)
	{
	}
};


class PUMPKIN :public plant
{
public:
	PUMPKIN(const char* _name, int _x, int _y, int _health, int _cost, int _interval) :
		plant(_name, ANSI_YELLOW, _x, _y, 9, _health, _cost, _interval)
	{
	}
private:
	void dead();
};




