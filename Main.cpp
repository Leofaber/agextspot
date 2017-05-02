#include "GammaRayDetector.h"

///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(){


    cout << "WELCOME TO AGILE GAMMA RAY FLARES (IN SHORT TERM IMAGES) DETECTOR" << endl;
    cout << "press any key to start!" <<endl;
    getchar();


    /// Il path al training set composto da 1000 immagini formato FITS (500 grb f=40,80,120,160,200 bg=0 , 500 background con f=0 bg=15)
    /// Il training set è all'interno della root del progetto
    string trainingSet = "Dataset1000/TrainingSet";



    /// Il path al test set. I test set disponibili sono i seguenti:
    /// TestSet Standard: 500 immagini formato FITS (250 grb f=40,80,120,160,200 bg=15 , 250 background con f=0 bg=15)
    /// MediumTestSet: 500 immagini formato FITS (250 grb f=80 bg=15 , 250 background con f=0 bg=15)
    /// HardTestSet: 500 immagini formato FITS (250 grb f=40 bg=15 , 250 background con f=0 bg=15)
    string workPath = "Dataset1000/MediumTestSet";


    /// GammaRayDetector(bool validationMode , string workPath, bool showImagesMode)
    GammaRayDetector grd(true,workPath,false);

    //grd.trainBayesianClassifier(trainingSet);


    grd.startAnalysis();


    getchar();
	return 0;

}
