#define _CRT_SECURE_NO_WARNINGS 1
#define _CRT_NON_CONFORMING_SWPRINTFS

#include<iostream>
using namespace std;

#include"fightgame.h"
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

int main()
{
	background::setbegin();
	cmdcontrol mainPerson;
	mainPerson.mainneumctrl();
	system("pause");
	return 0;
}