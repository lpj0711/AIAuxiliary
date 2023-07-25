#include "MouseClickAction.h"
#include<Windows.h>

using namespace std;

void move_mouse(int x,int y) {
	SetCursorPos(x, y);
	Sleep(100);
}