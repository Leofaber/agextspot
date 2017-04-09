#include "GammaRayDetector.h"
#include "ThresholdBackgroundEvaluator.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "Please insert the path to image in FITS format: " << endl;
	string fitsFilePath = "MappeSimulate/TestImages/50ImgSimF40bg15";
    string simulatedFitsFilesPath = "MappeSimulate/BackgroundImages";

    bool debugMode = false;

    ThresholdBackgroundEvaluator tbe(simulatedFitsFilesPath, debugMode);
	float backgroundThresholdValue = tbe.getBackgroundThresholdValue();

	debugMode = true;

 	GammaRayDetector grd(fitsFilePath,backgroundThresholdValue,debugMode);
	grd.startAnalysis();



	return 0;

}
