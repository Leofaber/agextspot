#ifndef BLOBSFINDER_H
#define BLOBSFINDER_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include <map>
#include "Blob.h"

using namespace cv;
using namespace std;


class BlobsFinder
{
    public:
        static vector<Blob> findBlobs(Mat image);
        static Point findCentroidOfMainBlob(vector<vector<Point> >& contours);
    protected:
    private:
        BlobsFinder();
        static Point computeCentroid(vector<Point >& currentBlob);
        static float computeIntraClusterDistance(vector<Point >& currentBlob, Point centroid);
        static float computeEuclideadDistanceBeetweenTwoPoints(Point p1, Point p2);
};

#endif // BLOBSFINDER_H
