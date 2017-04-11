#pragma once

#include <iostream>
#include <stdio.h>

#include "FitsToCvMatConverter.h"
#include "FolderManager.h"
#include "BlobsFinder.h"
#include "ErrorEstimator.h"
#include "BayesianClassifierForBlobs.h"
#include <math.h>
#define _USE_MATH_DEFINES

using namespace std;

class GammaRayDetector
{
public:

	GammaRayDetector(string fitsFilesPath, BayesianClassifierForBlobs* reverendBayes, ErrorEstimator* ee, bool debugMode);

 	/**
        For each file in fitsFilesPath, call detect().
    */
 	void startAnalysis();


    /**
        Open the fits file, convert it to Mat image, finds blobs, classify them with bayesian classifier, compute the
        centroid of the blob in galactic coordinate.
    */
 	void detect(string fitsFileName);



private:
    //float computeProbabilityFromDistribution(float ,normal_distribution<double> distribution);
	string fitsFilesPath;
 	bool debugMode;
	ErrorEstimator* errorEstimator;
	BayesianClassifierForBlobs* reverendBayes;
 };
