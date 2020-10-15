/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_HISTOGRAM_H
#define IMAGEPROCESS_HISTOGRAM_H

#import "ImageIO.h"

class Histogram
{

private:

    LONG mGrayBuffer[256];

    BMP mGrayBmp;

public:

    Histogram(BMP bmp);


    /**
     * 构建灰度直方图
     * @return 直方图BMP
     */
    BMP buildHistogramBmp();


    /**
     * 直方图均衡化
     * @return
     */
    BMP equalizeBmp();

};


#endif //IMAGEPROCESS_HISTOGRAM_H
