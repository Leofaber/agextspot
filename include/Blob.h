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
        Blob(vector<Point>& c, Mat image, Mat photonImage);
        virtual ~Blob();
        Point getCentroid();
        float getPixelsMean();
        vector<Point> getContour();
        int getNumberOfPixels();
        float getPhotonsInBlob();

    protected:
    private:

        int numberOfPixels;
        vector<Pixel> getBlobPixels();
        vector<Pixel> blobPixels;
        void computeBlobPixelsBlob(vector<Point>& c, Mat image);
        void computePhotonsBlob(Mat photonImage);
        vector<Point> contour;
        Point centroid;
        void computeCentroid();
        float pixelMean;
        float computePixelMean();
        float photonsInBlob;

};

#endif // BLOB_H
