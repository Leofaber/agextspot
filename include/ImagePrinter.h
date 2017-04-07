#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "stdio.h"
#include "Blob.h"
using namespace cv;
using namespace std;

class ImagePrinter
{
public:
	static void printImageInConsole(Mat inputImage);
	static void printImageInWindow(Mat inputImage, string windowName);
	static void printImageBlob(Mat inputImage, Blob b, string windowName);

private:
	ImagePrinter();
};
