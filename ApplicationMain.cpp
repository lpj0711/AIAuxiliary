#include<stdio.h>
#include"NewBadPersonAuxiliary.h"
#include <iostream>
#include"include/paddleocr.h"
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
    pporc.ocr(img);
    //函数体
    return 0;
}