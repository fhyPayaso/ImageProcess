
#include <iostream>

#include "utils/MockUtil.h"

#include "lesson/Lesson1.h"
#include "lesson/Lesson2.h"
#include "lesson/Lesson3.h"
#include "lesson/Lesson4.h"
#include "lesson/Lesson5.h"
#include "lesson/Lesson6.h"
#include "lesson/Lesson7.h"
#include "lesson/Lesson8.h"


const char *ORIGIN_BMP = "../bitmaps/test5.bmp";

const char *ORIGIN_BMP_GRAY8 = "../bitmaps/lesson1/test/image_gray8.bmp";

const char *ORIGIN_BMP_RICE = "../bitmaps/rice.bmp";

//const char *ORIGIN_BMP_LINE = "../bitmaps/image3.bmp";
const char *ORIGIN_BMP_LINE = "../bitmaps/5.bmp";
//const char *ORIGIN_BMP_LINE = "../bitmaps/hough_line.bmp";


int main()
{
//    Lesson1::split24BmpToRGB(ORIGIN_BMP);
//    Lesson1::cover24BmpToGray8(ORIGIN_BMP);
//    Lesson1::reverseGray8();

//    Lesson2::buildHistogram(ORIGIN_BMP_GRAY8);
//    Lesson2::equalizeHistogram(ORIGIN_BMP_GRAY8);

//    Lesson3::avgFilterWithoutBorder(ORIGIN_BMP_GRAY8);
//    Lesson3::avgFilterWithBorder(ORIGIN_BMP_GRAY8);
//    Lesson3::medianFilterWithoutBorder(ORIGIN_BMP_GRAY8);
//    Lesson3::medianFilterWithBorder(ORIGIN_BMP_GRAY8);

//    Lesson4::scale(2.0, 1.5, ORIGIN_BMP_GRAY8);
//    Lesson4::transform(50, 50, ORIGIN_BMP_GRAY8);
//    Lesson4::mirror(false, ORIGIN_BMP_GRAY8);
//    Lesson4::rotate(30, ORIGIN_BMP_GRAY8);
//
//    Lesson5::configThreshold(128, ORIGIN_BMP_GRAY8);
//    Lesson5::otsuThreshold(ORIGIN_BMP_GRAY8);
//    Lesson5::iterationThreshold(ORIGIN_BMP_GRAY8);

//    Lesson6::segmentWithSeed(Point2i(100, 50), 5, ORIGIN_BMP_RICE);
//    Lesson6::segmentWithoutSeed(ORIGIN_BMP_RICE);

//    Lesson7::prewittEdgeDetection(ORIGIN_BMP_GRAY8);
//    Lesson7::sobelEdgeDetection(ORIGIN_BMP_GRAY8);
//    Lesson7::LOGEdgeDetection(ORIGIN_BMP_GRAY8);

//    MockUtil::genLineBMP(ORIGIN_BMP_GRAY8);
    Lesson8::hough(6, ORIGIN_BMP_LINE);


    return 0;
}
