
#include <iostream>

#include "lesson/Lesson1.h"
#include "lesson/Lesson2.h"
#include "lesson/Lesson3.h"
#include "lesson/Lesson4.h"


const char *ORIGIN_BMP = "../bitmaps/test5.bmp";

//const char *ORIGIN_BMP_GRAY8 = "../bitmaps/lesson1/test/image_gray8.bmp";

const char *ORIGIN_BMP_GRAY8 = "../bitmaps/image2.bmp";


int main()
{
//    Lesson1::split24BmpToRGB(ORIGIN_BMP);
//    Lesson1::cover24BmpToGray8(ORIGIN_BMP);
//    Lesson1::reverseGray8();

//    Lesson2::buildHistogram(ORIGIN_BMP_GRAY8);
//    Lesson2::equalizeHistogram(ORIGIN_BMP_GRAY8);


    Lesson3::avgFilterWithoutBorder(ORIGIN_BMP_GRAY8);
    Lesson3::avgFilterWithBorder(ORIGIN_BMP_GRAY8);
    Lesson3::medianFilterWithoutBorder(ORIGIN_BMP_GRAY8);
    Lesson3::medianFilterWithBorder(ORIGIN_BMP_GRAY8);




    return 0;
}
