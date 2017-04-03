#pragma once

#include <iostream>
#include <stdio.h>
#include <string>


#include "FitsToCvMatConverter.h"
#include "PixelsMeanEvaluator.h"
#include "Thresholder.h"
#include "Filterer.h"
#include "ImagePrinter.h"
#include "HistogramStretching.h"

using namespace std;

class GammaRayDetector
{
public:
	GammaRayDetector(string fitsFilePath, string fitsSimulatedFilePath, string analysisMode, string thresholdMode);
	~GammaRayDetector();
	void detect();
private:
	Mat agileImage;
	FitsToCvMatConverter fcmc;
	string fitsFilePath;
	string fitsSimulatedFilePath;
	string analysisMode;
	string thresholdMode;
};

