#pragma once

#include <iostream>
#include <stdio.h>

#include "FitsToCvMatConverter.h"
#include "FolderManager.h"
#include "BlobsFinder.h"
#include "ErrorEstimator.h"

#include <math.h>
#define _USE_MATH_DEFINES

using namespace std;

class GammaRayDetector
{
public:
	GammaRayDetector(string fitsFilesPath, normal_distribution<double> fluxBlobMeansDistribution, normal_distribution<double> bgBlobMeansDitribution, bool debugMode);
	~GammaRayDetector();
	void detect(string fitsFileName);
	void startAnalysis();
	float computeProbabilityFromDistribution(float ,normal_distribution<double> distribution);
private:
	string fitsFilesPath;
	normal_distribution<double> fluxBlobMeansDistribution;
	float fluxDistributionAtZeroMean;
	normal_distribution<double> bgBlobMeansDistribution;
	float bgDistributionAtZeroMean;
	bool debugMode;
	ErrorEstimator* errorEstimator;
 };
