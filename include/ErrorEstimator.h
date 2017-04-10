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
        ErrorEstimator(int rows, int cols);
        virtual ~ErrorEstimator();
        float getDistanceFromCenter(Blob b);
        float updateErrorList(Blob* b);
        float errorMean();
        private:
        Point center;
        vector<float> errorListElement;
};

#endif // ERRORESTIMATOR_H
