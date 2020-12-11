#pragma once
#include "Zombies.h"
#include "Common.h"

class bullet
{
protected:
	int x, y;//x,y�������ص��(��Ȼ��ôת�������������!! )
	const int attack;
	const int speed;//�ӵ����ٶ��������ص�ǵ�,����Ҳ�������ص�ǵ�,���ʱֱ�Ӱ����ص������ʾ
public:
	bullet();
	bullet(const char* _name,const char* color,int _x,int _y, int _kind,int _attack, int _speed);
	~bullet();
	zombie* move();

	const char* name;
	const char* color;
	const int kind;//����ָʾ����������
	const int id;//��������ı��,���ڱ�ʶ
};

class PEA :public bullet
{
public:
	void explode(zombie* zb);
	PEA(const char* _name, int _x, int _y, int _attack, int _speed) :
		bullet(_name,ANSI_LIGHT_GREEN, _x, _y, 0, _attack, _speed)
	{
	}
};

class ICEPEA :public bullet
{
public:
	void explode(zombie* zb);
	ICEPEA(const char* _name, int _x, int _y, int _attack, int _speed) :
		bullet(_name,ANSI_LIGHT_CYAN, _x, _y, 1, _attack, _speed)
	{
	}
};

