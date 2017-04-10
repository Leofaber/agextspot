#include "GammaRayDetector.h"
#include "BlobsDistributionEvaluator.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "WELCOME TO AGILE GAMMA RAY FLARES SHORT TERM DETECTOR" << endl;
    cout << "press any key to start!" <<endl;
    getchar();



	string fitsFilePath = "MappeSimulate/TestImages/50ImgSimF40bg15";

    string simulatedFluxFitsFilesPath = "MappeSimulate/FluxImages/50ImgSimF80bg0";

    string simulatedBackgroundFitsFilesPath = "MappeSimulate/BackgroundImages";

    bool debugMode = false;

    BlobsDistributionEvaluator fluxBlobsEvaluator(simulatedFluxFitsFilesPath, debugMode);
	GaussianDistribution fluxGD = fluxBlobsEvaluator.getMeanAndDeviation();

	cout << "\n *** Analysis of Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxGD.mean <<endl;
    cout << "Standard Deviation: " << fluxGD.deviation << endl;
    getchar();

    BlobsDistributionEvaluator bgBlobsEvaluator(simulatedBackgroundFitsFilesPath, debugMode);
	GaussianDistribution bgGD = bgBlobsEvaluator.getMeanAndDeviation();

    cout << "\n *** Analysis of Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgGD.mean <<endl;
    cout << "Standard Deviation: " << bgGD.deviation << endl;
    getchar();




	float backgroundThresholdValue = bgGD.mean;
	float backgroundThresholdDeviation = bgGD.deviation;

	debugMode = true;

 	GammaRayDetector grd(fitsFilePath,backgroundThresholdValue,backgroundThresholdDeviation,debugMode);
	grd.startAnalysis();



	return 0;

}
