#ifndef THRESHOLDBACKGROUNDEVALUATOR_H
#define THRESHOLDBACKGROUNDEVALUATOR_H

#include "FolderManager.h"
#include "FitsToCvMatConverter.h"
#include "BlobsFinder.h"
#include <random>

enum AttributeType { PIXELMEAN = 1, AREA = 2, PHOTONS = 3};

class BlobsDistributionEvaluator
{
    public:
        static normal_distribution<double> getMeanAndDeviation(string pathFitsFiles, AttributeType attribute, bool debugMode);
    private:
         BlobsDistributionEvaluator();
         static vector<float> getAttributesInFitsFile(string pathFitsFiles, string pathToFile, AttributeType attribute, bool debugMode);
};

#endif // THRESHOLDBACKGROUNDEVALUATOR_H
