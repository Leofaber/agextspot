#include "GammaRayDetector.h"
#include "ThresholdBackgroundEvaluator.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){



	/*INPUT PATH TO FITS FILE*/
	cout << "Please insert the path to image in FITS format: " << endl;
	string fitsFilePath = "MappeSimulate/ImgSimF80bg15";
	//getline(cin, fitsFilePath);

    string simulatedFitsFilesPath = "MappeSimulate/BackgroundImages";

    bool debugMode = false;

    ThresholdBackgroundEvaluator tbe(fitsFilePath, debugMode);
	float backgroundThresholdValue = tbe.getBackgroundThresholdValue();

 	GammaRayDetector grd(fitsFilePath,backgroundThresholdValue,debugMode);
	grd.startAnalysis();



	return 0;

}
