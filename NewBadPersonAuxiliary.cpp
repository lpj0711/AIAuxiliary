#include "NewBadPersonAuxiliary.h"
#include"MouseClickAction.h"
#include<conio.h>
#include <iostream>  
#include <string> 
#include<map>
#include<Windows.h>
using namespace std;

map<string, int> keypadDict = { {"a" , 97},{"b" , 98},{"c" , 99},{"d" , 100},{"e" , 101},{"f" , 102},{"g" , 103},{"h" , 104},{"i" , 105},{"j" , 106},
							{"k" , 107},{"l" , 108},{"m" , 109},{"n" , 110},{"o" , 111},{"p" , 112},{"q" , 113},{"r" , 114},{"s" , 115},{"t" , 116},
							{"u" , 117},{"v" , 118},{"w" , 119},{"x" , 120},{"y" , 121},{"z" , 122},{"esc" , 27},
							{"0" , 48},{"1" , 49},{"2" , 50}, {"3" , 51},{"4" , 52},{"5" , 53}, {"6" , 54},{"7" , 55},{"8" , 56},{"9" , 57}, 
							{"`" , 96},{"-" , 45},{"=" , 61}, {"back space" , 8},{"tab" , 9},{"[" , 161}, {"]" , 191},{"enter" , 13},{"del" , 224}};
Mouse_Click_Action mca;
/*
	跳过镜头
*/
void jumpTheStory(int number) {
	for (int i = 0; i < number; i++)
	{
		mca.moveMouseAndClick(256, 605);
		Sleep(1000 * 0.2);
	}
}

/*
	主线任务
*/
void mainLines() {
	//剧情
	mca.moveMouseAndClick(45, 910);
	Sleep(1000 * 1);
	//剧情
	mca.moveMouseAndClick(127, 910);
	Sleep(1000*1);
	//挑战
	mca.moveMouseAndClick(265, 712);
	Sleep(1000*1);
	//跳过镜头
	jumpTheStory(20);
	//出战
	mca.moveMouseAndClick(257, 898);
	Sleep(1000 * 15);
	mca.moveMouseAndClick(179, 748);
	//空白关闭
	mca.moveMouseAndClick(256, 867);
	Sleep(1000 * 2);
	//跳过镜头
	jumpTheStory(10);
}
/*
登陆账号
*/
void LoginGame() {
	mca.moveMouseAndClick(269, 805);
	Sleep(5000);
}

/*
跳过剧情
*/
void skipTheStory() {
	int keypad;
	//LoginGame();
	while (true)
	{
		if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			keypad = _getch();
			cout << to_string(keypad) << endl;
			if (keypad == 27)
			{
				break;
			}
		}
		if (keypad == keypadDict["enter"]) {
			mainLines();
		}
	}	
}

void New_Bad_Person_Auxiliary::runGame() {
	skipTheStory();
}

void New_Bad_Person_Auxiliary::keyDown(int keyWord) {
	int keypad;
	while (true)
	{
		if (_kbhit()) {//如果有按键按下，则_kbhit()函数返回真
			keypad = _getch();
			cout << to_string(keypad) << endl;
			if (keypad == 27)
			{
				break;
			}
		}
		keybd_event(keyWord, 0, 0, 0); //按下F键
		Sleep(1000 * 3);
	}
}