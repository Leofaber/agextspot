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

    /**
        To use when training and validating the Gamma Ray Detector (will create an Error Detector)
    */
	GammaRayDetector(bool validationMode,string workPath,bool showImagesMode);



 	/**
        For each file in fitsFilesPath, call detect().
    */
 	void startAnalysis();

    /**
        Computes the distributions for the classifier from a training set
    */
    void trainBayesianClassifier(string trainingSetPath);



private:

    /**
        Open the fits file, convert it to Mat image, finds blobs, classify them with bayesian classifier, compute the
        centroid of the blob in galactic coordinate. Return the blob if found, eturn null_ptr instead.
    */
 	Blob* detect(string fitsFileName);

    /**
        Given a blob list, for each blob, call Reverend Bayes to predict the probabilities.
        Then computes the max and returns the most probable Blob to be a flux.
    */
    Blob* getMostProbableFluxBlob(vector<Blob*> blobs);

	string workPath;
 	bool showImagesMode;
 	bool validationMode;
	ErrorEstimator* errorEstimator;
	BayesianClassifierForBlobs* reverendBayes;
 };
