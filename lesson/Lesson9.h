/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON9_H
#define IMAGEPROCESS_LESSON9_H


#include "../utils/ImageIO.h"
#include <queue>

const static char *OUT_BMP_REGION_MARK = "../bitmaps/lesson9/region_mark.bmp";
const static char *OUT_BMP_REGION_PICK = "../bitmaps/lesson9/region_pick.bmp";

class Lesson9
{

public:

    static void regionMark(const char *bmp_in_dir,
                           const char *bmp_out_dir = OUT_BMP_REGION_MARK);

    static void regionPick(const char *bmp_in_dir,
                           const char *bmp_out_dir = OUT_BMP_REGION_PICK);


};


#endif //IMAGEPROCESS_LESSON9_H
