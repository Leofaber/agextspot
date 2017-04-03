#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

class Thresholder
{
public:
 	static Mat makeThresholding(cv::Mat inputImage, double t);
private:
	Thresholder();

};

