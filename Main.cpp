#include "GammaRayDetector.h"

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

    ErrorEstimator* ee = new ErrorEstimator(100,100,"flux",50);



    bool debugMode = false;


    BayesianClassifierForBlobs* reverendoBayes = new BayesianClassifierForBlobs(simulatedBackgroundFitsFilesPath,simulatedFluxFitsFilesPath,debugMode);









	debugMode = true;

    GammaRayDetector grd(fitsFilePath,reverendoBayes,ee,debugMode);
    grd.startAnalysis();


    getchar();
	return 0;

}
