#ifndef IMAGEPRINTER_H
#define IMAGEPRINTER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "stdio.h"
using namespace cv;
using namespace std;

class ImagePrinter
{
    public:
        static void printImage(Mat inputImage);
    protected:
    private:
        ImagePrinter();
};

#endif // IMAGEPRINTER_H
