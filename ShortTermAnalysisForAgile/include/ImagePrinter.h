#pragma once
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
	static void printImageInConsole(Mat inputImage);
	static void printImageInWindow(Mat inputImage, string windowName);
protected:
private:
	ImagePrinter();
};
