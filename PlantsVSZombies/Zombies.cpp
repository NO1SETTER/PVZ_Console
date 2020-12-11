#include "Zombies.h"
#include "Plants.h"

zombie::zombie():
	name("Zombie"),attack(0),bonus(0),id(rand()%10000)
{
	x = 0;
	y = 0;
	k = 0;
	health = 0;
	speed = 0;
	status = STAT_MOV;
}

zombie::zombie(const char* _name,int _x,int _y,int _k, int _health, int _attack, int _speed,int _bonus,int _kind):
	name(_name),attack(_attack),bonus(_bonus),id(rand()%10000)
{
	x = _x;
	y = _y;
	k = _k;
	health = _health;
	speed = _speed;
	kind = _kind;
	status = STAT_MOV;
}

zombie::~zombie()
{
}

void zombie::bite(plant* plt)
{
	assert(status == STAT_BITE);
	if (plt->getPumpkin())
		plt->getPumpkin()->hurt(attack);
	else
		plt->hurt(attack);

	if (plt->kind == KIND_GLC)
	{
		zrec[x][NormY(y)][k] = NULL;
		if (x == 0)
		{
			x = x + 1;
			k = findZombieSpace(x, NormY(y));
		}
		else if(x == 4)
		{
			x = x - 1;
			k = findZombieSpace(x, NormY(y));
		}
		else
		{
			x = x + 2 * (rand() % 2) - 1;
			k = findZombieSpace(x, NormY(y));
		}
		zrec[x][NormY(y)][k] = this;
	}
	else;
}

void zombie::move()
{
	assert(status == STAT_MOV);
	zrec[x][NormY(y)][k]=NULL;
	int nextPos = y - speed;
	int realPos = y;
	for (; realPos >= nextPos; realPos--)
	{
		if (realPos < 0)  fail();
		int nowy = NormY(y);
		int nxty = NormY(realPos);//此时该像素点对应的格子
		if (nxty == nowy) continue;//仍在此前的格子中
		
		if (prec[x][nxty]) //前方有植物
		{
			status = STAT_BITE;
			break;
		}

		if (findZombieSpace(x ,nxty)==-1 )//前方有僵尸
		{
			status = STAT_WAIT;
			break;
		}

	}
	y = realPos+1;//正常移动
	k = findZombieSpace(x,NormY(y));
	zrec[x][NormY(y)][k] = this;
}

void zombie::hurt(int damage)
{
	health = health - damage;
	if (health <= 0)
		dead();
}

void zombie::dead()
{
	point = point + bonus;
	zrec[x][NormY(y)][k] = NULL;
}

void zombie::accelerate(int val, int mode)
{
	if (mode == MODE_CHG)
		speed = speed + val;
	else
		speed = val;
}

void zombie::decelerate(int val, int mode)
{
	if (mode == MODE_CHG)
		speed = max(1, speed - val);
	else
		speed = val;
}

void zombie::printHP()
{
	char buf[100];
	sprintf(buf, "HP:%d", health);
	printf(buf);
	spaceComplement(strlen(buf));
}

void zombie::printID()
{
	char buf[100];
	sprintf(buf,"%d", id);
	printf(buf);
	spaceComplement(strlen(buf));
}

void zombie::printPos()
{
	char buf[100];
	sprintf(buf, "[%d,%d,%d]", x,y,k);
	printf(buf);
	spaceComplement(strlen(buf));
}

void zombie::printStatus()
{
	switch (status)
	{
	case STAT_BITE:printf("Bite"); break;
	case STAT_MOV:printf("Move"); break;
	case STAT_WAIT:printf("Wait"); break;
	default:break;
	}
	spaceComplement(4);
}



bool NewspaperZombie::func()
{
	if (health <= 5 && !activated)
	{
		activated = 1;
		attack = attack * 2;
		accelerate(speed * 2, MODE_SET);
		return 1;
	}
	return 0;
}

bool PoleVaultingZombie:: func()
{
	int edgeY = LatY(NormY(y));
	int nextY = NormY(y) - 1;
	if (!activated && nextY != -1 && (y == edgeY - 1 || y == edgeY || y == edgeY + 1) && prec[x][nextY])
	//    没跳过    并且   不是在第一格     并且     到达本格边缘                                      前一格有植物
	{
		activated = 1;
		assert(nextY >= 0);
		if (prec[x][nextY] && prec[x][nextY]->kind == KIND_HN) return 1;//高坚果,直接拦住
		int nextK = findZombieSpace(x, nextY);
		zrec[x][NormY(y)][k] = NULL;
		y = LatY(nextY);
		k = nextK;
		zrec[x][NormY(y)][k] = this;
		return 1;
	}
	return 0;
}


