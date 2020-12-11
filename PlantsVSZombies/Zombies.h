#pragma once
#include "Common.h"

class zombie
{
protected:
	int x, y, k;//zrec[x][y]�ĵ�k����ʬ
	int health;
	int speed;//��ʬ���ٶ��������ص�ǵ�,����Ҳ�������ص�ǵ�,�������ʱ��Ҫ����ת��������ʾ
	int attack;
	int kind;
	//Ҳ��[���ص�����]--->ĳһ��y
	const int bonus;//��ɱ����
public:
	zombie();
	zombie(const char* _name, int _x, int _y,int _k,int _health, int _attack, int _speed,int _bonus,int kind);
	~zombie();

	virtual void bite(plant* plt);//hurt�п��ܸ��µ�ͼ
	virtual void hurt(int damage);
	virtual void move();
	virtual bool func() {
		return 0;
	}//����func�Ƿ񷢶��˼���
	virtual void dead();
	void decelerate(int val, int mode);
	void accelerate(int val, int mode);

	void printHP();
	void printID();
	void printStatus();
	void printPos();
	int  getHealth() const{ return health; }
	const char* name;
	const int id;//��������ı��,���ڱ�ʶ
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
		status = STAT_WAIT;//Ͷ����ʬ��ʼ״̬��wait
		ballNum = 10;
		counter = 6;
		tarX = _x;
		tarY = 0;//Ĭ��Ͷ��Ŀ��
	}
	bool func();
private:
	int ballNum;
	int counter;
	int tarX, tarY;
};

class Basketball :public zombie//��Ͷ����ʬ��������������Ҳ��һ�ֽ�ʬ
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
	int tarX,tarY;//����Ŀ��
};

#define MODE_CHG 0
#define MODE_SET 1

zombie* generateZombies(int freq, int mode, int row, int k);
const char* decideColor(int health);
int findZombieSpace(int x, int y);//��[x][y]���ҵ�һ���ո���
int findZombie(int x, int y);//��[x][y]���ҵ�һ����С�н�ʬ��k