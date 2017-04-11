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
 	void detect(string fitsFileName);
	void startAnalysis();
	float computeProbabilityFromDistribution(float ,normal_distribution<double> distribution);
private:
	string fitsFilesPath;
 	bool debugMode;
	ErrorEstimator* errorEstimator;
	BayesianClassifierForBlobs* reverendBayes;
 };
