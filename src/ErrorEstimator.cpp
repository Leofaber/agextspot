#include "ErrorEstimator.h"

ErrorEstimator::ErrorEstimator(int row, int cols)
{
    center.x=row/2;
    center.y=cols/2;

}


float ErrorEstimator ::getDistanceFromCenter(Blob* b) {
    float distance =  0;
    Point c = b->getFloatingCentroid();
    float arg =  pow(c.x - center.x,2) +pow (c.y - center.y,2) ;
    distance = pow(arg , 0.5);
    cout << "Errore stimato: " << distance << endl;
    return distance;
}

 void ErrorEstimator :: updateErrorList(Blob* b, string fileName) {
    char classChar = fileName.at(0);
    //cout << "Il primo carattere " << classChar << endl;
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
    else if(b!=nullptr && classChar=='B'){
        bClass++;
        addFalsePositiveCount();
    }

}


void ErrorEstimator::addTruePositiveCount(){
    tpCount++;
    //cout << "Veri positivi: " << tpCount << endl;
}
void ErrorEstimator::addFalsePositiveCount(){
     fpCount++;
     //cout << "Falsi positivi: " << fpCount << endl;
}
void ErrorEstimator::addTrueNegativeCount(){
    tnCount++;
    //cout << "Veri negativi: " << tnCount << endl;
}
void ErrorEstimator::addFalseNegativeCount(){
    fnCount++;
    //cout << "Falsi negativi: " << fnCount << endl;
}

float ErrorEstimator :: computePrecision() {
    if(tpCount == 0 && fpCount == 0)
        return 0;
    else
        return tpCount/(tpCount+fpCount);
}

float ErrorEstimator :: computeRecall() {
    if(tpCount == 0 && fnCount == 0)
        return 0;
    else
        return tpCount/(tpCount+fnCount);
}

float ErrorEstimator :: computeSpecificity() {
    if(tnCount == 0 && fpCount == 0)
        return 0;
    else
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
    return recall* (tpCount+fpCount)/(bClass+fClass) + specificity* (tnCount+fnCount)/(bClass+fClass);
}

float ErrorEstimator :: computeSimpleAccuracy() {
   return (tpCount + tnCount)/(bClass+fClass);
}



 float ErrorEstimator :: getDistanceErrorMean() {
    float errorMean = 0;
    float sum = 0;
    for(vector<float> :: iterator i=errorListElement.begin(); i != errorListElement.end(); i++) {
        float f = *i;
        sum += f;
    }

    return errorMean = sum / errorListElement.size();

}

float ErrorEstimator :: getDistanceErrorStdDev(){
    float mean = getDistanceErrorMean();
    float deviation = 0;
    for(vector<float> :: iterator i=errorListElement.begin(); i != errorListElement.end(); i++) {
        double term = pow(*i - mean, 2);
        deviation += term;
    }
    float total = errorListElement.size();
    return sqrt(deviation/total);
 }

 float ErrorEstimator::computeFalseNegativeRate(){
    if(fnCount==0 && tpCount==0)
        return 0;
    else
        return fnCount/(tpCount+fnCount);
 }

float ErrorEstimator::computeFalsePositiveRate(){
    if(fpCount==0 && tnCount==0)
        return 0;
    else
        return fpCount/(fpCount+tnCount);
}

 int ErrorEstimator::getTotalInstances(){
    return tpCount+tnCount+fnCount+fpCount;
 }

 float ErrorEstimator::getChoenKappa(){
    float p0 = (tpCount+tnCount)/getTotalInstances();
    float pe = 0.5;
    return (p0-pe)/(1-pe);
 }

 void ErrorEstimator::showResults(){

    cout << "\n*********************************************" << endl;
    cout << "Results of Analysis: "<<endl;

    cout << "Correctly Classified Instances: " << tpCount+tnCount << "  "<< ((tpCount+tnCount)/getTotalInstances())*100<<"%"<<endl;

    cout << "Incorrectly Classified Instances: " << fpCount+fnCount << "  "<< ((fpCount+fnCount)/getTotalInstances())*100<<"%"<<endl;

    cout << "Kappa statistic: " << getChoenKappa() << endl;

    cout << "Total Number of Instances: " << "class Flux: " << fClass << " class Background: " << bClass << " total: " << fClass+bClass << endl;



    cout << "Distances Error Mean and Variance: " << getDistanceErrorMean() << " +- " << getDistanceErrorStdDev()<<endl;
    cout << "FN: "<<fnCount<<" FP: "<<fpCount<<" TP: "<<tpCount<<" TN:"<<tnCount<<endl;
    cout << "False Negatives Rate: " << computeFalseNegativeRate()*100<<"%  (miss rate)"<<endl;
    cout << "False Positives Rate: " << computeFalsePositiveRate()*100<<"%  (false alarm rate)"<<endl;
    cout << "Accuracy: " << computeAccuracy()*100<<"%" << endl;
    cout << "FMeasure: " << computeFMeasure()*100<<"%" <<endl;
    cout << "************************************************" << endl;

 }


