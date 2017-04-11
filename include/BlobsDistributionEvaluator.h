#ifndef THRESHOLDBACKGROUNDEVALUATOR_H
#define THRESHOLDBACKGROUNDEVALUATOR_H

#include "FolderManager.h"
#include "FitsToCvMatConverter.h"
#include "BlobsFinder.h"
#include <random>

enum AttributeType { PIXELMEAN = 1, AREA = 2, PHOTONS = 3}; /// ADD ATTRIBUTE IF NEEDED

class BlobsDistributionEvaluator
{
    public:
        /**
            Called by BayesianClassifier to get the needed distribution.
        */
        static normal_distribution<double> getMeanAndDeviation(string pathFitsFiles, AttributeType attribute, bool debugMode);


        /**
            Called by BayesianClassifier to get the needed class frequencies.
        */
        static float getFrequencyOfClass(string pathFitsFile, bool debugMode);



    private:
         BlobsDistributionEvaluator();


         /**
            Search in every blob of every images, the values of the desired attribute. E.g. number of photons...
         */
         static vector<float> getAttributesInFitsFile(string pathFitsFiles, string pathToFile, AttributeType attribute, bool debugMode);
};

#endif // THRESHOLDBACKGROUNDEVALUATOR_H
