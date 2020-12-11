#include "Zombies.h"
#include "Plants.h"


plant::plant():
	name("plant"),color(ANSI_GREEN),x(0),y(0),kind(-1),cost(0),interval(0),id(rand()%10000)
{
	health = 0;
	counter = 0;
	ppk = NULL;
}

plant::plant(const char* _name,const char* _color, int _x, int _y, int _kind, int _health, int _cost, int _interval):
	name(_name),color(_color),x(_x),y(_y),kind(_kind),cost(_cost),interval(_interval),id(rand()%10000)
{
	health = _health;
	counter = interval - 1;
	ppk = NULL;
}

plant::~plant()
{
}

void plant::hurt(int damage)
{
	health = health - damage;
	if (health <= 0)
		dead();
}

void plant::dead()
{
	prec[x][y] = NULL;
}

void plant::printHP()
{
	char buf[100];
	sprintf(buf, "HP:%d", health);
	printf(buf);
	spaceComplement(strlen(buf));
}

void plant::printID()
{
	char buf[100];
	sprintf(buf, "%d", id);
	printf(buf);
	spaceComplement(strlen(buf));
}

void plant::printPos()
{
	char buf[100];
	sprintf(buf, "[%d,%d]", x, y);
	printf(buf);
	spaceComplement(strlen(buf));
}

bool plant::addPumpkin(PUMPKIN* _ppk)//给它传一个空的也ok
{
	if (ppk) return 0;
	ppk = _ppk;
	return 1;
}

PUMPKIN* plant::getPumpkin()
{
	return ppk;
}

bool plant::removePumpkin()
{
	if (!ppk) return 0;
	ppk = NULL;
	return 1;
}

void SUNFLOWER::func()
{
	if (counter < interval)
	{
		counter += 1;
		return;
	}
	counter = 0;
	sun = sun + 50;
}

void PEASHOOTER::func()
{
	if (counter < interval)
	{
		counter += 1;
		return;
	}
	counter = 0;
	int xPos = 0;
	for (int i = 1; i < 6; i++)
	{
		if (brec[LatX(x) + i][LatY(y + 1)] == NULL)
		{
			xPos = i;
			break;
		}
	}
	brec[LatX(x) + xPos][LatY(y + 1)] = new normalPea(LatX(x) + xPos, LatY(y + 1));
}


void ICEPEASHOOTER::func()
{
	if (counter < interval)
	{
		counter += 1;
		return;
	}
	counter = 0;
	int xPos = 0;
	for (int i = 1; i < 6; i++)
	{
		if (brec[LatX(x) + i][LatY(y + 1)] == NULL)
		{
			xPos = i;
			break;
		}
	}
	brec[LatX(x) + xPos][LatY(y + 1)] = new icePea(LatX(x) + xPos, LatY(y + 1));
}

void DOUBLEPEASHOOTER::func()
{
	if (counter < interval)
	{
		counter += 1;
		return;
	}
	counter = 0;

	int xPos = 0;
	for (int i = 1; i < 6; i++)
	{
		if (brec[LatX(x) + i][LatY(y + 1)] == NULL)
		{
			xPos = i;
			break;
		}
	}
	brec[LatX(x) + xPos][LatY(y + 1)] = new normalPea(LatX(x) + xPos, LatY(y + 1));
	xPos = 0;
	for (int i = 1; i < 6; i++)
	{
		if (brec[LatX(x) + i][LatY(y + 1)] == NULL)
		{
			xPos = i;
			break;
		}
	}
	brec[LatX(x) + xPos][LatY(y + 1)] = new normalPea(LatX(x) + xPos, LatY(y + 1));
}

void SQUASH::func()
{
	if (findZombie(x, y) != -1)
	{
		for (int i = 0; i < 7; i++)
			if(zrec[x][y][i])
				zrec[x][y][i]->hurt(attack);
		
		prec[x][y] = NULL;
	}
	else if ((y + 1 < 10) && findZombie(x, y + 1) != -1 )
	{
		for (int i = 0; i < 7; i++)
			if (zrec[x][y + 1][i])
				zrec[x][y + 1][i]->hurt(attack);
		
		prec[x][y] = NULL;
	}
}

void CHERRYBOMB::func()
{
	if (counter < interval)
	{
		counter += 1;
		return;
	}

	prec[x][y] = NULL;
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = y - 1; j <= y + 1; j++)
		{
			if (!INRANGE(i, j)) continue;
			for (int k = 0; k < 7; k++)
			{
				if (zrec[i][j][k])
					zrec[i][j][k]->hurt(attack);
			}
		}
}

void PUMPKIN::dead()
{
	if (prec[x][y]->kind == KIND_PPK)
		prec[x][y] = NULL;
	else
		prec[x][y]->removePumpkin();
}

