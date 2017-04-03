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
	ImagePrinter::printImage(tempImage);

    // FILTERING
	Filterer gaussianFilter(Size(3,3),10);
	tempImage = gaussianFilter.filter(tempImage);
    // PRINTING IMAGE
	ImagePrinter::printImage(tempImage);

    // COMPUTING MEAN
 	float mean = PixelsMeanEvaluator::getPixelsMean(tempImage);
	cout << "mean: " << mean << endl;


    // THRESHOLDING
    tempImage = Thresholder::makeThresholding(tempImage, mean);


	// PRINTING IMAGE
	ImagePrinter::printImage(tempImage);



	// Thresholding then Filtering
	if (analysisMode == "TF")
	{


	}
	// Filtering then Thresolding
	if (analysisMode == "FT")
	{


	}

    	getchar();

}

