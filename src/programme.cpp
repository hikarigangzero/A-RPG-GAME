#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NON_CONFORMING_SWPRINTFS

#include<iostream>
#include<graphics.h>
#include<easyx.h>
#include<mmsystem.h>
#include<string>
#include<tchar.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <wchar.h>
#include <fstream>

#pragma comment(lib, "winmm.lib")
using namespace std;

#include"fightgame.h"

int background::smalllength = 64;
int background::smallwidth = 20;
int background::maintextlength = 64;
int background::maintextwidth = 20;
uniform_int_distribution<int> game::dist_type(0, 9);
uniform_int_distribution<int> game::dist_a(0, map_s - 1);
uniform_int_distribution<int> game::dist_b(0, map_r - 1);
uniform_int_distribution<int> game::dist_m(1, 4);
uniform_int_distribution<int> game::dist_bull(1, 4);

//background类函数定义
//开启窗口
void background::setbegin()
{
	initgraph(1280, 720);
	cleardevice();
	mciSendString(L"open .\\source\\RhythmQuest.mp3", 0, 0, 0);
	mciSendString(L"play .\\source\\RhythmQuest.mp3 repeat", 0, 0, 0);

	background::setbackground();
}

//设置主界面背景的白色实心矩形
void background::setbgRectangle()
{
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	rectangle(0, 0, 1280, 720);
	solidrectangle(0, 0, 1280, 720);
}

//设置角色选择界面背景纯色
void background::playerchooseRectangle_one()
{
	//褐色153,51,0 
	setfillcolor(RGB(120, 67, 21));
	setlinecolor(RGB(120, 67, 21));
	rectangle(0, 0, 1280, 720);
	solidrectangle(0, 0, 1280, 720);
}

//设置选择框纯色背景1
void background::playerchooseRectangle_two()
{
	setfillcolor(BLACK);
	setlinecolor(WHITE);
	solidrectangle(900, 150, 1060, 270);
	rectangle(900, 150, 1060, 270);
}

//设置选择框纯色背景2
void background::playerchooseRectangle_three()
{
	setfillcolor(WHITE);
	setlinecolor(WHITE);
	rectangle(850, 320, 1095, 640);
	solidrectangle(850, 320, 1095, 640);
}

//设置按钮图标
void background::playerchoosebutton()
{
	setfillcolor(RGB(249, 99, 201));
	fillellipse(860, 550, 860 + 100, 550 + 80);
	fillellipse(980, 550, 980 + 100, 550 + 80);
}

//设置主界面文字
void background::setbgWord()
{
	settextcolor(RGB(255, 255, 255));
	settextstyle(128, 40, _T("黑体"));
	const wchar_t* str = L"像素战争";
	TCHAR* tstr = new TCHAR[wcslen(str) + 1];
	wcscpy_s(tstr, wcslen(str) + 1, str);
	int width = textwidth(str);
	int x = (getmaxx() - width) / 2;
	int y = 100;
	outtextxy(x, y, str);

	setfillcolor(RGB(249,99,201));  // 设置填充颜色为桃红色R=249，G=99，B=201
	int x1 = 200;
	int y1 = 420;
	settextcolor(RGB(255, 255, 255));
	settextstyle(maintextlength, maintextwidth, _T("黑体"));
	const wchar_t* str1 = L"开始";
	// 获取字符串的范围
	smallwidth = textheight(str1);
	smalllength = textwidth(str1);
	fillellipse(x1, y1, x1 + smalllength, y1 + smallwidth);
	setbkmode(TRANSPARENT);
	outtextxy(x1, y1, str1);

	setfillcolor(RGB(249, 99, 201));
	int x2 = 400;
	int y2 = 420;
	fillellipse(x2, y2, x2 + smalllength, y2 + smallwidth);
	settextcolor(RGB(255, 255, 255));
	settextstyle(maintextlength, maintextwidth, _T("黑体"));
	const wchar_t* str2 = L"读档";
	setbkmode(TRANSPARENT);
	outtextxy(x2, y2, str2);

	setfillcolor(RGB(249, 99, 201));
	int x3 = 600;
	int y3 = 420;
	fillellipse(x3, y3, x3 + smalllength, y3 + smallwidth);
	settextcolor(RGB(255, 255, 255));
	settextstyle(maintextlength, maintextwidth, _T("黑体"));
	const wchar_t* str3 = L"设置";
	setbkmode(TRANSPARENT);
	outtextxy(x3, y3, str3);

	setfillcolor(RGB(249, 99, 201));
	int x4 = 800;
	int y4 = 420;
	fillellipse(x4, y4, x4 + smalllength, y4 + smallwidth);
	settextcolor(RGB(255, 255, 255));
	settextstyle(maintextlength, maintextwidth, _T("黑体"));
	const wchar_t* str4 = L"退出";
	setbkmode(TRANSPARENT);
	outtextxy(x4, y4, str4);

	setfillcolor(RGB(249, 99, 201));
	int x5 = 1000;
	int y5 = 420;
	fillellipse(x5, y5, x5 + smalllength, y5 + smallwidth);
	settextcolor(RGB(255, 255, 255));
	settextstyle(maintextlength, maintextwidth, _T("黑体"));
	const wchar_t* str5 = L"帮助";
	setbkmode(TRANSPARENT);
	outtextxy(x5, y5, str5);
}

//设置主界面图片
void background::setbgpic()
{
	IMAGE img;
	loadimage(&img, _T(".\\source\\menubackground.png"));
	putimage(0, 0, &img);
}

//设置背景
void background::setbackground()
{
	background::setbgRectangle();
	background::setbgpic();
	background::setbgWord();
}

//设置过场图
void background::loadingpic()
{
	IMAGE img;
	loadimage(&img, _T(".\\source\\loading.png"));
	putimage(0, 0, &img);
}

//设置角色选择界面图片
void background::playerchoosepic()
{
	IMAGE img;
	loadimage(&img, _T(".\\source\\characterchoose.png"));
	putimage(154, 0, &img);
}

//设置战斗界面背景
void background::setfightbg()
{
	BeginBatchDraw();
	IMAGE backgroundBuffer(1280, 720);
	background::setbgRectangle();
	srand(static_cast<unsigned int>(time(NULL)));//初始化随机数种子
	IMAGE imgs[4];//草地
	loadimage(&imgs[0], _T(".\\source\\fightbkg\\floor1\\1.png"));
	loadimage(&imgs[1], _T(".\\source\\fightbkg\\floor1\\2.png"));
	loadimage(&imgs[2], _T(".\\source\\fightbkg\\floor1\\3.png"));
	loadimage(&imgs[3], _T(".\\source\\fightbkg\\floor1\\4.png"));
	for (int i = 0; i < map_s; i++)
	{
		for (int j = 0; j < map_r; j++)
		{
			int index = rand() % 4;
			putimage(0+mm*i, 0+mm*j, &imgs[index]);
		}
	}
	IMAGE imgs_s[3];//墙
	loadimage(&imgs_s[0], _T(".\\source\\fightbkg\\wall\\stone.png"));
	loadimage(&imgs_s[1], _T(".\\source\\fightbkg\\floor1\\startpoint.png"));
	loadimage(&imgs_s[2], _T(".\\source\\fightbkg\\floor1\\huifu.png"));

	for (int i = 0; i < map_r; i++)
	{
		for (int j = 0; j < map_s; j++)
		{
			if (map_size[i][j] == 1)
			{
				putimage(mm * j, mm * i, &imgs_s[0]);
			}
			else if (map_size[i][j] == 2)
			{
				putimage(mm * j, mm * i, &imgs_s[1]);
			}
			else if (map_size[i][j] == 3)
			{
				putimage(mm * j, mm * i, &imgs_s[2]);
			}
		}
	}
	EndBatchDraw();
	FlushBatchDraw();
	saveimage(_T(".\\source\\record\\background.png"));
}

