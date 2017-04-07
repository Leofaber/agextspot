#pragma once

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
using namespace std;
using namespace cv;

class PixelsMeanEvaluator
{
public:
	//static float getWeightedPixelsMean(string path);
	static float getWeightedPixelsMean(Mat image);
	static float getPixelsMean(Mat image);
private:
	PixelsMeanEvaluator();
	static Mat computeHistogram(Mat image, int histSize);
	static void drawHistogram(Mat histogram, int histSize);


};

