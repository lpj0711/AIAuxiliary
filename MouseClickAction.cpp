#include "MouseClickAction.h"
#include<Windows.h>

using namespace std;

void moveMouse(int x,int y) {
	SetCursorPos(x, y);
}

/*SendInput函数是 Win32 API 中用于模拟输入事件的函数，可以模拟鼠标事件、键盘事件、硬件事件
    等。
    其函数原型如下：
        UINT SendInput(UINT nInputs, LPINPUT pInputs, int cbSize);
    其中，nInputs 参数指定输入事件的数量，pInputs 参数指向输入事件数组的指针，cbSize 参数指定输
    入事件数组的大小（单位为字节）。*/
void mousClick() {
    INPUT input;                //创建一个INPUT类型结构体
    input.type = INPUT_MOUSE;   //指定输入事件类型为鼠标事件
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP; // 模拟鼠标左键按下和抬起的动作
    //mi是结构体INPUT的一个成员属性，mi是MOUSEINPUT类型
    //MOUSEINPUT 结构体用于描述鼠标事件，例如鼠标左键单击、双击、右键单击、移动等操作。

    input.mi.dx = 0;            //设置鼠标事件发生的x坐标
    input.mi.dy = 0;            //设置鼠标事件发生的y坐标
    input.mi.mouseData = 0;     //设置鼠标滚轮的滚动距离
    input.mi.dwExtraInfo = 0;   //将 dwExtraInfo 字段设置为 0，表示不传递任何附加的输入数据。
    input.mi.time = 0;          //time字段是用来设置时间戳的，0表示使用系统的时间戳
    SendInput(1, &input, sizeof(INPUT));
}
void moveMouseAndClick(int x, int y) {
    moveMouse(x,y);
    mousClick();
}