//初始化战斗界面背景上凸起建筑
int background::map_size[map_r][map_s] =
{
	//1墙,2出生点,3恢复蓝的地方
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,1,1,0,1,0,0,0,1,0,0,0,1,0,1,1,0,0,1,1,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,2,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,3,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,1},
	{1,0,0,0,1,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

//cmdcontrol类函数定义
//主菜单界面控制
void cmdcontrol::mainneumctrl()
{
	while (true)
	{
		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			// 判断鼠标点击是否在指定范围内
			if (msg.uMsg == WM_LBUTTONDOWN &&
				msg.x >= 200 && msg.x <= (200+ background::smalllength) &&
				msg.y >= 420 && msg.y <= (420+ background::smallwidth))
			{
				if (cmdHead.startGame() == 0)
				{
					background::setbackground();
				}
			}
			else if (msg.uMsg == WM_LBUTTONDOWN &&
				msg.x >= 400 && msg.x <= (400 + background::smalllength) &&
				msg.y >= 420 && msg.y <= (420 + background::smallwidth))
			{
				//读档接口
				if (cmdHead.goonGame() == 0)
				{
					background::setbackground();
				}
			}
			else if (msg.uMsg == WM_LBUTTONDOWN &&
				msg.x >= 600 && msg.x <= (600 + background::smalllength) &&
				msg.y >= 420 && msg.y <= (420 + background::smallwidth))
			{
				//设置接口
				//无需设置，未来需要再完善
				while (true)
				{
					BeginBatchDraw();
					setfillcolor(WHITE);
					setlinecolor(WHITE);
					rectangle(0, 0, 1280, 720);
					solidrectangle(0, 0, 1280, 720);
					int xx = 200;
					int yy = 220;
					settextcolor(BLACK);
					settextstyle(64, 16, _T("黑体"));
					const wchar_t* strd = L"这个游戏暂时不需要这个功能";
					setbkmode(TRANSPARENT);
					outtextxy(xx, yy, strd);

					setlinecolor(BLACK);
					setfillcolor(RED);
					rectangle(980, 650, 980 + 100, 650 + 80);
					solidrectangle(980, 650, 980 + 100, 650 + 80);
					settextcolor(BLACK);
					settextstyle(background::maintextlength - 32, background::maintextwidth - 10, _T("黑体"));
					const wchar_t* strLS4 = L"返回";
					setbkmode(TRANSPARENT);
					outtextxy(1010, 673, strLS4);

					FlushBatchDraw();
					if (MouseHit())
					{
						MOUSEMSG msgee = GetMouseMsg();
						if (msgee.uMsg == WM_LBUTTONDOWN &&
							msgee.x >= 980 && msgee.x <= (980 + 100) &&
							msgee.y >= 650 && msgee.y <= (650 + 80))
						{
							break;
						}
					}
				}
				EndBatchDraw();
				background::setbackground();
			}
			else if (msg.uMsg == WM_LBUTTONDOWN &&
				msg.x >= 800 && msg.x <= (800 + background::smalllength) &&
				msg.y >= 420 && msg.y <= (420 + background::smallwidth))
			{
				exit(0);
			}
			else if (msg.uMsg == WM_LBUTTONDOWN &&
				msg.x >= 1000 && msg.x <= (1000 + background::smalllength) &&
				msg.y >= 420 && msg.y <= (420 + background::smallwidth))
			{
				//帮助接口
				while (true)
				{
					BeginBatchDraw();
					setfillcolor(WHITE);
					setlinecolor(WHITE);
					rectangle(0, 0, 1280, 720);
					solidrectangle(0, 0, 1280, 720);
					int xx = 100;
					int yy = 220;
					settextcolor(BLACK);
					settextstyle(64, 16, _T("黑体"));
					const wchar_t* str = L"上下左右控制移动，Z进行攻击，X发动技能，地图上的蓝色区域停留可恢复SP";
					const wchar_t* stree = L"然后就没有然后了";
					setbkmode(TRANSPARENT);
					outtextxy(xx, yy, str);
					outtextxy(xx, yy+3*mm, stree);

					setlinecolor(BLACK);
					setfillcolor(RED);
					rectangle(980, 650, 980 + 100, 650 + 80);
					solidrectangle(980, 650, 980 + 100, 650 + 80);
					settextcolor(BLACK);
					settextstyle(background::maintextlength - 32, background::maintextwidth - 10, _T("黑体"));
					const wchar_t* strLS3 = L"返回";
					setbkmode(TRANSPARENT);
					outtextxy(1010, 673, strLS3);

					FlushBatchDraw();
					if (MouseHit())
					{
						MOUSEMSG msghelp = GetMouseMsg();
						if (msghelp.uMsg == WM_LBUTTONDOWN &&
							msghelp.x >= 980 && msghelp.x <= (980 + 100) &&
							msghelp.y >= 650 && msghelp.y <= (650 + 80))
						{
							break;
						}
					}
				}
				EndBatchDraw();
				background::setbackground();
			}
		}
	}
}

