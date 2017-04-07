#include <iostream>
#include <string>
#include "GammaRayDetector.h"
#include "FolderManager.h"
#include <stdio.h>




using namespace std;



int main(){

	/*INPUT PATH TO FITS FILE*/
	cout << "Please insert the path to image in FITS format: " << endl;
	string fitsFilePath = "MappeSimulate/ImgSimF40bg15";
	//getline(cin, fitsFilePath);




	/*INPUT ANALYSIS MODE*/
	cout << "Please insert a analysis mode: \nTF (Thresholding then Filtering) or \nFT (Filtering then Thresholding)" << endl;
	string inputMode;
	//getline(cin, inputMode);
	inputMode = "TF";
	if ((inputMode != "TF") && (inputMode != "FT")){
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
	grd.startAnalysis();



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

