#include "ErrorEstimator.h"

ErrorEstimator::ErrorEstimator(int row, int cols)
{
    center.x=row/2;
//    cout << "riga centro immagine " << x << endl;
    center.y=cols/2;
  //  cout << "colonna centro immagine " << y<< endl;

}

ErrorEstimator::~ErrorEstimator()
{
    //dtor
}

float ErrorEstimator ::getDistanceFromCenter(Blob b) {
    float distance =  0;
    Point c = b.getCentroid();
    float arg =  pow(c.x - center.x,2) +pow (c.y - center.y,2) ;
    distance = pow(arg , 0.5);
    cout << "Errore stimato: " << distance << endl;
    return distance;
}

 float ErrorEstimator :: updateErrorList(Blob* b) {
     Blob b1 = *b;
     float error = getDistanceFromCenter(b1);
     errorListElement.push_back(error);
 }

 float ErrorEstimator :: errorMean() {
    float errorMean = 0;
    float sum = 0;
    for(vector<float> :: iterator i=errorListElement.begin(); i != errorListElement.end(); i++) {
        float f = *i;
        sum += f;
    }

    return errorMean = sum / errorListElement.size();

 }