//game类函数定义
//开始游戏
int game::startGame()
{
	background::loadingpic();
	Sleep(3000);
	int a = game::playerchoose();
	if (a == 0)
	{
		return 0;
	}
	else if (a == 1)
	{
		//选择角色1开始游戏的接口
		rng.seed(std::random_device()());
		background::setfightbg();
		IMAGE imgrcd;
		loadimage(&imgrcd, _T(".\\source\\record\\background.png"));
		person.playerconfirm(a - 1);
		person.loadingPlayer();
		this->loadingmonster();
		person.drawinplace();
		BeginBatchDraw();
		int c = 1;
		int e = 0;
		while (true)
		{
			int b = person.playerMove(8,background::map_size);
			putimage(0, 0, &imgrcd);
			this->coutRmessage();

			static DWORD t1, t2;
			if (t2 - t1 > 500)
			{
				this->monsterCreate();
				this->monsterAction(32, background::map_size);
				e=this->mst2ACT();
				t1 = t2;
			}
			t2 = clock();
			this->ms2ACTmove(e, 4, background::map_size);
			this->drawEnemy();

			static DWORD t5, t6;
			if (t6 - t5 > 2000)
			{
				this->mstACTjudge(background::map_size);
				t5 = t6;
			}
			t6 = clock();

			c = person.drawPlayer(b, c);
			int d = 0;
			static DWORD t3, t4;
			if (t4 - t3 > 500)
			{
				d = person.playerattack(c);
				t3 = t4;
			}
			t4 = clock();
			this->pyerACTjudge1(d);

			static DWORD t7, t8;
			if (t8 - t7 > 5000)
			{
				person.SPadd();
				t7 = t8;
			}
			t8 = clock();

			FlushBatchDraw();
			Sleep(20);

			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 12 * mm) && msg.y <= (mm + 12 * mm + 2 * mm))
				{
					//存档
					ofstream fp;
					fp.open(".\\source\\save\\save.dat", ios::binary | ios::out);
					fp.write((char*)&person.strcfm, sizeof(playerData));
					fp.close();
				}
				else if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 15 * mm) && msg.y <= (mm + 15 * mm + 2 * mm))
				{
					break;
				}
			}
			if (person.strcfm.HP <= 0)
			{
				setfillcolor(WHITE);
				setlinecolor(WHITE);
				rectangle(0, 0, 1280, 720);
				solidrectangle(0, 0, 1280, 720);
				int xx = 300;
				int yy = 250;
				settextcolor(BLACK);
				settextstyle(128, 32, _T("黑体"));
				const wchar_t* strf = L"角色阵亡，游戏结束";
				setbkmode(TRANSPARENT);
				outtextxy(xx, yy, strf);
				FlushBatchDraw();
				Sleep(2000);
				break;
			}
		}
		EndBatchDraw();
		return 0;
	}
	else if (a == 2)
	{
		//选择角色2开始游戏的接口
		rng.seed(std::random_device()());
		background::setfightbg();
		IMAGE imgrcd;
		loadimage(&imgrcd, _T(".\\source\\record\\background.png"));
		person.playerconfirm(a - 1);
		person.loadingPlayer2();
		this->loadingmonster();
		person.drawinplace();
		BeginBatchDraw();
		int c = 1;
		int e = 0;

		while (true)
		{
			int b = person.playerMove(8, background::map_size);
			putimage(0, 0, &imgrcd);
			this->coutRmessage();

			static DWORD t1, t2;
			if (t2 - t1 > 500)
			{
				this->monsterCreate();
				this->monsterAction(32, background::map_size);
				e = this->mst2ACT();
				t1 = t2;
			}
			t2 = clock();
			this->ms2ACTmove(e, 4, background::map_size);
			this->drawEnemy();

			static DWORD t5, t6;
			if (t6 - t5 > 2000)
			{
				this->mstACTjudge(background::map_size);
				t5 = t6;
			}
			t6 = clock();

			c = person.drawPlayer(b, c);
			int d = 0;
			static DWORD t3, t4;
			if (t4 - t3 > 500)
			{
				d = person.playerattack2(c);//差分
				this->person2ACT(d, 8);
				t3 = t4;
			}
			t4 = clock();
			this->pyerACTjudge2(8);

			static DWORD t7, t8;
			if (t8 - t7 > 5000)
			{
				person.SPadd();
				t7 = t8;
			}
			t8 = clock();

			FlushBatchDraw();
			Sleep(20);

			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 12 * mm) && msg.y <= (mm + 12 * mm + 2 * mm))
				{
					//存档
					ofstream fp;
					fp.open(".\\source\\save\\save.dat", ios::binary | ios::out);
					fp.write((char*)&person.strcfm, sizeof(playerData));
					fp.close();
				}
				else if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 15 * mm) && msg.y <= (mm + 15 * mm + 2 * mm))
				{
					break;
				}
			}
			if (person.strcfm.HP <= 0)
			{
				setfillcolor(WHITE);
				setlinecolor(WHITE);
				rectangle(0, 0, 1280, 720);
				solidrectangle(0, 0, 1280, 720);
				int xx = 300;
				int yy = 250;
				settextcolor(BLACK);
				settextstyle(128, 32, _T("黑体"));
				const wchar_t* strf = L"角色阵亡，游戏结束";
				setbkmode(TRANSPARENT);
				outtextxy(xx, yy, strf);
				FlushBatchDraw();
				Sleep(2000);
				break;
			}
		}
		EndBatchDraw();
		return 0;
	}
}

//读档开始游戏
int game::goonGame()
{
	background::loadingpic();
	Sleep(3000);
	ifstream fp;
	fp.open(".\\source\\save\\save.dat", ios::binary | ios::in);
	fp.read((char*)&person.strcfm, sizeof(playerData));
	fp.close();
	int a = this->playerjudge();
	if (a == 0)
	{
		return 0;
	}
	else if (a == 1)
	{
		rng.seed(std::random_device()());
		IMAGE imgrcd;
		loadimage(&imgrcd, _T(".\\source\\record\\background.png"));
		person.loadingPlayer();
		this->loadingmonster();
		person.drawinplace();
		BeginBatchDraw();
		int c = 1;
		int e = 0;
		while (true)
		{
			int b = person.playerMove(8, background::map_size);
			putimage(0, 0, &imgrcd);
			this->coutRmessage();

			static DWORD t1, t2;
			if (t2 - t1 > 500)
			{
				this->monsterCreate();
				this->monsterAction(32, background::map_size);
				e = this->mst2ACT();
				t1 = t2;
			}
			t2 = clock();
			this->ms2ACTmove(e, 4, background::map_size);
			this->drawEnemy();

			static DWORD t5, t6;
			if (t6 - t5 > 2000)
			{
				this->mstACTjudge(background::map_size);
				t5 = t6;
			}
			t6 = clock();

			c = person.drawPlayer(b, c);
			int d = 0;
			static DWORD t3, t4;
			if (t4 - t3 > 500)
			{
				d = person.playerattack(c);
				t3 = t4;
			}
			t4 = clock();
			this->pyerACTjudge1(d);

			static DWORD t7, t8;
			if (t8 - t7 > 5000)
			{
				person.SPadd();
				t7 = t8;
			}
			t8 = clock();

			FlushBatchDraw();
			Sleep(20);

			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 12 * mm) && msg.y <= (mm + 12 * mm + 2 * mm))
				{
					//存档
					ofstream fp;
					fp.open(".\\source\\save\\save.dat", ios::binary | ios::out);
					fp.write((char*)&person.strcfm, sizeof(playerData));
					fp.close();
				}
				else if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 15 * mm) && msg.y <= (mm + 15 * mm + 2 * mm))
				{
					break;
				}
			}
			if (person.strcfm.HP <= 0)
			{
				setfillcolor(WHITE);
				setlinecolor(WHITE);
				rectangle(0, 0, 1280, 720);
				solidrectangle(0, 0, 1280, 720);
				int xx = 300;
				int yy = 250;
				settextcolor(BLACK);
				settextstyle(128, 32, _T("黑体"));
				const wchar_t* strf = L"角色阵亡，游戏结束";
				setbkmode(TRANSPARENT);
				outtextxy(xx, yy, strf);
				FlushBatchDraw();
				Sleep(2000);
				break;
			}
		}
		EndBatchDraw();
		return 0;
	}
	else if (a == 2)
	{
		rng.seed(std::random_device()());
		IMAGE imgrcd;
		loadimage(&imgrcd, _T(".\\source\\record\\background.png"));
		person.loadingPlayer2();
		this->loadingmonster();
		person.drawinplace();
		BeginBatchDraw();
		int c = 1;
		int e = 0;

		while (true)
		{
			int b = person.playerMove(8, background::map_size);
			putimage(0, 0, &imgrcd);
			this->coutRmessage();

			static DWORD t1, t2;
			if (t2 - t1 > 500)
			{
				this->monsterCreate();
				this->monsterAction(32, background::map_size);
				e = this->mst2ACT();
				t1 = t2;
			}
			t2 = clock();
			this->ms2ACTmove(e, 4, background::map_size);
			this->drawEnemy();

			static DWORD t5, t6;
			if (t6 - t5 > 2000)
			{
				this->mstACTjudge(background::map_size);
				t5 = t6;
			}
			t6 = clock();

			c = person.drawPlayer(b, c);
			int d = 0;
			static DWORD t3, t4;
			if (t4 - t3 > 500)
			{
				d = person.playerattack2(c);//差分
				this->person2ACT(d, 8);
				t3 = t4;
			}
			t4 = clock();
			this->pyerACTjudge2(8);

			static DWORD t7, t8;
			if (t8 - t7 > 5000)
			{
				person.SPadd();
				t7 = t8;
			}
			t8 = clock();

			FlushBatchDraw();
			Sleep(20);

			if (MouseHit())
			{
				MOUSEMSG msg = GetMouseMsg();
				if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 12 * mm) && msg.y <= (mm + 12 * mm + 2 * mm))
				{
					//存档
					ofstream fp;
					fp.open(".\\source\\save\\save.dat", ios::binary | ios::out);
					fp.write((char*)&person.strcfm, sizeof(playerData));
					fp.close();
				}
				else if (msg.uMsg == WM_LBUTTONDOWN &&
					msg.x >= (mm * map_s + mm / 2) && msg.x <= (mm * map_s + mm / 2 + 4 * mm) &&
					msg.y >= (mm + 15 * mm) && msg.y <= (mm + 15 * mm + 2 * mm))
				{
					break;
				}
			}
			if (person.strcfm.HP <= 0)
			{
				setfillcolor(WHITE);
				setlinecolor(WHITE);
				rectangle(0, 0, 1280, 720);
				solidrectangle(0, 0, 1280, 720);
				int xx = 300;
				int yy = 250;
				settextcolor(BLACK);
				settextstyle(128, 32, _T("黑体"));
				const wchar_t* strf = L"角色阵亡，游戏结束";
				setbkmode(TRANSPARENT);
				outtextxy(xx, yy, strf);
				FlushBatchDraw();
				Sleep(2000);
				break;
			}
		}
		EndBatchDraw();
		return 0;
	}
}

