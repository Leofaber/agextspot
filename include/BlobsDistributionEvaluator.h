#ifndef THRESHOLDBACKGROUNDEVALUATOR_H
#define THRESHOLDBACKGROUNDEVALUATOR_H

#include "FolderManager.h"
#include "FitsToCvMatConverter.h"
#include "BlobsFinder.h"
#include <random>



class BlobsDistributionEvaluator
{
    public:
        BlobsDistributionEvaluator(string pathFitsFiles, bool debugMode);
        normal_distribution<double> getMeanAndDeviation();
    private:
        string pathFitsFiles;
        bool debugMode;
        vector<float> getBlobsPixelsMeanInFitsFile(string pathToFile);
};

#endif // THRESHOLDBACKGROUNDEVALUATOR_H
