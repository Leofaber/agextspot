#include "PixelsMeanEvaluator.h"


PixelsMeanEvaluator::PixelsMeanEvaluator()
{
}



float PixelsMeanEvaluator::getPixelsMean(cv::Mat image) {

	cout << image.rows << image.cols << endl;


	/// Establish the number of bins
	int histSize = 256;

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat imageHist;
	calcHist(&image, 1, 0, Mat(), imageHist, 1, &histSize, &histRange, uniform, accumulate);

	float mean = 0;
	float tot = image.rows*image.cols;
	for (int i = 1; i < histSize; i++){
		mean += imageHist.at<float>(i) * i;
	}
	mean = mean / (tot - imageHist.at<float>(0));
	return mean;

	/*
	float pixelValue = 0;
	for (int i = 0; i<image.rows; i++) {
		for (int j = 0; j<image.cols; j++) {
			pixelValue += (float)image.at<uchar>(i, j);
		}
	}

	return pixelValue / (image.rows*image.cols);*/
}
