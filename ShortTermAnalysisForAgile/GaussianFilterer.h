#pragma once

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;


class GaussianFilterer
{
public:
	GaussianFilterer(Size kernelSize, double sigma);
	virtual ~GaussianFilterer();
	Mat filter(Mat inputImg);
protected:
private:
	Size kernelSize;
	double sigma;
};

