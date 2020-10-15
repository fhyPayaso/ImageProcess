/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 滤波器类
# ====================================================*/
#ifndef IMAGEPROCESS_FILTER_H
#define IMAGEPROCESS_FILTER_H

#import "ImageIO.h"
#include <algorithm>
#include <string>

const int hMove[9] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
const int wMove[9] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

class Filter
{

private:


public:

    static BMP averageWithoutBorder(BMP bmp);

    static BMP averageWithBorder(BMP bmp);

    static BMP midWithoutBorder(BMP bmp);

    static BMP midWithBorder(BMP bmp);

};


#endif //IMAGEPROCESS_FILTER_H
