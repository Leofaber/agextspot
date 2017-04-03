#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

class Thresholder
{
public:
	static Mat makeThresholding(cv::Mat inputImage, double t);
	static int getThresholdFromPeaksMethod(Mat histogram);

private:
	Thresholder();

};

