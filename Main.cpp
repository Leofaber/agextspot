#include "GammaRayDetector.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "WELCOME TO AGILE GAMMA RAY FLARES (IN SHORT TERM IMAGES) DETECTOR" << endl;
    cout << "press any key to start!" <<endl;
    getchar();



	string testSetPath = "MappeSimulate/TestImages/50ImgSimF80bg15";

    string simulatedFluxFitsFilesPath = "MappeSimulate/FluxImages/50ImgSimF80bg0";

    string simulatedBackgroundFitsFilesPath = "MappeSimulate/BackgroundImages";



    /// Classe per il calcolo della permormance
    ErrorEstimator* ee = new ErrorEstimator(100,100,"flux",50);



    bool debugMode = false;
    /// Classificatore Bayesiano per la classificazione dei blobs in flusso/background
    BayesianClassifierForBlobs* reverendoBayes = new BayesianClassifierForBlobs(simulatedBackgroundFitsFilesPath,simulatedFluxFitsFilesPath,debugMode);



	debugMode = true;
	/// Classe per la rilevazione delle sorgenti di raggi gamma
    GammaRayDetector grd(testSetPath,reverendoBayes,ee,debugMode);
    grd.startAnalysis();


    getchar();
	return 0;

}