//判断读档角色
int game::playerjudge()
{
	if (person.strcfm.name == "近战剑士")
	{
		return 1;
	}
	else if (person.strcfm.name == "远程法师")
	{
		return 2;
	}
}

//选择角色
int game::playerchoose()
{
	player AA;
	BeginBatchDraw();
	background::playerchooseRectangle_one();
	background::playerchoosepic();
	player::putmessintro1();
	AA.putmessintro2();
	EndBatchDraw();

	int a = 0;
	while (true)
	{
		if (MouseHit())
		{
			MOUSEMSG msgchos = GetMouseMsg();
			//确认角色
			if (msgchos.uMsg == WM_LBUTTONDOWN &&
				msgchos.x >= 980 && msgchos.x <= (980 + 100) &&
				msgchos.y >= 550 && msgchos.y <= (550 + 80))
			{
				if (a == 0)
				{
					return 1;//角色1
				}
				else if (a == 1)
				{
					return 2;//角色2
				}
				
			}
			//翻页
			else if (msgchos.uMsg == WM_LBUTTONDOWN &&
				msgchos.x >= 860 && msgchos.x <= (860 + 100) &&
				msgchos.y >= 550 && msgchos.y <= (550 + 80))
			{
				if (a == 0)
				{
					BeginBatchDraw();
					background::playerchooseRectangle_one();
					background::playerchoosepic();
					playerData::putmessintro3();
					AA.putmessintro4();
					EndBatchDraw();
					a = 1;
				}
				else if (a == 1)
				{
					BeginBatchDraw();
					background::playerchooseRectangle_one();
					background::playerchoosepic();
					playerData::putmessintro1();
					AA.putmessintro2();
					EndBatchDraw();
					a = 0;
				}
			}
			//返回
			else if (msgchos.uMsg == WM_LBUTTONDOWN &&
				msgchos.x >= 980 && msgchos.x <= (980 + 100) &&
				msgchos.y >= 650 && msgchos.y <= (650 + 80))
			{
				BeginBatchDraw();
				background::setbackground();
				EndBatchDraw();
				return 0;
			}
		}
	}
}

//playerData类函数定义
//空缺省构造函数
playerData::playerData()
{
	HP=0;
	SP=0;
	ACT=0;
	DEF=0;
	money=0;
	grade=0;
	live=true;
	x=0;
	y=0;
}

//playerData构造函数
playerData::playerData(string a, int b, int c, int d, int e)
{
	name = a;
	HP = b;
	SP = c;
	ACT = d;
	DEF = e;
	money = 0;
	grade = 0;
	live = true;
	x = 1 * mm;
	y = 11 * mm;
}

