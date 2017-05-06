#include "GammaRayDetector.h"


///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(int argc, char*argv[]){

    if( argc > 2) {



        string imagePath = (string)argv[1];
        string outputLogName = (string)argv[2];


        cout << "**********************************************************************" << endl;
        cout << "WELCOME TO AGILE GAMMA RAY BURST (IN SHORT TERM ANALYSIS) DETECTOR" << endl;
        cout << "**********************************************************************" << endl;


        GammaRayDetector grd(imagePath,outputLogName);
        //grd.trainBayesianClassifier(trainingSet);
        grd.startAnalysis();


    }
    else if( argc > 3 ) {
        printf("Too many arguments supplied.\n  -the image folder path \n   -the name of output log file\n");

    }
    else {
        printf("Two arguments expected.\n   -the image folder path \n   -the name of output log file.\n");
    }
    return 0;

}
