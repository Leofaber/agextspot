#ifndef ERRORESTIMATOR_H
#define ERRORESTIMATOR_H

#include <vector>
#include <string>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "Blob.h"
#include <math.h>


class ErrorEstimator
{
    public:
        ErrorEstimator(int rows, int cols, string imagesTypes, int numberOfImages);
        virtual ~ErrorEstimator();
        float getDistanceFromCenter(Blob b);
        float updateErrorList(Blob* b);
        float getErrorMean();
        void showResults();
        int getFalsePositives();
        void addFluxCount();
        void addNoFluxCount();
    private:
        string imagesTypes;
        int numberOfImages;
        Point center;
        vector<float> errorListElement;
        int fluxCount;
        int noFluxCount;
};

#endif // ERRORESTIMATOR_H
