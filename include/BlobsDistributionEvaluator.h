#ifndef THRESHOLDBACKGROUNDEVALUATOR_H
#define THRESHOLDBACKGROUNDEVALUATOR_H

#include "FolderManager.h"
#include "FitsToCvMatConverter.h"
#include "BlobsFinder.h"

struct GaussianDistribution{
    float mean;
    float deviation;
};

class BlobsDistributionEvaluator
{
    public:
        BlobsDistributionEvaluator(string pathFitsFiles, bool debugMode);
        GaussianDistribution getMeanAndDeviation();
    private:
        string pathFitsFiles;
        bool debugMode;
        vector<float> getBlobsPixelsMeanInFitsFile(string pathToFile);
};

#endif // THRESHOLDBACKGROUNDEVALUATOR_H
