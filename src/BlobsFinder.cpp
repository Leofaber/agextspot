#include "BlobsFinder.h"

BlobsFinder::BlobsFinder()
{
    //ctor
}

vector<Blob> BlobsFinder::findBlobs(Mat image) {

    vector<Blob> blobs;
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;

    Mat copyOfImage = image.clone();
    findContours( copyOfImage, contours, hierarchy,CV_RETR_CCOMP, CV_CHAIN_APPROX_NONE);

    for(vector<vector<Point> >::iterator i = contours.begin(); i < contours.end(); i++){

        vector<Point> currentBlob = *i;
        blobs.push_back(Blob(currentBlob,image));

    }

    return blobs;
}














/*
Point BlobsFinder::findCentroidOfMainBlob(vector<vector<Point> >& contours){


    map<int,Point> blobCentroidPairs;

    int index = 0;
    for(vector<vector<Point> >::iterator i = contours.begin(); i < contours.end(); i++){

        vector<Point> currentBlob = *i;

        /// COMPUTING CENTROIDS
        Point centroid = BlobsFinder::computeCentroid(currentBlob);
       // cout << "Centroid: " << centroid;
        blobCentroidPairs.insert(pair<int,Point>(index,centroid));

        index++;
    }

    /// PRINT CENTROIDS ON WINDOW
    /*Mat prova(100, 100, CV_8UC1, Scalar(0));
    map<int,Point>::iterator i;
    for(i=blobCentroidPairs.begin(); i != blobCentroidPairs.end(); i++){
        cout << i->first << i->second << endl;
        prova.at<uchar>(i->second.y,i->second.x) = 255;
    }*/

/*
    /// COMPUTE DISTANCE INTER CLUSTER (BEETWEEN EVERY CONTOUR POINT WITH THE CENTROID)
    map<int,float> blobIntraClusterDistancePairs;

    index = 0;
    for(vector<vector<Point> >::iterator i = contours.begin(); i < contours.end(); i++){

        vector<Point> currentBlob = *i;

        /// COMPUTING INTRA CLUSTER DISTANCES
        float distance = BlobsFinder::computeIntraClusterDistance(currentBlob,blobCentroidPairs[index]);
        cout << "distanceInterCluster: " << distance << endl;

        blobIntraClusterDistancePairs.insert(pair<int,float>(index,distance));

        index++;
    }


    /// RETURN THE CENTROID OF THE BIGGEST BLOB
    map<int,float>::iterator itt;
    index = 0;
    int max = 0;
    int blobIndex = blobCentroidPairs.begin()->first;
    for(itt=blobIntraClusterDistancePairs.begin(); itt != blobIntraClusterDistancePairs.end(); itt++){
        cout << "Cluster: "<<itt->first << " ->  dist: " << itt->second << endl;
        cout << "Cluster: "<<index<< " ->  centroid: " << blobCentroidPairs[index] << endl;

        if(itt->second > max){
            blobIndex = index;
        }
        index++;

    }
    cout << "index: " << index-1 << endl;
    cout << "RETURN: " << blobCentroidPairs[index-1] << endl;
    return blobCentroidPairs[index-1];


   // waitKey(0);
}
/*
Point BlobsFinder::computeCentroid(vector<Point >& currentBlob){
    int sumX =0;
    int sumY=0;
    for(vector<Point>::iterator l = currentBlob.begin(); l < currentBlob.end(); l++){
                Point p = *l;
                //cout << p << endl;
                sumX+=p.x;
                sumY+=p.y;
    }
    Point centroid(sumX/currentBlob.size(),sumY/currentBlob.size());
    return centroid;
}
*/
float BlobsFinder::computeIntraClusterDistance(vector<Point >& currentBlob, Point centroid){

    int distanceInterCluster = 0;
    for(vector<Point>::iterator l = currentBlob.begin(); l < currentBlob.end(); l++){
        Point p = (Point)*l;
        distanceInterCluster += BlobsFinder::computeEuclideadDistanceBeetweenTwoPoints(p,centroid);

    }
    return distanceInterCluster;
}

float BlobsFinder::computeEuclideadDistanceBeetweenTwoPoints(Point p1, Point p2){
    cout << "P1: " << p1 << "Centroid: " << p2 << endl;
    float powX = pow(p1.x - p2.x, 2);
    float powY = pow(p1.y - p2.y, 2);
    float distance = sqrt(powX + powY);
    cout << "Distance: " << distance << endl;
   // getchar();
    return distance;
}
