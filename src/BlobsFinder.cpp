#include "BlobsFinder.h"

BlobsFinder::BlobsFinder()
{
    //ctor
}

vector<Blob> BlobsFinder::findBlobs(Mat tempImage, bool debugMode) {

    Mat photonImage = tempImage.clone();


    /// STRETCHING
 	float r = 0.05;
	tempImage = HistogramStretching::nonLinearStretch(tempImage,r);


	/// PRINTING IMAGE
	if(debugMode){
        cout << "Stretching complete" <<endl;
//        ImagePrinter::printImageInConsole(tempImage);
        ImagePrinter::printImageInWindow(tempImage,"window1");

	}








	/// GAUSSIAN FILTERING
	GaussianFilterer gaussianFilter(Size(23, 23), 3); // 17x17   2.5
	tempImage = gaussianFilter.filter(tempImage);


	/// PRINTING IMAGE
	if(debugMode){
        cout << "Gaussian Filtering complete" << endl;

        //ImagePrinter::printImageInConsole(tempImage);
        ImagePrinter::printImageInWindowWithStretching(tempImage, "window2");
	}





	/// COMPUTING THRESHOLD
	//float threshold = Thresholder::getThresholdFromPeaksMethod(tempImage);
	float threshold = Thresholder::getThresholdFromPercentileMethod(tempImage,98.7);
	//cout << "threshold: " << threshold << endl;
	/// DO THRESHOLDING
	tempImage = Thresholder::makeThresholding(tempImage, threshold);

	/// PRINTING IMAGE
	if(debugMode){
        cout << "Thresholding complete." << endl;
        //ImagePrinter::printImageInConsole(tempImage);
        ImagePrinter::printImageInWindowWithStretching(tempImage, "window3");
	}


    vector<Blob> blobs;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat copyOfImage = tempImage.clone();
    findContours( copyOfImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);


    for(vector<vector<Point> >::iterator i = contours.begin(); i < contours.end(); i++){

        vector<Point> currentBlob = *i;
        blobs.push_back(Blob(currentBlob,tempImage,photonImage));

    }

    return blobs;
}

