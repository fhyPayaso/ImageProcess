/* ====================================================
#   Copyright (C)2019 2020 fhyPayaso All rights reserved.
#
#   @Author        : fhyPayaso
#   @Email         : 401619823@qq.com
#   @Description   : 
# ====================================================*/
#ifndef IMAGEPROCESS_LESSON4_H
#define IMAGEPROCESS_LESSON4_H


#include <cmath>
#include "../utils/ImageIO.h"


class Lesson4
{

private:
    static int i;
    static int j;

public:

    static void test()
    {
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                printf("====\n");
            }
        }
    }
};


#endif //IMAGEPROCESS_LESSON4_H
