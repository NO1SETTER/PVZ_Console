#include"Grassland.h"



Grassland::Grassland()
{
	startx = starty  = x = y = 0;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}

Grassland::Grassland(int _x, int _y)
{
	x = _x;
	y = _y;
	startx = LatX(x) - 1;
	starty = LatY(y) - 1;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
}


void Grassland::printFrame()
{
	HideCursor();
	for (int i = 0; i < 14; i++)
	{
		SetConsoleCursorPosition(hOut, { (short)(starty + i),(short)(startx) });
		printf("*");
		SetConsoleCursorPosition(hOut, { (short)(starty + i),(short)(startx + 8) });
		printf("*");
	}

	for (int i = 2; i < 7; i++)
	{
		SetConsoleCursorPosition(hOut, { (short)starty,(short)(startx + i) });
		printf(" ");
		SetConsoleCursorPosition(hOut, { (short)(starty + 13), (short)(startx + i) });
		printf(" ");
	}
	SetConsoleCursorPosition(hOut, { (short)(starty), (short)(startx + 1) });
	printf("*");
	SetConsoleCursorPosition(hOut, { (short)(starty), (short)(startx + 7) });
	printf("*");
	SetConsoleCursorPosition(hOut, { (short)(starty + 13), (short)(startx + 1 ) });
	printf("*");
	SetConsoleCursorPosition(hOut, { (short)(starty + 13), (short)(startx + 7 ) });
	printf("*");
}

void Grassland::printPlant(int aim)
{
	assert(prec[x][y]);
	HideCursor();
	const char* bgcolor = aim ? ANSI_LIGHT_CYAN_BG : ANSI_BLACK_BG;
	if (prec[x][y]->getPumpkin())
	{
		SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + 1) });
		printf(ANSI_YELLOW"%s((%s%s" ANSI_YELLOW "))" ANSI_RESET,bgcolor,prec[x][y]->color,prec[x][y]->name);
		spaceComplement(strlen(prec[x][y]->name) + 4);
	}
	else
	{
		SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + 1) });
		printf("%s%s%s" ANSI_RESET,bgcolor, prec[x][y]->color,prec[x][y]->name);
		spaceComplement(strlen(prec[x][y]->name));
	}
	printf(ANSI_RESET);
	SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + 2) });
	prec[x][y]->printHP();
	for (int i = 3; i < 8; i++)
	{
		SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + i) });
		printf("            ");
	}
}

void Grassland::printZombie(int aim)
{
	assert(findZombie(x, y) != -1);
	HideCursor();
	int no = 0;
	const char* bgcolor = aim ? ANSI_LIGHT_CYAN_BG : ANSI_BLACK_BG;
	for (int i = 0; i < 7; i++)
	{
		if (zrec[x][y][i])
		{
			SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + no + 1) });
			const char* color = decideColor(zrec[x][y][i]->getHealth());
			printf("%s%s%s" ANSI_RESET,bgcolor, color, zrec[x][y][i]->name);
			spaceComplement(strlen(zrec[x][y][i]->name));
			no += 1;
		}
	}
	for (int i = no + 1; i < 8; i++)
	{
		SetConsoleCursorPosition(hOut, { (short)(starty + 1),(short)(startx + i) });
		printf("            ");
	}
}

void Grassland::printBullet(int aim)
{
	HideCursor();
	const char* bgcolor = aim ? ANSI_LIGHT_CYAN_BG : ANSI_BLACK_BG;
	for (int i = 1; i < 8; i++)
		for (int j = 0; j <= 13; j++)
		{
			SetConsoleCursorPosition(hOut, {(short)(starty + j),(short)(startx + i) });
			if (brec[startx + i][starty + j])
			{
				printf("%s%s@" ANSI_RESET, bgcolor, brec[startx + i][starty + j]->color);
			}
			else if (((i == 1) && (j == 0 || j == 13)) || ((i == 7) && (j == 0 || j == 13)))
				printf("*");
			else if (j != 0 && j != 13)
				printf("%s " ANSI_RESET, bgcolor);
			else
				printf(" ");
		}
}