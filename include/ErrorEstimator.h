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

        /**
            Add to the errorListElement a new distance error.
            Call addFluxCount() or addNoFluxCount().
            It is called from GammaRayDetector when a blob is found.
        */
        void updateErrorList(Blob* b);


        /**
            Print on console the results in terms of error mean and false negatives.
        */
        void showResults();


    private:


        /**
            Returns the euclidean distance of the blob centroid from the center of the image
        */
        float getDistanceFromCenter(Blob* b);

        /**
            Update the fluxCount attribute adding a true positive blob.
        */
        void addFluxCount();
        /**
            Update the noFluxCount attribute adding a true negative blob.
        */
        void addNoFluxCount();

        /**
            Returns the mean of the values of errorListElement.
        */
        float getErrorMean();

        /**
            Returns noFluxCount if imagesTypes is "flux"
            Return fluxCount if imagesTypes is "bg"
        */
        int getFalseNegatives();

        vector<float> errorListElement;

        string imagesTypes;
        int numberOfImages;
        Point center;
        int fluxCount;
        int noFluxCount;

};

#endif // ERRORESTIMATOR_H
