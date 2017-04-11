#ifndef BLOB_H
#define BLOB_H

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace std;
using namespace cv;

struct Pixel{
    int greyLevel;
    Point p;
};

class Blob
{
    public:

        /**
            Create a new Blob starting from the contour pixels.
            Computes the centroid of the blob.
            Finds the pixels that are inside the blob.
            Finds the number of photons inside the blob.
            Compute the gray level pixel mean of the blob.
        */
        Blob(vector<Point>& c, Mat image, Mat photonImage);


        /**
            GETTERS
        */
        Point getCentroid();
        float getPixelsMean();
        vector<Point> getContour();
        int getNumberOfPixels();
        float getPhotonsInBlob();
        vector<Pixel> getBlobPixels();



     private:

        vector<Point> contour;


        vector<Pixel> blobPixels;
        int numberOfPixels;
        vector<Pixel> computePixelsOfBlob(vector<Point>& c, Mat image);

        float photonsInBlob;
        float computePhotonsBlob(Mat photonImage);

        Point centroid;
        Point computeCentroid();

        float pixelMean;
        float computePixelMean();


};

#endif // BLOB_H
