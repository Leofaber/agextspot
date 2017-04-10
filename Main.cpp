#include "GammaRayDetector.h"
#include "BlobsDistributionEvaluator.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "WELCOME TO AGILE GAMMA RAY FLARES SHORT TERM DETECTOR" << endl;
    cout << "press any key to start!" <<endl;
    getchar();



	string fitsFilePath = "MappeSimulate/TestImages/50ImgSimF80bg15";

    string simulatedFluxFitsFilesPath = "MappeSimulate/FluxImages/50ImgSimF80bg0";

    string simulatedBackgroundFitsFilesPath = "MappeSimulate/BackgroundImages";

    bool debugMode = false;

    BlobsDistributionEvaluator fluxBlobsEvaluator(simulatedFluxFitsFilesPath, debugMode);
	normal_distribution<double> fluxGD = fluxBlobsEvaluator.getMeanAndDeviation();

	cout << "\n *** Analysis of Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxGD.mean() <<endl;
    cout << "Standard Deviation: " << fluxGD.stddev() << endl;
    getchar();

    BlobsDistributionEvaluator bgBlobsEvaluator(simulatedBackgroundFitsFilesPath, debugMode);
	normal_distribution<double> bgGD = bgBlobsEvaluator.getMeanAndDeviation();


    cout << "\n *** Analysis of Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgGD.mean() <<endl;
    cout << "Standard Deviation: " << bgGD.stddev() << endl;
    getchar();





	debugMode = true;

 	GammaRayDetector grd(fitsFilePath,fluxGD,bgGD,debugMode);
	grd.startAnalysis();



	return 0;

}
