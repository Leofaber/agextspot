#pragma once

#include <iostream>
#include <stdio.h>


#include "FitsToCvMatConverter.h"
#include "FolderManager.h"
#include "BlobsFinder.h"

using namespace std;

class GammaRayDetector
{
public:
	GammaRayDetector(string fitsFilesPath, float backgroundThresholdValue, float backgroundThresholdDeviation,bool debugMode);
	~GammaRayDetector();
	void detect(string fitsFileName);
	void startAnalysis();
private:
	string fitsFilesPath;
	float backgroundThresholdValue;
	float backgroundThresholdDeviation;
	bool debugMode;
 };
