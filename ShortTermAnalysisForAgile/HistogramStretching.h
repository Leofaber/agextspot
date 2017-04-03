#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace std;
using namespace cv;

class HistogramStretching
{
public:
	static Mat stretch(Mat image);
protected:
private:
	HistogramStretching();
};