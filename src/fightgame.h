#pragma once
#include<iostream>
#include<easyx.h>
#include<graphics.h>
#include <mmsystem.h>
#include<string>
#include<tchar.h>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <wchar.h>
#include <fstream>

#pragma comment(lib, "winmm.lib")

const int mm = 32;
const int map_r = 22;
const int map_s = 33;
const int monster_max = 10;

class background
{
public:
	static void setbegin();//开启窗口
	static void setbackground();//设置背景
	static void setbgRectangle();//设置主界面的背景
	static void setbgWord();//设置主界面文字
	static void setbgpic();//设置主界面图片
	static void loadingpic();//设置过场图
	static void playerchooseRectangle_one();//设置角色选择界面背景纯色
	static void playerchoosepic();//设置角色选择界面图片
	static void playerchooseRectangle_two();//设置选择框纯色背景1
	static void playerchooseRectangle_three(); // 设置选择框纯色背景2
	static void playerchoosebutton();//设置按钮图标
	static void setfightbg();//设置战斗界面背景
	static int maintextlength;//主界面按钮字体长
	static int maintextwidth;//主界面按钮字体宽
	static int smalllength;//按钮长
	static int smallwidth;//按钮宽
	static int map_size[map_r][map_s];//地图初始化

private:
	
};

class playerData
{
public:
	playerData(string a, int b, int c, int d, int e);
	playerData();
	static void putmessintro1();//选角色界面介绍1
	static void putmessintro3();//选角色界面介绍3
	friend class player;
	friend class game;

protected:
	string name;//角色名
	int HP;//血量
	int SP;//魔法值
	int ACT;//攻击力
	int DEF;//防御力
	long int money;//金钱
	double grade;//分数
	bool live;//存活情况
	int x;//横坐标
	int y;//纵坐标
};

class bull
{
public:
	bull();
	friend class enemy;
	friend class player;
	friend class game;

private:
	int x;//横坐标
	int y;//纵坐标
	bool live;//存活情况
	int fx;//方向记录
};

class player :public playerData
{
public:
	player();
	void putmessintro2();//选角色界面介绍2
	void putmessintro4();//选角色界面介绍4
	void loadingPlayer();//加载角色图片
	int drawPlayer(int a, int b);//输出角色图片
	void playerconfirm(int a);//角色确立传递
	int playerMove(int speed, int map_size[][map_s]);//角色移动
	void drawinplace();//绘制角色开始的位置
	int calplace(int speed, int movetpye);//计算位置对应的矩阵值
	int playerattack(int a);//角色1攻击
	int playerattack2(int a);//角色2攻击
	void addGrade(bool b);//分数上升
	void addMoney(int a);//金钱上升
	void loadingPlayer2();//加载角色图片2
	void SPadd();//回复SP
	friend class game;

	playerData str[2] = { {"近战剑士",150,50,10,30},{"远程法师",100,100,20,10} };
private:
	IMAGE imgs[9];
	playerData strcfm;
};

class enemy
{
public:
	enemy();
	bool monsterHPjudge();//怪物血量判定
	void mst3ACTway(int map_size[][map_s]);//怪物三攻击方式
	friend class game;

private:
	int HP;//血量
	int type;//用来控制敌人类型
	bool live;//存活情况
	int x;//横坐标
	int y;//纵坐标
	IMAGE imgss[7];//图片
	bull monsbull;
};

class game
{
public:
	int startGame();//开始游戏
	static int playerchoose();//选择角色
	void drawEnemy();//输出怪物图片
	void monsterCreate();//产生怪物
	void loadingmonster();//加载怪物图片
	void monsterAction(int speed, int map_size[][map_s]);//怪物行为
	int calpalceMonster(int speed);//计算位置对应的矩阵值
	void pyerACTjudge1(int a);//判定角色1的攻击行为
	void coutRmessage();//输出右侧信息
	void mstACTjudge(int map_size[][map_s]);//判定怪物的攻击行为
	int mst2ACT();//怪物2攻击行为
	void ms2ACTmove(int a,int speed, int map_size[][map_s]);//怪物2攻击物
	void person2ACT(int a, int speed);//角色2攻击输出
	void pyerACTjudge2(int speed);//判定角色2的攻击行为
	int goonGame();//读档开始游戏
	int playerjudge();//判断读档角色

	static uniform_int_distribution<int> dist_type;
	static uniform_int_distribution<int> dist_a;
	static uniform_int_distribution<int> dist_b;
	static uniform_int_distribution<int> dist_m;
	static uniform_int_distribution<int> dist_bull;
private:
	player person;//玩家控制的角色
	enemy monster[monster_max];//敌人
	bull perbull[5];//角色2攻击总数
	mt19937 rng;//随机因子
};

class cmdcontrol
{
public:
	void mainneumctrl();//主菜单界面控制
private:
	game cmdHead;
};



