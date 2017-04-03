#include <iostream>
#include <string>
#include "GammaRayDetector.h";



using namespace std;



int main(){

	/*INPUT PATH TO FITS FILE*/
 	cout << "Please insert the path to image in FITS format: " << endl;
	string fitsFilePath = "/home/giancarlo/Documenti/università/Secondo anno/Computer Vision/Computer Vision - Bulgarelli/MappeSimulate/ImgSimF80bg15/0000000008_001_GRBTESTMAP.cts";
	//getline(cin, fitsFilePath);


	/*INPUT ANALYSIS MODE*/
	cout << "Please insert a analysis mode: \nTF (Thresholding then Filtering) or \nFT (Filtering then Thresholding)" << endl;
	string inputMode;
	//getline(cin, inputMode);
 	inputMode = "TF";
 	if ((inputMode != "TF") && (inputMode != "FT") ){
		cout << "Input Error. You inserted " << inputMode << ". Insert instead TF or FT" << endl;
		getchar();
		return 0;
	}


	/*INPUT THRESHOLDING MODE*/
	cout << "Please insert how to compute the threshold for the thresholding step: \nTR (Compute the threshold from the real image) or \nTS (Compute the threshold from simulated images)" << endl;
	string thresholdMode;
	//getline(cin, thresholdMode);
	thresholdMode = "TR";
	if (thresholdMode != "TR" && thresholdMode != "TS"){
		cout << "Input Error. You inserted " << thresholdMode << ". Insert instead TR or TS" << endl;
		getchar();
		return 0;
	}


	/*INPUT PATH TO SIMULATED FITS FILES*/
	string simulatedFitsFilesPath;
	if (thresholdMode == "TS"){
		cout << "Please insert the path to the simulated images in FITS format: " << endl;
 		getline(cin, simulatedFitsFilesPath);

	}





	GammaRayDetector grd(fitsFilePath, simulatedFitsFilesPath, inputMode, thresholdMode);
	grd.detect();


	return 0;
}

/*
void showImages(vector<string> filenames){
FitsToCvMatConverter ftcvc;
int c = 0;
for (vector<string>::iterator image_path_it = filenames.begin(); image_path_it != filenames.end(); ++image_path_it)
{
Mat image = ftcvc.convertFitsToCvMat(*image_path_it);
stretching(&image);
namedWindow("Image" + c, CV_WINDOW_AUTOSIZE);
imshow("Image" + c, image);
c++;
}
}
*/

 /*
	// Draw the histogram
	int hist_w = 512; int hist_h = 500;
	int bin_w = cvRound((double)hist_w / histSize);

	Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

	/// Draw a line for each grey level
	for (int i = 1; i < histSize; i++)
	{
		cout << "Grey level " << i - 1 << " Count: " << imageHist.at<float>(i - 1) << endl;
		line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(imageHist.at<float>(i - 1))),
			Point(bin_w*(i), hist_h - cvRound(imageHist.at<float>(i))),
			Scalar(255, 0, 0), 2, 8, 0);

	}


	namedWindow("Image", CV_WINDOW_AUTOSIZE);
	imshow("Image", image);
	/// Display
	namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
	imshow("calcHist Demo", histImage);

	//waitKey(0);
    */
