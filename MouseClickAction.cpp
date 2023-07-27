#include "MouseClickAction.h"
#include<Windows.h>

using namespace std;

void moveMouse(int x,int y) {
	SetCursorPos(x, y);
}

/*SendInput������ Win32 API ������ģ�������¼��ĺ���������ģ������¼��������¼���Ӳ���¼�
    �ȡ�
    �亯��ԭ�����£�
        UINT SendInput(UINT nInputs, LPINPUT pInputs, int cbSize);
    ���У�nInputs ����ָ�������¼���������pInputs ����ָ�������¼������ָ�룬cbSize ����ָ����
    ���¼�����Ĵ�С����λΪ�ֽڣ���*/
void mousClick() {
    INPUT input;                //����һ��INPUT���ͽṹ��
    input.type = INPUT_MOUSE;   //ָ�������¼�����Ϊ����¼�
    input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN | MOUSEEVENTF_LEFTUP; // ģ�����������º�̧��Ķ���
    //mi�ǽṹ��INPUT��һ����Ա���ԣ�mi��MOUSEINPUT����
    //MOUSEINPUT �ṹ��������������¼�������������������˫�����Ҽ��������ƶ��Ȳ�����

    input.mi.dx = 0;            //��������¼�������x����
    input.mi.dy = 0;            //��������¼�������y����
    input.mi.mouseData = 0;     //���������ֵĹ�������
    input.mi.dwExtraInfo = 0;   //�� dwExtraInfo �ֶ�����Ϊ 0����ʾ�������κθ��ӵ��������ݡ�
    input.mi.time = 0;          //time�ֶ�����������ʱ����ģ�0��ʾʹ��ϵͳ��ʱ���
    SendInput(1, &input, sizeof(INPUT));
}
void moveMouseAndClick(int x, int y) {
    moveMouse(x,y);
    mousClick();
}