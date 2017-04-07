#pragma once

#include <iostream>
#include <stdio.h>


#include "FitsToCvMatConverter.h"
#include "Thresholder.h"
#include "GaussianFilterer.h"
#include "ImagePrinter.h"
#include "HistogramStretching.h"
#include "FolderManager.h"
#include "BlobsFinder.h"

using namespace std;

class GammaRayDetector
{
public:
	GammaRayDetector(string fitsFilesPath, string fitsSimulatedFilePath, string analysisMode, string thresholdMode);
	~GammaRayDetector();
	void detect(string fitsFileName);
	void startAnalysis();
private:
	string fitsFilesPath;
	string fitsSimulatedFilePath;
	string analysisMode;
	string thresholdMode;
};
