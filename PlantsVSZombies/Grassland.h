#pragma once
#include<conio.h>
#include<windows.h>
#include"Color.h"
#include"Common.h"
#include"Plants.h"

// h:9 w:14
class Grassland
{
public:
	Grassland();
	Grassland(int _x, int _y);
	void printFrame();
	void printPlant(int aim);
	void printZombie(int aim);
	void printBullet(int aim);
private:
	int x, y;//�ڲݵ��е�����
	int startx, starty;//���Ͻǵ��������
	HANDLE hOut;
};

