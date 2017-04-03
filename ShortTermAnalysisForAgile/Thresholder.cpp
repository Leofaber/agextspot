#include "Thresholder.h"
#include "Thresholder.h"


Thresholder::Thresholder()
{
}


Mat Thresholder::makeThresholding(Mat inputImage, double t) {
	Mat destinationImage;
	double maxValue = 255;
 	threshold(inputImage, destinationImage, t, maxValue, THRESH_TOZERO);
	return destinationImage;
}
