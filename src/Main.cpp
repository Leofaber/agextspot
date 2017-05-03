#include "GammaRayDetector.h"


///  BitBucket address
///  git@bitbucket.org:GZHeisenberg/shorttermanalysisforagilefinal.git


using namespace std;



int main(int argc, char*argv[]){

    if( argc >= 2 && argc <=3 ) {


        bool showImagesFlag = false;

        if(argc==3 && (string)argv[2]=="t")
            showImagesFlag = true;

        string workPath = (string)argv[1];//"Dataset1000/TestSet";


        cout << "**********************************************************************" << endl;
        cout << "WELCOME TO AGILE GAMMA RAY BURST (IN SHORT TERM ANALYSIS) DETECTOR" << endl;
        cout << "press any key to start!"<<endl;
        cout << "**********************************************************************" << endl;

        getchar();

        /** Il path al training set composto da 1000 immagini formato FITS (500 grb f=40,80,120,160,200 bg=0 , 500 background con f=0 bg=15)
        Il training set è all'interno della root del progetto
        */
        string trainingSet = "Dataset1000/TrainingSet";

        /** Il path al test set. I test set disponibili sono i seguenti:
            TestSet Standard: 500 immagini formato FITS (250 grb f=40,80,120,160,200 bg=15 , 250 background con f=0 bg=15)
            MediumTestSet: 500 immagini formato FITS (250 grb f=80 bg=15 , 250 background con f=0 bg=15)
            HardTestSet: 500 immagini formato FITS (250 grb f=40 bg=15 , 250 background con f=0 bg=15)
        */

        /** GammaRayDetector(
                bool validationMode -> se il software vuole essere usato per scopi valutativi
                string workPath -> il path al dataset
                bool showImagesMode -> per mostrare le immagini nelle opencv windows
        )
        */


        GammaRayDetector grd(false,workPath,showImagesFlag);
        //grd.trainBayesianClassifier(trainingSet);
        grd.startAnalysis();


    }
    else if( argc > 3 ) {
        printf("Too many arguments supplied.\n  -the image folder path \n   -t [optional] to show the image analysis process.\n");

    }
    else {
        printf("Two arguments expected.\n   -the image folder path \n   -t [optional] to show the image analysis process.\n");
    }
    return 0;

}
