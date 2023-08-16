#include "GetAndOpreateWindow.h"
#include <iostream>
#include<Windows.h>
using namespace std;

//�Ӵ��ڻص�����
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);
    if (strlen(title) > 0)
        cout << hex << "�����" << hwnd << "  ���⣺" << title << endl;
    return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);
    if (strlen(title) > 0)
        cout << hex << "�����" << hwnd << "  ���⣺" << title << endl;
    EnumChildWindows(hwnd, EnumChildWindowsProc, NULL);
    return true;
}

BOOL myEnumWindow(HWND hwnd)
{
    char title[100] = { 0 };
    HWND after = NULL;
    while (after = ::FindWindowEx(hwnd, after, NULL, NULL))
    {
        GetWindowTextA(after, title, 100);
        if (strlen(title) > 0)
            cout << "�����" << hex << after << "  ���⣺" << title << endl;
        myEnumWindow(after);
    }
    return true;
}

LPCWSTR stringToLPCWSTR(std::string orig)
{
    wchar_t* wcstring = 0;
    try
    {
        size_t origsize = orig.length() + 1;
        const size_t newsize = 100;
        size_t convertedChars = 0;
        if (orig == "")
        {
            wcstring = (wchar_t*)malloc(0);
            mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
        }
        else
        {
            wcstring = (wchar_t*)malloc(sizeof(wchar_t) * (orig.length() - 1));
            mbstowcs_s(&convertedChars, wcstring, origsize, orig.c_str(), _TRUNCATE);
        }
    }
    catch (std::exception e)
    {
    }
    return wcstring;
}

void Get_And_Opreate_Window::GetWindowsSize(){
    HWND handle = NULL;
    string Ipwindowsname = "���������";
    LPCWSTR aa = stringToLPCWSTR(Ipwindowsname);
    FindWindow(NULL, aa);//�����ض����ڵĴ��ھ��
    RECT rect;
    int width, height;
    if (handle)
    {
        GetWindowRect(handle, &rect);//��ȡ������Ϣ
        width = rect.right - rect.left, height = rect.bottom - rect.top;
        cout << "��: " << width << endl << "��: " << height << endl;
        cout << MoveWindow(handle, 100, 100, width, height, true) << endl;
    }
    //ʹ��EnumWindowsö�ٴ��ڣ���ȡ���ж���ɼ����ڼ����ǵ��Ӵ���
    EnumWindows(EnumWindowsProc, NULL);

    cout << endl << endl << "�ڶ��ַ�����" << endl;
    myEnumWindow(NULL);//ʹ��FindWindowExö�ٴ���

    getchar();
    getchar();
}