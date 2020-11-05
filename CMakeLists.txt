cmake_minimum_required(VERSION 3.15)
project(ImageProcess)

set(CMAKE_CXX_STANDARD 14)

add_executable(ImageProcess main.cpp utils/ImageIO.h utils/ImageIO.cpp lesson/Lesson1.cpp lesson/Lesson1.h lesson/Lesson2.cpp lesson/Lesson2.h utils/Histogram.cpp utils/Histogram.h lesson/Lesson3.cpp lesson/Lesson3.h utils/Filter.cpp utils/Filter.h lesson/Lesson4.cpp lesson/Lesson4.h utils/MatrixUtil.cpp utils/MatrixUtil.h lesson/Lesson5.cpp lesson/Lesson5.h lesson/Lesson6.cpp lesson/Lesson6.h lesson/Lesson7.cpp lesson/Lesson7.h)