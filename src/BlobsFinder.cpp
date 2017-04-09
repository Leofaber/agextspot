#include "BlobsFinder.h"

BlobsFinder::BlobsFinder()
{
    //ctor
}

vector<Blob> BlobsFinder::findBlobs(Mat tempImage, bool debugMode) {




    /// STRETCHING
	cout << "STRETCHING" << endl;
	float r = 0.05;
	tempImage = HistogramStretching::nonLinearStretch(tempImage,r);

	/// PRINTING IMAGE
	if(debugMode){
        ImagePrinter::printImageInWindow(tempImage,"window1");
        ImagePrinter::printImageInConsole(tempImage);
	}








	/// GAUSSIAN FILTERING
    cout << "GAUSSIAN FILTERING" << endl;
	GaussianFilterer gaussianFilter(Size(23, 23), 3.5); // 17x17   2.5
	tempImage = gaussianFilter.filter(tempImage);
	/// PRINTING IMAGE
	if(debugMode){
            ImagePrinter::printImageInConsole(tempImage);
            ImagePrinter::printImageInWindow(tempImage, "window2");
	}





	/// COMPUTING THRESHOLD
    cout << "THRESHOLD" << endl;
	//float threshold = Thresholder::getThresholdFromPeaksMethod(tempImage);
	float threshold = Thresholder::getThresholdFromPercentileMethod(tempImage,99);
	cout << "threshold: " << threshold << endl;
	/// DO THRESHOLDING
	tempImage = Thresholder::makeThresholding(tempImage, threshold);
	/// PRINTING IMAGE
	if(debugMode){
            ImagePrinter::printImageInConsole(tempImage);
            ImagePrinter::printImageInWindow(tempImage, "window3");
	}


    vector<Blob> blobs;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat copyOfImage = tempImage.clone();
    findContours( copyOfImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);


    for(vector<vector<Point> >::iterator i = contours.begin(); i < contours.end(); i++){

        vector<Point> currentBlob = *i;
        blobs.push_back(Blob(currentBlob,tempImage));

    }

    return blobs;
}

