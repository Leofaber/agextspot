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
        centroid of the blob in galactic coordinate. Return the blob if found, eturn null_ptr instead.
    */
 	Blob* detect(string fitsFileName);



private:

    /**
        Given a blob list, for each blob, call Reverend Bayes to predict the probabilities.
        Then computes the max and returns the most probable Blob to be a flux.
    */
    Blob* getMostProbableFluxBlob(vector<Blob*> blobs);

	string fitsFilesPath;
 	bool debugMode;
	ErrorEstimator* errorEstimator;
	BayesianClassifierForBlobs* reverendBayes;
 };
