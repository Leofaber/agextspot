#pragma once

#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

class PixelsMeanEvaluator
{
public:
 	static float getPixelsMean(string path);
	static float getPixelsMean(cv::Mat image);
private:
    PixelsMeanEvaluator();

};

