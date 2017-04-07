#include "PixelsMeanEvaluator.h"


PixelsMeanEvaluator::PixelsMeanEvaluator()
{
}

Mat PixelsMeanEvaluator::computeHistogram(Mat image, int histSize){
	

	/// Set the ranges ( for B,G,R) )
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat imageHist;
	calcHist(&image, 1, 0, Mat(), imageHist, 1, &histSize, &histRange, uniform, accumulate);
	return imageHist;
}


float PixelsMeanEvaluator::getWeightedPixelsMean(Mat image) {

	/// Establish the number of bins
	int histSize = 256;
	Mat imageHist = computeHistogram(image, histSize);
	

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

float PixelsMeanEvaluator::getPixelsMean(cv::Mat image) {
	/// Establish the number of bins
	int histSize = 256;
	Mat imageHist = computeHistogram(image, histSize);
	drawHistogram(imageHist,histSize);

	float mean = 0;
	float tot = image.rows*image.cols;
	for (int i = 1; i < histSize; i++){
		mean += imageHist.at<float>(i) * i;
	}
	cout << "mean= " << mean << "/ " << (tot - imageHist.at<float>(0)) << endl;

	mean = mean / (tot - imageHist.at<float>(0));
	return mean;
}

void PixelsMeanEvaluator::drawHistogram(Mat histogram, int histSize){
	int hist_w = 512; int hist_h = 500;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Draw a line for each grey level
	for (int i = 1; i < histSize; i++)
	{
		cout << "Grey level " << i - 1 << " Count: " << histogram.at<float>(i - 1) << endl;
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histogram.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(histogram.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);

	}
 
	namedWindow("histogram", CV_WINDOW_AUTOSIZE);
	imshow("histogram", histImage);
	//waitKey(0);
}
