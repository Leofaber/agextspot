#include "GammaRayDetector.h"
#include "GammaRayDetector.h"




GammaRayDetector::GammaRayDetector(string _fitsFilePath, string _fitsSimulatedFilePath, string _analysisMode, string _thresholdMode)
{
	fitsFilePath = _fitsFilePath;
	fitsSimulatedFilePath = _fitsSimulatedFilePath;
	analysisMode = _analysisMode;
	thresholdMode = _thresholdMode;

	agileImage = fcmc.convertFitsToCvMat(fitsFilePath);


}


GammaRayDetector::~GammaRayDetector()
{
}

void GammaRayDetector::detect()
{

	Mat tempImage = agileImage.clone();


	// STRETCHING
	tempImage = HistogramStretching::stretch(tempImage);

	// PRINTING IMAGE
	ImagePrinter::printImageInWindow(tempImage,"window1");
	//ImagePrinter::printImageInConsole(tempImage);

	// FILTERING
	GaussianFilterer gaussianFilter(Size(7, 7), 3);
	tempImage = gaussianFilter.filter(tempImage);
	// PRINTING IMAGE
	//ImagePrinter::printImageInConsole(tempImage);
	ImagePrinter::printImageInWindow(tempImage, "window2");

	// FILTERING
	GaussianFilterer gaussianFilter4Histogram(Size(3, 3), 1);
	tempImage = gaussianFilter.filter(tempImage);

	// PRINTING IMAGE
	//ImagePrinter::printImageInConsole(tempImage);
	ImagePrinter::printImageInWindow(tempImage, "window3");



	// COMPUTING MEAN
	float mean = PixelsMeanEvaluator::getPixelsMean(tempImage);
	//cout << "mean: " << mean << endl;


	// COMPUTING THRESHOLD
	float threshold = Thresholder::getThresholdFromPeaksMethod(tempImage);
	cout << "threshold: " << threshold << endl;


	// THRESHOLDING
	tempImage = Thresholder::makeThresholding(tempImage, threshold);
	ImagePrinter::printImageInConsole(tempImage);
	ImagePrinter::printImageInWindow(tempImage, "window2");


	// STRETCHING
	tempImage = HistogramStretching::stretch(tempImage);
	// PRINTING IMAGE
	ImagePrinter::printImageInWindow(tempImage, "window2");






	// Thresholding then Filtering
	if (analysisMode == "TF")
	{


	}
	// Filtering then Thresolding
	if (analysisMode == "FT")
	{


	}

	//getchar();

}

