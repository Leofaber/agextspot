#include "ErrorEstimator.h"

ErrorEstimator::ErrorEstimator(int row, int cols, string _imagesTypes, int _numberOfImages)
{
    center.x=row/2;
    center.y=cols/2;
    imagesTypes = _imagesTypes;
    numberOfImages = _numberOfImages;
//    fluxCount = 0;

}


float ErrorEstimator ::getDistanceFromCenter(Blob* b) {
    float distance =  0;
    Point c = b->getCentroid();
    float arg =  pow(c.x - center.x,2) +pow (c.y - center.y,2) ;
    distance = pow(arg , 0.5);
    cout << "Errore stimato: " << distance << endl;
    return distance;
}

 void ErrorEstimator :: updateErrorList(Blob* b, string fileName) {
    char classChar = fileName.at(0);
    cout << "Il primo carattere " << classChar << endl;
     if(b==nullptr && classChar=='F'){
        fClass++;
        addFalseNegativeCount();
     }
     else if (b!=nullptr && classChar=='F'){
        fClass++;
        addTruePositiveCount();
        float error = getDistanceFromCenter(b);
        errorListElement.push_back(error);
    }
    else if(b==nullptr && classChar=='B') {
        bClass++;
        addTrueNegativeCount();
    }
    else {
        bClass++;
        addFalseNegativeCount();
    }
        //addFluxCount();

}


void ErrorEstimator::addTruePositiveCount(){
    tpCount++;
    cout << "Veri positivi: " << tpCount << endl;
}
void ErrorEstimator::addFalsePositiveCount(){
     fpCount++;
     cout << "Falsi positivi: " << fpCount << endl;
}
void ErrorEstimator::addTrueNegativeCount(){
    tnCount++;
    cout << "Veri negativi: " << tnCount << endl;
}
void ErrorEstimator::addFalseNegativeCount(){
    fnCount++;
    cout << "Falsi negativi: " << fnCount << endl;
}

float ErrorEstimator :: computePrecision() {
    return tpCount/(tpCount+fpCount);
}

float ErrorEstimator :: computeRecall() {
    return tpCount/(tpCount+fnCount);
}

float ErrorEstimator :: computeSpecificity() {
    return tnCount/(tnCount+fpCount);
}

float ErrorEstimator :: computeFMeasure() {
    precision = computePrecision();
    recall = computeRecall();
    return 2*precision*recall/(precision+recall);
}

float ErrorEstimator :: computeAccuracy() {
    recall = computeRecall();
    specificity = computeSpecificity();
    return recall*tpCount/(bClass+fClass) + specificity*tnCount/(bClass+fClass);
}

float ErrorEstimator :: computeSimpleAccuracy() {
   return (tpCount + tnCount)/(bClass+fClass);
}



 float ErrorEstimator :: getErrorMean() {
    float errorMean = 0;
    float sum = 0;
    for(vector<float> :: iterator i=errorListElement.begin(); i != errorListElement.end(); i++) {
        float f = *i;
        sum += f;
    }

    return errorMean = sum / errorListElement.size();

 }

 void ErrorEstimator::showResults(){
    float errorMean = getErrorMean();


    cout << "\n*********************************************" << endl;
    cout << "Results of Analysis: "<<endl;
    cout << "Distances Error Mean: " << errorMean << endl;
    cout << "Accuracy: " << computeAccuracy() << endl;
    cout << "Simple Accuracy: " << computeSimpleAccuracy() << endl;
    cout << "FMeasure: " << computeFMeasure() << endl;
    cout << "************************************************" << endl;

 }