bool ClownZombie::func()
{
	if (rand() % 20 == 3)
	{
		dead();
		return 1;
	}
	return 0;
}

void ClownZombie::dead()
{
	point = point + bonus;
	zrec[x][NormY(y)][k] = NULL;
	for (int i = x - 1; i <= x + 1; i++)
		for (int j = NormY(y) - 1; j <= NormY(y) + 1; j++)
		{
			if (!INRANGE(i, j)) continue;
			if (!prec[i][j]) continue;
			if (prec[i][j]->getPumpkin())
				prec[i][j]->getPumpkin()->hurt(50);
			else
				prec[i][j]->hurt(50);//设定南瓜头能挡住爆炸伤害
		}
}

bool CatapultZombie::func()
{

	if (ballNum&&status==STAT_WAIT)
	{
		if (counter > 0)
			counter--;
		else
		{
			counter = 6;
			if (!prec[tarX][tarY])
			{
				tarY = -1;
				for (int i = 0; i < NormY(y); i++)
				{
					if (prec[x][i])
					{
						tarY = i; break;
					}
				}
			}
			if (tarY != -1)
			{
				int k = findZombieSpace(x, NormY(y) - 1);
				zrec[x][NormY(y) - 1][k] = new basketball(x, LatY(NormY(y)) - 2, k, tarX, tarY);
				ballNum--;
			}
			else
				status = STAT_MOV;//此后不再停下来投篮
		}
		return 1;
	}
	return 0;
}

bool Basketball::func()//综合移动和伤害的函数,Basketball的移动不通过move实现
{
	zrec[x][NormY(y)][k] = NULL;
	y = y - speed;
	k = findZombieSpace(x, NormY(y));
	zrec[x][NormY(y)][k] = this;
	if (x == tarX && NormY(y) == tarY)
	{
		if (prec[tarX][tarY])
		{
			status = STAT_BITE;
			bite(prec[tarX][tarY]);
		}
			
		dead();
	}
	return 1;
}


zombie* generateZombies(int freq, int mode, int row, int k)
{
	assert(freq >= 10);
	if (timect <= 120)// 100%普通僵尸
	{
		if (rand() % freq == 0)
			return new normalZombie(row, 129, k);
	}
	else if (timect > 120 && timect <= 240)// 70%普通僵尸,20%读报僵尸, 10%路障僵尸
	{
		if (rand() % (int)(0.75 * freq) == 0)
		{
			int temp = rand() % 10;
			switch (temp)
			{
			case 0:return new coneHeadZombie(row, 129, k); 
			case 1:case 2:return new newspaperZombie(row, 129, k); 
			default: return new normalZombie(row, 129, k); 
			}
		}
	}
	else if (timect >= 240)
	{
		if (rand() % (int)(0.5 * freq) == 0)//40%普通僵尸,20%读报僵尸,20%路障僵尸,10%铁桶僵尸,5%投篮僵尸,5%小丑僵尸
		{
			int temp = rand() % 20;
			switch (temp)
			{
			case 0:return new catapultZombie(row, 129, k);
			case 1:return new clownZombie(row, 129, k);
			case 2:case 3:return new bucketHeadZombie(row, 129, k);
			case 4:case 5:case 6:case 7:return new coneHeadZombie(row, 129, k);
			case 8:case 9:case 10:case 11:return new newspaperZombie(row, 129, k);
			default:return new normalZombie(row, 129, k);
			}
		}
	}
	return NULL;
}  


const char* decideColor(int health)
{
	if (health > 200) return ANSI_LIGHT_MAGENTA;
	if (health <= 200 && health > 150) return ANSI_MAGENTA;
	if (health <= 150 && health > 100) return ANSI_LIGHT_BLUE;
	if (health <= 100 && health > 50)  return ANSI_BLUE;
	if (health <= 50  && health > 35)  return ANSI_LIGHT_CYAN;
	if (health <= 35  && health > 25)  return ANSI_CYAN;
	if (health <= 25  && health > 15)  return ANSI_LIGHT_YELLOW;
	if (health <= 15  && health > 10)  return ANSI_YELLOW;
	if (health <= 10  && health > 5)   return ANSI_LIGHT_RED;
	if (health <= 5) return ANSI_RED;
	return NULL;
}

int findZombieSpace(int x, int y)
{
	for (int i = 0; i < 7; i++)
	{
		if (zrec[x][y][i] == NULL)
			return i;
	}
	return -1;
}

int findZombie(int x, int y)
{
	for (int i = 0; i < 7; i++)
	{
		if (zrec[x][y][i])
			return i;
	}
	return -1;
}