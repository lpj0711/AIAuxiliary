#include "NewBadPersonAuxiliary.h"
#include"MouseClickAction.h"
#include<conio.h>
#include <iostream>  
#include <string> 
#include<map>
using namespace std;

map<string, int> keypad = { {"a" , 97},{"b" , 98},{"c" , 99},{"d" , 100},{"e" , 101},{"f" , 102},{"g" , 103},{"h" , 104},{"i" , 105},{"j" , 106},
							{"k" , 107},{"l" , 108},{"m" , 109},{"n" , 110},{"o" , 111},{"p" , 112},{"q" , 113},{"r" , 114},{"s" , 115},{"t" , 116},
							{"u" , 117},{"v" , 118},{"w" , 119},{"x" , 120},{"y" , 121},{"z" , 122},{"esc" , 27},
							{"0" , 48},{"1" , 49},{"2" , 50}, {"3" , 51},{"4" , 52},{"5" , 53}, {"6" , 54},{"7" , 55},{"8" , 56},{"9" , 57}, 
							{"`" , 96},{"-" , 45},{"=" , 61}, {"back space" , 8},{"tab" , 9},{"[" , 161}, {"]" , 191},{"enter" , 13},{"del" , 224}};

/*
跳过剧情
*/
void skipTheStory() {
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
		moveMouseAndClick(100, 1000);
	}	
}

void runGame() {
	skipTheStory();
}