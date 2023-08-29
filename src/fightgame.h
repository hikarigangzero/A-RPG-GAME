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
	static void setbegin();//��������
	static void setbackground();//���ñ���
	static void setbgRectangle();//����������ı���
	static void setbgWord();//��������������
	static void setbgpic();//����������ͼƬ
	static void loadingpic();//���ù���ͼ
	static void playerchooseRectangle_one();//���ý�ɫѡ����汳����ɫ
	static void playerchoosepic();//���ý�ɫѡ�����ͼƬ
	static void playerchooseRectangle_two();//����ѡ���ɫ����1
	static void playerchooseRectangle_three(); // ����ѡ���ɫ����2
	static void playerchoosebutton();//���ð�ťͼ��
	static void setfightbg();//����ս�����汳��
	static int maintextlength;//�����水ť���峤
	static int maintextwidth;//�����水ť�����
	static int smalllength;//��ť��
	static int smallwidth;//��ť��
	static int map_size[map_r][map_s];//��ͼ��ʼ��

private:
	
};

class playerData
{
public:
	playerData(string a, int b, int c, int d, int e);
	playerData();
	static void putmessintro1();//ѡ��ɫ�������1
	static void putmessintro3();//ѡ��ɫ�������3
	friend class player;
	friend class game;

protected:
	string name;//��ɫ��
	int HP;//Ѫ��
	int SP;//ħ��ֵ
	int ACT;//������
	int DEF;//������
	long int money;//��Ǯ
	double grade;//����
	bool live;//������
	int x;//������
	int y;//������
};

class bull
{
public:
	bull();
	friend class enemy;
	friend class player;
	friend class game;

private:
	int x;//������
	int y;//������
	bool live;//������
	int fx;//�����¼
};

class player :public playerData
{
public:
	player();
	void putmessintro2();//ѡ��ɫ�������2
	void putmessintro4();//ѡ��ɫ�������4
	void loadingPlayer();//���ؽ�ɫͼƬ
	int drawPlayer(int a, int b);//�����ɫͼƬ
	void playerconfirm(int a);//��ɫȷ������
	int playerMove(int speed, int map_size[][map_s]);//��ɫ�ƶ�
	void drawinplace();//���ƽ�ɫ��ʼ��λ��
	int calplace(int speed, int movetpye);//����λ�ö�Ӧ�ľ���ֵ
	int playerattack(int a);//��ɫ1����
	int playerattack2(int a);//��ɫ2����
	void addGrade(bool b);//��������
	void addMoney(int a);//��Ǯ����
	void loadingPlayer2();//���ؽ�ɫͼƬ2
	void SPadd();//�ظ�SP
	friend class game;

	playerData str[2] = { {"��ս��ʿ",150,50,10,30},{"Զ�̷�ʦ",100,100,20,10} };
private:
	IMAGE imgs[9];
	playerData strcfm;
};

class enemy
{
public:
	enemy();
	bool monsterHPjudge();//����Ѫ���ж�
	void mst3ACTway(int map_size[][map_s]);//������������ʽ
	friend class game;

private:
	int HP;//Ѫ��
	int type;//�������Ƶ�������
	bool live;//������
	int x;//������
	int y;//������
	IMAGE imgss[7];//ͼƬ
	bull monsbull;
};

class game
{
public:
	int startGame();//��ʼ��Ϸ
	static int playerchoose();//ѡ���ɫ
	void drawEnemy();//�������ͼƬ
	void monsterCreate();//��������
	void loadingmonster();//���ع���ͼƬ
	void monsterAction(int speed, int map_size[][map_s]);//������Ϊ
	int calpalceMonster(int speed);//����λ�ö�Ӧ�ľ���ֵ
	void pyerACTjudge1(int a);//�ж���ɫ1�Ĺ�����Ϊ
	void coutRmessage();//����Ҳ���Ϣ
	void mstACTjudge(int map_size[][map_s]);//�ж�����Ĺ�����Ϊ
	int mst2ACT();//����2������Ϊ
	void ms2ACTmove(int a,int speed, int map_size[][map_s]);//����2������
	void person2ACT(int a, int speed);//��ɫ2�������
	void pyerACTjudge2(int speed);//�ж���ɫ2�Ĺ�����Ϊ
	int goonGame();//������ʼ��Ϸ
	int playerjudge();//�ж϶�����ɫ

	static uniform_int_distribution<int> dist_type;
	static uniform_int_distribution<int> dist_a;
	static uniform_int_distribution<int> dist_b;
	static uniform_int_distribution<int> dist_m;
	static uniform_int_distribution<int> dist_bull;
private:
	player person;//��ҿ��ƵĽ�ɫ
	enemy monster[monster_max];//����
	bull perbull[5];//��ɫ2��������
	mt19937 rng;//�������
};

class cmdcontrol
{
public:
	void mainneumctrl();//���˵��������
private:
	game cmdHead;
};



