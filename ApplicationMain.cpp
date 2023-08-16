#include<stdio.h>
#include"NewBadPersonAuxiliary.h"
#include <iostream>
#include"include/paddleocr.h"
#include"GetAndOpreateWindow.h"
using namespace std;
int main(int argc, char* argv[])
{
    //新不良人的点击事件
    //New_Bad_Person_Auxiliary nbpa;
    //nbpa.keyDown(70);

    //ocr识别
    string img_path = "D:/Cwork/source/12.jpg";
    cv::Mat img = cv::imread(img_path);
    PaddleOCR::PPOCR pporc;
    vector <PaddleOCR::OCRPredictResult> result = pporc.ocr(img);
    cout << "这个会不会成功" << endl;
    for (PaddleOCR::OCRPredictResult res :result)
    {

        cout << "这个会不会成功"+ res.text << endl;
    }
    //函数体
    Get_And_Opreate_Window getAndOpreateWindow;
    getAndOpreateWindow.GetWindowsSize();
    return 0;
}