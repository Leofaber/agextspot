#ifndef BAYESIANCLASSIFIERFORBLOBS_H
#define BAYESIANCLASSIFIERFORBLOBS_H

#include "BlobsDistributionEvaluator.h"

class BayesianClassifierForBlobs
{
    public:
        BayesianClassifierForBlobs(string simulatedBackgroundFitsFilesPath,string simulatedFluxFitsFilesPath, bool debugMode);

        vector<pair<string,float> > classify(Blob b);

    protected:

    private:


        normal_distribution<double> fluxPixelMeanDistribution;
        normal_distribution<double> fluxAreaDistribution;
		normal_distribution<double> bgPixelMeanDistribution;
        normal_distribution<double> bgAreaDistribution;
        normal_distribution<double> fluxPhotonsInBlobDistribution;
        normal_distribution<double> bgPhotonsInBlobDistribution;

        float computeProbabilityFromDistribution(float x,normal_distribution<double> distribution);


        float bgFrequency;
        float fluxFrequency;

};

#endif // BAYESIANCLASSIFIERFORBLOBS_H
