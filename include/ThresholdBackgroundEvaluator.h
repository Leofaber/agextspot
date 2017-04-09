#ifndef THRESHOLDBACKGROUNDEVALUATOR_H
#define THRESHOLDBACKGROUNDEVALUATOR_H

#include "FolderManager.h"
#include "FitsToCvMatConverter.h"
#include "BlobsFinder.h"


class ThresholdBackgroundEvaluator
{
    public:
        ThresholdBackgroundEvaluator(string pathFitsFiles, bool debugMode);
        float getBackgroundThresholdValue();
    private:
        string pathFitsFiles;
        bool debugMode;
        vector<float> getBlobsPixelsMeanInFitsFile(string pathToFile);
};

#endif // THRESHOLDBACKGROUNDEVALUATOR_H
