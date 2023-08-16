#include "GetAndOpreateWindow.h"
#include <iostream>
#include<Windows.h>
using namespace std;

//子窗口回调函数
BOOL CALLBACK EnumChildWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);
    if (strlen(title) > 0)
        cout << hex << "句柄：" << hwnd << "  标题：" << title << endl;
    return true;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    char title[100] = { 0 };
    GetWindowTextA(hwnd, title, 100);
    if (strlen(title) > 0)
        cout << hex << "句柄：" << hwnd << "  标题：" << title << endl;
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
            cout << "句柄：" << hex << after << "  标题：" << title << endl;
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
    string Ipwindowsname = "任务管理器";
    LPCWSTR aa = stringToLPCWSTR(Ipwindowsname);
    FindWindow(NULL, aa);//查找特定窗口的窗口句柄
    RECT rect;
    int width, height;
    if (handle)
    {
        GetWindowRect(handle, &rect);//获取窗口信息
        width = rect.right - rect.left, height = rect.bottom - rect.top;
        cout << "宽: " << width << endl << "高: " << height << endl;
        cout << MoveWindow(handle, 100, 100, width, height, true) << endl;
    }
    //使用EnumWindows枚举窗口，获取所有顶层可见窗口及他们的子窗口
    EnumWindows(EnumWindowsProc, NULL);

    cout << endl << endl << "第二种方法：" << endl;
    myEnumWindow(NULL);//使用FindWindowEx枚举窗口

    getchar();
    getchar();
}