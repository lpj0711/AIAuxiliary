#include<stdio.h>
#include"NewBadPersonAuxiliary.h"
#include <iostream>
#include"include/paddleocr.h"
using namespace std;
int main(int argc, char* argv[])
{
    //�²����˵ĵ���¼�
    //New_Bad_Person_Auxiliary nbpa;
    //nbpa.keyDown(70);

    //ocrʶ��
    string img_path = "D:/Cwork/source/12.jpg";
    cv::Mat img = cv::imread(img_path);
    PaddleOCR::PPOCR pporc;
    pporc.ocr(img);
    //������
    return 0;
}