//playerData类函数定义
//选角色界面介绍1
void playerData::putmessintro1()
{
	background::playerchooseRectangle_two();
	IMAGE img[4];
	loadimage(&img[0], _T(".\\source\\player\\player1\\101.png"));
	putimage(903, 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player1\\102.png"));
	putimage(903+10+mm, 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player1\\103.png"));
	putimage(903 + 2 * (10 + mm), 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player1\\104.png"));
	putimage(903 + 3 * (10 + mm), 194, &img[0]);
	background::playerchooseRectangle_three();
}

//选角色界面介绍3
void playerData::putmessintro3()
{
	background::playerchooseRectangle_two();
	IMAGE img[4];
	loadimage(&img[0], _T(".\\source\\player\\player2\\201.png"));
	putimage(903, 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player2\\202.png"));
	putimage(903 + 10 + mm, 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player2\\203.png"));
	putimage(903 + 2 * (10 + mm), 194, &img[0]);
	loadimage(&img[0], _T(".\\source\\player\\player2\\204.png"));
	putimage(900 + 3 * (10 + mm), 194, &img[0]);
	background::playerchooseRectangle_three();
}

//player类函数定义
//选角色界面介绍2
void player::putmessintro2()
{
	int arrx[10], arry[10];
	arrx[0] = 860;
	arry[0] = 330;
	for (int i = 0; i < 9; i++)
	{
		arrx[i + 1] = arrx[i];
		arry[i + 1] = arry[i] + 40;
	}

	//输出昵称部分
	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str1 = L"昵称：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[0], arry[0], str1);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	const char* cstr1 = str[0].name.c_str();

	int len = MultiByteToWideChar(CP_ACP, 0, cstr1, -1, NULL, 0);
	LPWSTR lpwstr1 = new WCHAR[len];
	MultiByteToWideChar(CP_ACP, 0, cstr1, -1, lpwstr1, len);
	TCHAR* tstr1 = lpwstr1;
	outtextxy(arrx[0]+50, arry[0], tstr1);

	//输出攻击、防御、血量、蓝量等数据
	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str2 = L"HP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[1], arry[1], str2);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr2[20];
	swprintf(wstr2, L"%d", str[0].HP);
	outtextxy(arrx[1]+50, arry[1], wstr2);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str3 = L"SP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[2], arry[2], str3);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr3[20];
	swprintf(wstr3, L"%d", str[0].SP);
	outtextxy(arrx[2] + 50, arry[2], wstr3);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str4 = L"ACT：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[3], arry[3], str4);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr4[20];
	swprintf(wstr4, L"%d", str[0].ACT);
	outtextxy(arrx[3] + 50, arry[3], wstr4);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str5 = L"DEF：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[4], arry[4], str5);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr5[20];
	swprintf(wstr5, L"%d", str[0].DEF);
	outtextxy(arrx[4] + 50, arry[4], wstr5);

	//生成确认与切换图标
	background::playerchoosebutton();
	settextcolor(BLACK);
	settextstyle(background::maintextlength-32, background::maintextwidth-10, _T("黑体"));
	const wchar_t* strLS1 = L"下一页";
	setbkmode(TRANSPARENT);
	outtextxy(880, 573, strLS1);
	const wchar_t* strLS2 = L"确认";
	setbkmode(TRANSPARENT);
	outtextxy(1010, 573, strLS2);

	//生成返回上一界面图标
	setlinecolor(BLACK);
	setfillcolor(RED);
	rectangle(980, 650, 980+100, 650+80);
	solidrectangle(980, 650, 980 + 100, 650 + 80);
	settextcolor(BLACK);
	settextstyle(background::maintextlength - 32, background::maintextwidth - 10, _T("黑体"));
	const wchar_t* strLS3 = L"返回";
	setbkmode(TRANSPARENT);
	outtextxy(1010, 673, strLS3);
}

//选角色界面介绍4
void player::putmessintro4()
{
	int arrx[10], arry[10];
	arrx[0] = 860;
	arry[0] = 330;
	for (int i = 0; i < 9; i++)
	{
		arrx[i + 1] = arrx[i];
		arry[i + 1] = arry[i] + 40;
	}

	//输出昵称部分
	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str1 = L"昵称：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[0], arry[0], str1);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	const char* cstr1 = str[1].name.c_str();

	int len = MultiByteToWideChar(CP_ACP, 0, cstr1, -1, NULL, 0);
	LPWSTR lpwstr1 = new WCHAR[len];
	MultiByteToWideChar(CP_ACP, 0, cstr1, -1, lpwstr1, len);
	TCHAR* tstr1 = lpwstr1;
	outtextxy(arrx[0] + 50, arry[0], tstr1);

	//输出攻击、防御、血量、蓝量等数据
	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str2 = L"HP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[1], arry[1], str2);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr2[20];
	swprintf(wstr2, L"%d", str[1].HP);
	outtextxy(arrx[1] + 50, arry[1], wstr2);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str3 = L"SP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[2], arry[2], str3);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr3[20];
	swprintf(wstr3, L"%d", str[1].SP);
	outtextxy(arrx[2] + 50, arry[2], wstr3);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str4 = L"ACT：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[3], arry[3], str4);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr4[20];
	swprintf(wstr4, L"%d", str[1].ACT);
	outtextxy(arrx[3] + 50, arry[3], wstr4);

	settextcolor(BLACK);
	settextstyle(36, 8, _T("黑体"));
	const wchar_t* str5 = L"DEF：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[4], arry[4], str5);
	settextstyle(36, 8, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr5[20];
	swprintf(wstr5, L"%d", str[1].DEF);
	outtextxy(arrx[4] + 50, arry[4], wstr5);

	//生成确认与切换图标
	background::playerchoosebutton();
	settextcolor(BLACK);
	settextstyle(background::maintextlength - 32, background::maintextwidth - 10, _T("黑体"));
	const wchar_t* strLS1 = L"上一页";
	setbkmode(TRANSPARENT);
	outtextxy(880, 573, strLS1);
	const wchar_t* strLS2 = L"确认";
	setbkmode(TRANSPARENT);
	outtextxy(1010, 573, strLS2);

	//生成返回上一界面图标
	setlinecolor(BLACK);
	setfillcolor(RED);
	rectangle(980, 650, 980 + 100, 650 + 80);
	solidrectangle(980, 650, 980 + 100, 650 + 80);
	settextcolor(BLACK);
	settextstyle(background::maintextlength - 32, background::maintextwidth - 10, _T("黑体"));
	const wchar_t* strLS3 = L"返回";
	setbkmode(TRANSPARENT);
	outtextxy(1010, 673, strLS3);
}

//空缺省构造函数
player::player()
{

}

//加载角色图片
void player::loadingPlayer()
{
	loadimage(&imgs[0], _T(".\\source\\player\\player1\\101.png"));
	loadimage(&imgs[1], _T(".\\source\\player\\player1\\102.png"));
	loadimage(&imgs[2], _T(".\\source\\player\\player1\\103.png"));
	loadimage(&imgs[3], _T(".\\source\\player\\player1\\104.png"));
	loadimage(&imgs[4], _T(".\\source\\effect\\player1\\1.png"));
	loadimage(&imgs[5], _T(".\\source\\effect\\player1\\101.png"));
	loadimage(&imgs[6], _T(".\\source\\effect\\player1\\102.png"));
	loadimage(&imgs[7], _T(".\\source\\effect\\player1\\103.png"));
	loadimage(&imgs[8], _T(".\\source\\effect\\player1\\104.png"));
}

//加载角色图片2
void player::loadingPlayer2()
{
	loadimage(&imgs[0], _T(".\\source\\player\\player2\\201.png"));
	loadimage(&imgs[1], _T(".\\source\\player\\player2\\202.png"));
	loadimage(&imgs[2], _T(".\\source\\player\\player2\\203.png"));
	loadimage(&imgs[3], _T(".\\source\\player\\player2\\204.png"));
	loadimage(&imgs[4], _T(".\\source\\effect\\player2\\1.png"));
}

//输出角色图片
int player::drawPlayer(int a, int b)
{
	switch (a)
	{
	case 2:
	{
		putimage(strcfm.x, strcfm.y, &imgs[1]);
		return a;
		break;
	}
	case 1:
	{
		putimage(strcfm.x, strcfm.y, &imgs[0]);
		return a;
		break;
	}
	case 3:
	{
		putimage(strcfm.x, strcfm.y, &imgs[2]);
		return a;
		break;
	}
	case 4:
	{
		putimage(strcfm.x, strcfm.y, &imgs[3]);
		return a;
		break;
	}
	case 5:
	{
		putimage(strcfm.x, strcfm.y, &imgs[b-1]);
		return b;
		break;
	}
	default:
		return b;
		break;
	}
}

//角色确立传递
void player::playerconfirm(int a)
{
	strcfm = str[a];
}

//角色移动函数
int player::playerMove(int speed, int map_size[][map_s])
{
	if (GetAsyncKeyState(VK_UP))
	{
		if (this->calplace(speed, 1) == 1)
		{
			strcfm.y -= speed;
		}
		return 2;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (this->calplace(speed, 2) == 1)
		{
			strcfm.y += speed;
		}
		return 1;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (this->calplace(speed, 3) == 1)
		{
			strcfm.x -= speed;
		}
		return 3;
	}
	else if (GetAsyncKeyState(VK_RIGHT))
	{
		if (this->calplace(speed, 4) == 1)
		{
			strcfm.x += speed;
		}
		return 4;
	}
	else return 5;
}

//绘制角色开始的位置
void player::drawinplace()
{
	putimage(strcfm.x, strcfm.y, &imgs[0]);
}

//计算位置对应的矩阵值
int player::calplace(int speed, int movetpye)
{
	int px1 = (strcfm.x) / mm;
	int py1 = (strcfm.y) / mm;
	int px2 = 0;
	int py2 = 0;
	int px3 = strcfm.x % mm;
	int py3 = strcfm.y % mm;
	switch (movetpye)
	{
	case 1:
	{
		//向上
		py2 = (strcfm.y - speed) / mm;
		px2 = (strcfm.x) / mm;
		if ((background::map_size[py1][px1] != 1) && (background::map_size[py2][px2] != 1)
			&& (background::map_size[py2][px2 + 1] != 1))
		{
			return 1;
		}
		else if ((background::map_size[py1][px1] != 1) && (background::map_size[py2][px2] != 1)
			&& (background::map_size[py2][px2 + 1] == 1)
			&& (px3 == 0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case 2:
	{
		//向下
		py2 = (strcfm.y + speed) / mm;
		px2 = (strcfm.x) / mm;
		if ((background::map_size[py1+1][px1] != 1) && (background::map_size[py1+1][px1 + 1] != 1))
		{
			return 1;
		}
		else if ((background::map_size[py1 + 1][px1] != 1)
			&& (background::map_size[py1 + 1][px1 + 1] == 1)
			&& (px3 == 0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case 3:
	{
		//向左
		py2 = (strcfm.y) / mm;
		px2 = (strcfm.x - speed) / mm;
		if ((background::map_size[py1][px1] != 1) && (background::map_size[py2][px2] != 1)
			&& (background::map_size[py2 + 1][px2] != 1))
		{
			return 1;
		}
		else if ((background::map_size[py1][px1] != 1) && (background::map_size[py2][px2] != 1)
			&& (background::map_size[py2 + 1][px2] == 1)
			&& ((py3 == 0)))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	case 4:
	{
		//向右
		py2 = (strcfm.y) / mm;
		px2 = (strcfm.x + speed) / mm;
		if ((background::map_size[py1][px1+1] != 1) && (background::map_size[py1+1][px1 + 1] != 1))
		{
			return 1;
		}
		else if ((background::map_size[py1][px1 + 1] != 1)
			&& (background::map_size[py1 + 1][px1 + 1] == 1)
			&& (py3 == 0))
		{
			return 1;
		}
		else
		{
			return 0;
		}
		break;
	}
	default:return 0;
		break;
	}
}

//角色1攻击
int player::playerattack(int a)
{
	if (GetAsyncKeyState('Z'))
	{
		switch (a)
		{
		case 2:
		{
			putimage(strcfm.x, strcfm.y - mm, &imgs[4]);
			FlushBatchDraw();
			Sleep(100);
			return 1;
			break;
		}
		case 1:
		{
			putimage(strcfm.x, strcfm.y + mm, &imgs[4]);
			FlushBatchDraw();
			Sleep(100);
			return 2;
			break;
		}
		case 3:
		{
			putimage(strcfm.x - mm, strcfm.y, &imgs[4]);
			FlushBatchDraw();
			Sleep(100);
			return 3;
			break;
		}
		case 4:
		{
			putimage(strcfm.x + mm, strcfm.y, &imgs[4]);
			FlushBatchDraw();
			Sleep(100);
			return 4;
			break;
		}
		default:
			return 0;
			break;
		}
	}
	else if (GetAsyncKeyState('X'))
	{
		if (strcfm.SP >= 25)
		{
			for (int i = 5; i < 9; i++)
			{
				putimage(strcfm.x + mm, strcfm.y, &imgs[i]);
				putimage(strcfm.x + mm, strcfm.y - mm, &imgs[i]);
				putimage(strcfm.x + mm, strcfm.y + mm, &imgs[i]);
				putimage(strcfm.x - mm, strcfm.y, &imgs[i]);
				putimage(strcfm.x - mm, strcfm.y - mm, &imgs[i]);
				putimage(strcfm.x - mm, strcfm.y + mm, &imgs[i]);
				putimage(strcfm.x, strcfm.y - mm, &imgs[i]);
				putimage(strcfm.x, strcfm.y + mm, &imgs[i]);
			}
			strcfm.SP -= 25;
			FlushBatchDraw();
			Sleep(1000);
			return 5;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}

//角色2攻击
int player::playerattack2(int a)
{
	if (GetAsyncKeyState('Z'))
	{
		switch (a)
		{
		case 2:
		{
			return 1;
			break;
		}
		case 1:
		{
			return 2;
			break;
		}
		case 3:
		{
			return 3;
			break;
		}
		case 4:
		{
			return 4;
			break;
		}
		default:
			return 0;
			break;
		}
	}
}

//分数上升
void player::addGrade(bool b)
{
	if (b)
	{
		strcfm.grade += 10;
	}
}

//金钱上升
void player::addMoney(int a)
{
	if (a == 0)
	{
		strcfm.money += 2;
	}
	else if (a == 1)
	{
		strcfm.money += 3;
	}
	else if (a == 2)
	{
		strcfm.money += 5;
	}
}

//回复SP
void player::SPadd()
{
	if (((strcfm.x + mm) >= ((map_s-2) * mm))
		&& ((strcfm.x ) <= ((map_s - 1) * mm))
		&& ((strcfm.y+mm) >= ((12 - 1) * mm))
		&& ((strcfm.y) <= ((12) * mm)))
	{
		strcfm.SP += 25;
	}
}

//enemy类函数定义
//敌人类构造函数
enemy::enemy()
{
	HP = 10;
	live = false;
	x = 0;
	y = 0;
	type = 0;
}

//怪物血量判定
bool enemy::monsterHPjudge()
{
	if (HP <= 0)
	{
		live = false;
		return true;
	}
	else
	{
		return false;
	}
}

//怪物三攻击方式
void enemy::mst3ACTway(int map_size[][map_s])
{
	int b = x / mm;
	int a = y / mm;
	for (int i = b - 1; i >= 0; i--)
	{
		if (map_size[a][i] == 1)
		{
			break;
		}
		putimage(i * mm, a * mm, &imgss[4]);
	}
	for (int i = b + 1; i < map_s; i++)
	{
		if (map_size[a][i] == 1)
		{
			break;
		}
		putimage(i * mm, a * mm, &imgss[4]);
	}
	for (int i = a - 1; i >= 0; i--)
	{
		if (map_size[i][b] == 1)
		{
			break;
		}
		putimage(b * mm, i * mm, &imgss[3]);
	}
	for (int i = a + 1; i < map_r; i++)
	{
		if (map_size[i][b] == 1)
		{
			break;
		}
		putimage(b * mm, i * mm, &imgss[3]);
	}
}

//加载怪物图片
void game::loadingmonster()
{
	for (int i = 0; i < monster_max; i++)
	{
		loadimage(&monster[i].imgss[0], _T(".\\source\\enemy\\1.png"));
		loadimage(&monster[i].imgss[1], _T(".\\source\\enemy\\2.png"));
		loadimage(&monster[i].imgss[2], _T(".\\source\\enemy\\3.png"));
		loadimage(&monster[i].imgss[3], _T(".\\source\\effect\\monster3\\1.png"));
		loadimage(&monster[i].imgss[4], _T(".\\source\\effect\\monster3\\2.png"));
		loadimage(&monster[i].imgss[5], _T(".\\source\\effect\\monster1\\1.png"));
		loadimage(&monster[i].imgss[6], _T(".\\source\\effect\\monster2\\1.png"));
	}
}

//输出怪物图片
void game::drawEnemy()
{
	for (int i = 0; i < monster_max; i++)
	{
		if (monster[i].live)
		{
			if (monster[i].type == 0)
			{
				putimage(monster[i].x, monster[i].y, &monster[i].imgss[0]);
			}
			else if (monster[i].type == 1)
			{
				putimage(monster[i].x, monster[i].y, &monster[i].imgss[1]);
			}
			else if (monster[i].type == 2)
			{
				putimage(monster[i].x, monster[i].y, &monster[i].imgss[2]);
			}
		}
	}
}

//计算怪物位置对应的矩阵值
int game::calpalceMonster(int speed)
{
	int a = dist_m(rng);
	for (int i = 0; i < monster_max; i++)
	{
		if (monster[i].live)
		{
			int px1 = (monster[i].x) / mm;
			int py1 = (monster[i].y) / mm;
			switch (a)
			{
			case 1:
			{
				//向上
				if (background::map_size[py1 - 1][px1] != 1) 
				{
					return 1;
				}
				break;
			}
			case 2:
			{
				//向下
				if (background::map_size[py1 + 1][px1] != 1) 
				{
					return 2;
				}
				break;
			}
			case 3:
			{
				//向左
				if (background::map_size[py1][px1 - 1] != 1) 
				{
					return 3;
				}
				break;
			}
			case 4:
			{
				//向右
				if (background::map_size[py1][px1 + 1] != 1)
				{
					return 4;
				}
				break;
			}
			default:
				return 0;
				break;
			}
		}
	}
}

//怪物行为
void game::monsterAction(int speed, int map_size[][map_s])
{
	for (int i = 0; i < monster_max; i++)
	{
		if (monster[i].live)
		{
			int a = calpalceMonster(speed);
			int px1 = (monster[i].x) / mm;
			int py1 = (monster[i].y) / mm;
			switch (a)
			{
			case 1:
				// 向上
				if (background::map_size[py1 - 1][px1] != 1)
				{
					monster[i].y -= speed;
				}
				break;
			case 2:
				// 向下
				if (background::map_size[py1 + 1][px1] != 1)
				{
					monster[i].y += speed;
				}
				break;
			case 3:
				// 向左
				if (background::map_size[py1][px1 - 1] != 1)
				{
					monster[i].x -= speed;
				}
				break;
			case 4:
				// 向右
				if (background::map_size[py1][px1 + 1] != 1)
				{
					monster[i].x += speed;
				}
				break;
			}
		}
	}
}

//产生怪物
void game::monsterCreate()
{
	for (int i = 0; i < monster_max; i++)
	{
		if (!monster[i].live)
		{
			monster[i].live = true;
			int a = 0;
			int b = 0;
			do
			{
				a = dist_a(rng);
				b = dist_b(rng);
				monster[i].x = a * mm;
				monster[i].y = b * mm;
			} while (background::map_size[b][a] == 1);
			int c = dist_type(rng);
			if (c <= 4)
			{
				monster[i].type = 0;
				monster[i].HP = 10;
			}
			else if ((c > 4) && (c <= 7))
			{
				monster[i].type = 1;
				monster[i].HP = 20;
			}
			else
			{
				monster[i].type = 2;
				monster[i].HP = 40;
			}
		}
	}
}

//判定角色1的攻击行为
void game::pyerACTjudge1(int a)
{
	switch (a)
	{
	case 1:
	{
		for (int i = 0; i < monster_max; i++)
		{
			if (monster[i].live)
			{
				if (((monster[i].x + mm / 2) >= person.strcfm.x)
					&& ((monster[i].x + mm / 2) <= person.strcfm.x + mm)
					&&((monster[i].y+mm/2)>=(person.strcfm.y-mm))
					&& ((monster[i].y + mm / 2) <= person.strcfm.y))
				{
					monster[i].HP -= 10;
					bool b = monster[i].monsterHPjudge();
					person.addGrade(b);
					person.addMoney(monster[i].type);
				}
			}
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < monster_max; i++)
		{
			if (monster[i].live)
			{
				if (((monster[i].x + mm / 2) >= person.strcfm.x)
					&& ((monster[i].x + mm / 2) <= person.strcfm.x + mm)
					&& ((monster[i].y + mm / 2) >= (person.strcfm.y + mm))
					&& ((monster[i].y + mm / 2) <= person.strcfm.y + 2 * mm))
				{
					monster[i].HP -= 10;
					bool b = monster[i].monsterHPjudge();
					person.addGrade(b);
					person.addMoney(monster[i].type);
				}
			}
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < monster_max; i++)
		{
			if (monster[i].live)
			{
				if (((monster[i].x + mm / 2) >= person.strcfm.x - mm)
					&& ((monster[i].x + mm / 2) <= person.strcfm.x)
					&& ((monster[i].y + mm / 2) >= (person.strcfm.y))
					&& ((monster[i].y + mm / 2) <= person.strcfm.y + mm))
				{
					monster[i].HP -= 10;
					bool b = monster[i].monsterHPjudge();
					person.addGrade(b);
					person.addMoney(monster[i].type);
				}
			}
		}
		break;
	}
	case 4:
	{
		for (int i = 0; i < monster_max; i++)
		{
			if (monster[i].live)
			{
				if (((monster[i].x + mm / 2) >= person.strcfm.x + mm)
					&& ((monster[i].x + mm / 2) <= person.strcfm.x + 2 * mm)
					&& ((monster[i].y + mm / 2) >= (person.strcfm.y))
					&& ((monster[i].y + mm / 2) <= person.strcfm.y + mm))
				{
					monster[i].HP -= 10;
					bool b = monster[i].monsterHPjudge();
					person.addGrade(b);
					person.addMoney(monster[i].type);
				}
			}
		}
		break;
	}
	case 5:
	{
		for (int i = 0; i < monster_max; i++)
		{
			if (monster[i].live)
			{
				if (((monster[i].x + mm / 2) >= person.strcfm.x - mm)
					&& ((monster[i].x + mm / 2) <= person.strcfm.x + 2 * mm)
					&& ((monster[i].y + mm / 2) >= (person.strcfm.y - mm))
					&& ((monster[i].y + mm / 2) <= person.strcfm.y + 2 * mm))
				{
					monster[i].HP -= 20;
					bool b = monster[i].monsterHPjudge();
					person.addGrade(b);
					person.addMoney(monster[i].type);
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

//判定角色2的攻击行为
void game::pyerACTjudge2(int speed)
{
	for (int i = 0; i < 5; i++)
	{
		if (perbull[i].live)
		{
			if (perbull[i].fx == 1)
			{
				perbull[i].y -= speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
			}
			else if (perbull[i].fx == 2)
			{
				perbull[i].y += speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
			}
			else if (perbull[i].fx == 3)
			{
				perbull[i].x -= speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
			}
			else if (perbull[i].fx == 4)
			{
				perbull[i].x += speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
			}
			for (int j = 0; j < monster_max; j++)
			{
				if (monster[j].live)
				{
					if (((monster[j].x + mm) > (perbull[i].x))
						&& ((monster[j].x) < (perbull[i].x + mm))
						&& ((monster[j].y + mm) > (perbull[i].y))
						&& ((monster[j].y) < (perbull[i].y + mm)))
					{
						monster[j].HP -= 20;
						bool b = monster[j].monsterHPjudge();
						person.addGrade(b);
						person.addMoney(monster[i].type);
						perbull[i].live = false;
					}
				}
			}

			if ((perbull[i].y < 0) || (perbull[i].y > map_r*mm)
				|| (perbull[i].x < 0) || (perbull[i].x > map_s*mm))
			{
				perbull[i].live = false;
			}
		}
	}
}

//输出右侧信息
void game::coutRmessage()
{
	int arrx[10], arry[10];
	arrx[0] = mm * map_s + mm / 2;
	arry[0] = mm;
	for (int i = 0; i < 9; i++)
	{
		arrx[i + 1] = arrx[i];
		arry[i + 1] = arry[i] + 3 * mm;
	}

	//HP输出
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str1 = L"HP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[0], arry[0], str1);
	settextstyle(64, 16, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr12[20];
	swprintf(wstr12, L"%d", person.strcfm.HP);
	outtextxy(arrx[0] + 50, arry[0], wstr12);

	//SP输出
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str2 = L"SP：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[1], arry[1], str2);
	settextstyle(64, 16, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr22[20];
	swprintf(wstr22, L"%d", person.strcfm.SP);
	outtextxy(arrx[1] + 50, arry[1], wstr22);

	//grade输出
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str3 = L"分数：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[2], arry[2], str3);
	settextstyle(64, 16, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr32[20];
	swprintf(wstr32, L"%.1lf", person.strcfm.grade);
	outtextxy(arrx[2] + 100, arry[2], wstr32);

	//money输出
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str4 = L"金钱：";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[3], arry[3], str4);
	settextstyle(64, 16, _T("宋体"));
	setbkmode(TRANSPARENT);
	wchar_t wstr42[20];
	swprintf(wstr42, L"%ld", person.strcfm.money);
	outtextxy(arrx[3] + 100, arry[3], wstr42);

	//存档与退出
	setfillcolor(RGB(255, 127, 39));
	setlinecolor(RGB(255, 127, 39));
	rectangle(arrx[4], arry[4], arrx[4] + 4 * mm, arry[4] + 2 * mm);
	solidrectangle(arrx[4], arry[4], arrx[4] + 4 * mm, arry[4] + 2 * mm);
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str5 = L"存档";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[4] + mm, arry[4], str5);

	setfillcolor(RGB(255, 127, 39));
	setlinecolor(RGB(255, 127, 39));
	rectangle(arrx[5], arry[5], arrx[5] + 4 * mm, arry[5] + 2 * mm);
	solidrectangle(arrx[5], arry[5], arrx[5] + 4 * mm, arry[5] + 2 * mm);
	settextcolor(BLACK);
	settextstyle(64, 16, _T("黑体"));
	const wchar_t* str6 = L"退出";
	setbkmode(TRANSPARENT);
	outtextxy(arrx[5] + mm, arry[5], str6);
}

//判定怪物的攻击行为
void game::mstACTjudge(int map_size[][map_s])
{
	for (int i = 0; i < monster_max; i++)
	{
		if (monster[i].live)
		{
			if (monster[i].type == 0)
			{
				if (((person.strcfm.x) > (monster[i].x - mm))
					&& ((person.strcfm.x) < (monster[i].x + mm))
					&& ((person.strcfm.y) < (monster[i].y - mm))
					&& ((person.strcfm.y) < (monster[i].y + mm)))
				{
					putimage(monster[i].x, monster[i].y, &monster[i].imgss[5]);
					if (person.strcfm.DEF > 0)
					{
						person.strcfm.DEF -= 5;
						person.strcfm.HP -= 10;
					}
					else if (person.strcfm.DEF <= 0)
					{
						person.strcfm.HP -= 50;
					}
				}
			}
			else if (monster[i].type == 1)
			{
				//空
			}
			else if (monster[i].type == 2)
			{
				//怪物三攻击
				int e2 = monster[i].x / mm;
				int e1 = monster[i].y / mm;
				int e3 = 0;
				int e4 = 0;
				int e5 = 0;
				int e6 = 0;
				for (int j = e2 - 1; j >= 0; j--)
				{
					if (map_size[e1][j] == 1)
					{
						e3 = j + 1;
						break;
					}
				}
				for (int j = e2 + 1; j < map_s; j++)
				{
					if (map_size[e1][j] == 1)
					{
						e4 = j - 1;
						break;
					}
				}
				for (int j = e1 - 1; j >=0; j--)
				{
					if (map_size[j][e2] == 1)
					{
						e5 = j + 1;
						break;
					}
				}
				for (int j = e1 + 1; j < map_r; j++)
				{
					if (map_size[j][e2] == 1)
					{
						e6 = j - 1;
						break;
					}
				}
				if ((((person.strcfm.x + mm) > (e3 * mm))
					&& ((person.strcfm.x) < (e4 * mm + mm))
					&& ((person.strcfm.y + mm) > (monster[i].y))
					&& ((person.strcfm.y) < (monster[i].y + mm)))
					|| (((person.strcfm.x + mm) > monster[i].x)
						&& ((person.strcfm.x) < (monster[i].x + mm))
						&& ((person.strcfm.y + mm) > (e5 * mm))
						&& ((person.strcfm.y) < (e6 * mm + mm))))
				{
					if (person.strcfm.DEF > 0)
					{
						person.strcfm.DEF -= 5;
						person.strcfm.HP -= 10;
					}
					else if (person.strcfm.DEF <= 0)
					{
						person.strcfm.HP -= 50;
					}
				}
				monster[i].mst3ACTway(background::map_size);
			}
		}
	}
}

//怪物2攻击行为
int game::mst2ACT()
{
	int a = dist_bull(rng);
	for (int i = 0; i < monster_max; i++)
	{
		if (monster[i].live)
		{
			if (monster[i].type == 1)
			{
				if (!monster[i].monsbull.live)
				{
					monster[i].monsbull.live = true;
					switch (a)
					{
					case 1:
					{
						monster[i].monsbull.x = monster[i].x;
						monster[i].monsbull.y = monster[i].y - mm;
						putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
						return 1;
						break;
					}
					case 2:
					{
						monster[i].monsbull.x = monster[i].x;
						monster[i].monsbull.y = monster[i].y + mm;
						putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
						return 2;
						break;
					}
					case 3:
					{
						monster[i].monsbull.x = monster[i].x - mm;
						monster[i].monsbull.y = monster[i].y;
						putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
						return 3;
						break;
					}
					case 4:
					{
						monster[i].monsbull.x = monster[i].x + mm;
						monster[i].monsbull.y = monster[i].y;
						putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
						return 4;
						break;
					}
					default:
						return 0;
						break;
					}
				}
			}
		}
	}
}

//怪物2攻击物
void game::ms2ACTmove(int a,int speed, int map_size[][map_s])
{
	for (int i = 0; i < monster_max; i++)
	{
		int b = monster[i].x / mm;
		int c = monster[i].y / mm;
		if (map_size[b][c] == 1)
		{
			monster[i].monsbull.live = false;
		}
		if ((monster[i].monsbull.x < 0)
			|| (monster[i].monsbull.x > map_s * mm)
			|| (monster[i].monsbull.y < 0)
			|| (monster[i].monsbull.y > map_r * mm))
		{
			monster[i].monsbull.live = false;
		}
		if (monster[i].monsbull.live)
		{
			if (((person.strcfm.x + mm) > monster[i].monsbull.x)
				&& ((person.strcfm.x) < (monster[i].monsbull.x + mm))
				&& ((person.strcfm.y + mm) > (monster[i].monsbull.y))
				&& ((person.strcfm.y) < (monster[i].monsbull.y + mm)))
			{
				monster[i].monsbull.live = false;
				if (person.strcfm.DEF > 0)
				{
					person.strcfm.DEF -= 5;
					person.strcfm.HP -= 10;
				}
				else if (person.strcfm.DEF <= 0)
				{
					person.strcfm.HP -= 50;
				}
			}
		}
		if (monster[i].type == 1)
		{
			if (monster[i].monsbull.live)
			{
				if (a == 1)
				{
					monster[i].monsbull.y -= speed;
					putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
				}
				else if (a == 2)
				{
					monster[i].monsbull.y += speed;
					putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
				}
				else if (a == 3)
				{
					monster[i].monsbull.x -= speed;
					putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
				}
				else if (a == 4)
				{
					monster[i].monsbull.x += speed;
					putimage(monster[i].monsbull.x, monster[i].monsbull.y, &monster[i].imgss[6]);
				}
			}
		}
	}
}

//角色2攻击输出
void game::person2ACT(int a,int speed)
{
	switch (a)
	{
	case 1:
	{
		for (int i = 0; i < 5; i++)
		{
			if(!perbull[i].live)
			{
				perbull[i].fx = 1;
				perbull[i].live = true;
				perbull[i].x = person.strcfm.x;
				perbull[i].y = person.strcfm.y - mm;
				//perbull[i].y -= speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
				break;
			}
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i < 5; i++)
		{
			if (!perbull[i].live)
			{
				perbull[i].fx = 2;
				perbull[i].live = true;
				perbull[i].x = person.strcfm.x;
				perbull[i].y = person.strcfm.y + mm;
				//perbull[i].y += speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
				break;
			}
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i < 5; i++)
		{
			if (!perbull[i].live)
			{
				perbull[i].fx = 3;
				perbull[i].live = true;
				perbull[i].x = person.strcfm.x - mm;
				perbull[i].y = person.strcfm.y;
				//perbull[i].x -= speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
				break;
			}
		}
		break;
	}
	case 4:
	{
		for (int i = 0; i < 5; i++)
		{
			if (!perbull[i].live)
			{
				perbull[i].fx = 4;
				perbull[i].live = true;
				perbull[i].x = person.strcfm.x + mm;
				perbull[i].y = person.strcfm.y;
				//perbull[i].x += speed;
				putimage(perbull[i].x, perbull[i].y, &person.imgs[4]);
				break;
			}
		}
		break;
	}
	default:
		break;
	}
}

//bull类构造函数
bull::bull()
{
	x = 0;
	y = 0;
	live = false;
	fx = 0;
}
