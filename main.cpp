
#include <iostream>

#include "lesson/Lesson1.h"
#include "lesson/Lesson2.h"
#include "lesson/Lesson3.h"
#include "lesson/Lesson4.h"
#include "lesson/Lesson5.h"
#include "lesson/Lesson6.h"
#include "lesson/Lesson7.h"
#include "lesson/Lesson8.h"
#include "lesson/Lesson9.h"

using namespace std;

const char *RGB_CIRCLE = "../bitmaps/data1.bmp";
const char *ORIGIN_GRAY8 = "../bitmaps/data2.bmp";
const char *NOISE_GRAY8 = "../bitmaps/data3.bmp";
const char *RICE_GRAY8 = "../bitmaps/data4.bmp";
const char *ORIGIN_BMP_LINE1 = "../bitmaps/data5.bmp";
const char *ORIGIN_BMP_LINE2 = "../bitmaps/data6.bmp";
const char *RICE_BINARY = "../bitmaps/data7.bmp";

int main()
{

    Lesson1::split24BmpToRGB(RGB_CIRCLE);
    cout << "<=========== Lesson1::RGB分离完成! ===========>" << endl;
    Lesson1::cover24BmpToGray8(RGB_CIRCLE);
    cout << "<=========== Lesson1::24位彩色图灰度化完成! ===========>" << endl;
    Lesson1::reverseGray8();
    cout << "<=========== Lesson1::8位灰色图反色完成! ===========>" << endl;

    Lesson2::buildHistogram(ORIGIN_GRAY8);
    cout << "<=========== Lesson2::直方图统计完成! ===========>" << endl;
    Lesson2::equalizeHistogram(ORIGIN_GRAY8);
    cout << "<=========== Lesson2::直方图均衡化完成! ===========>" << endl;


    Lesson3::avgFilterWithoutBorder(NOISE_GRAY8);
    cout << "<=========== Lesson3::均值滤波(无边界)完成! ===========>" << endl;
    Lesson3::avgFilterWithBorder(NOISE_GRAY8);
    cout << "<=========== Lesson3::均值滤波(有边界)完成! ===========>" << endl;
    Lesson3::medianFilterWithoutBorder(NOISE_GRAY8);
    cout << "<=========== Lesson3::中值滤波(无边界)完成! ===========>" << endl;
    Lesson3::medianFilterWithBorder(NOISE_GRAY8);
    cout << "<=========== Lesson3::中值滤波(有边界)完成! ===========>" << endl;


    Lesson4::scale(2.0, 1.5, ORIGIN_GRAY8);
    cout << "<=========== Lesson4::图像放缩完成! ===========>" << endl;
    Lesson4::transform(50, 50, ORIGIN_GRAY8);
    cout << "<=========== Lesson4::图像平移完成! ===========>" << endl;
    Lesson4::mirror(false, ORIGIN_GRAY8);
    cout << "<=========== Lesson4::图像镜像完成! ===========>" << endl;
    Lesson4::rotate(30, ORIGIN_GRAY8);
    cout << "<=========== Lesson4::图像旋转完成! ===========>" << endl;


    Lesson5::configThreshold(128, ORIGIN_GRAY8);
    cout << "<=========== Lesson5::固定阈值 图像分割完成! ===========>" << endl;
    Lesson5::iterationThreshold(ORIGIN_GRAY8);
    cout << "<=========== Lesson5::迭代法求阈值 图像分割完成! ===========>" << endl;
    Lesson5::otsuThreshold(ORIGIN_GRAY8);
    cout << "<=========== Lesson5::大津法求阈值 图像分割完成! ===========>" << endl;


    Lesson6::segmentWithSeed(Point2i(100, 50), 5, RICE_GRAY8);
    cout << "<=========== Lesson6::基于种子的区域增长完成! ===========>" << endl;
    Lesson6::segmentWithoutSeed(RICE_GRAY8);
    cout << "<=========== Lesson6::基于分裂合并的区域增长完成! ===========>" << endl;


    Lesson7::prewittEdgeDetection(ORIGIN_GRAY8);
    cout << "<=========== Lesson7::prewitt算子边缘检测完成! ===========>" << endl;
    Lesson7::sobelEdgeDetection(ORIGIN_GRAY8);
    cout << "<=========== Lesson7::sobel算子边缘检测完成! ===========>" << endl;
    Lesson7::LOGEdgeDetection(ORIGIN_GRAY8);
    cout << "<=========== Lesson7::LOG算子边缘检测完成! ===========>" << endl;


    Lesson8::hough(5, ORIGIN_BMP_LINE1, OUT_BMP_HOUGH1);
    Lesson8::hough(6, ORIGIN_BMP_LINE2, OUT_BMP_HOUGH2);
    cout << "<=========== Lesson7::hough直线检测完成! ===========>" << endl;


    Lesson9::regionMark(RICE_BINARY);
    cout << "<=========== Lesson9::区域标记完成! ===========>" << endl;
    Lesson9::regionPick(RICE_BINARY);
    cout << "<=========== Lesson9::区域提取完成! ===========>" << endl;

    return 0;
}
