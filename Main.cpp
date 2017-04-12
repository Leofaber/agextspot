#include "GammaRayDetector.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "WELCOME TO AGILE GAMMA RAY FLARES (IN SHORT TERM IMAGES) DETECTOR" << endl;
    cout << "press any key to start!" <<endl;
    getchar();



	string testSetPath = "Dataset/TestSet";

    string trainSetFlux = "Dataset/TrainSet/flux";

    string trainSetBg = "Dataset/TrainSet/bg";



    /// Classe per il calcolo della permormance
    ErrorEstimator* ee = new ErrorEstimator(100,100,"flux",50);



    bool debugMode = false;
    /// Classificatore Bayesiano per la classificazione dei blobs in flusso/background
    BayesianClassifierForBlobs* reverendoBayes = new BayesianClassifierForBlobs(trainSetBg,trainSetFlux,debugMode);



	debugMode = false;
	/// Classe per la rilevazione delle sorgenti di raggi gamma
    GammaRayDetector grd(testSetPath,reverendoBayes,ee,debugMode);
    grd.startAnalysis();


    getchar();
	return 0;

}
