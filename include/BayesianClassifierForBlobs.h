#ifndef BAYESIANCLASSIFIERFORBLOBS_H
#define BAYESIANCLASSIFIERFORBLOBS_H

#include "BlobsDistributionEvaluator.h"

class BayesianClassifierForBlobs
{
    public:

        /**
            Use the BlobsDistributionEvaluator class to compute the frequencies of the classes background/flux,
            and the distributions of the attributes.
        */
        BayesianClassifierForBlobs(string simulatedBackgroundFitsFilesPath,string simulatedFluxFitsFilesPath, bool debugMode);

        /**
            Compute the probability for a Blob to be background and flux. Returns [ ("background", x%) , ("flux",1-x%) ]
        */
        vector<pair<string,float> > classify(Blob* b);


    private:

        /**
            Compute the probability of an attribute value, given a distribution, from the Gaussian Equation.
            This probability will be inserted in the Bayesian Theorem in the classify() method.
        */
        float computeProbabilityFromDistribution(float x,normal_distribution<double> distribution);

        normal_distribution<double> fluxPixelMeanDistribution;
        normal_distribution<double> fluxAreaDistribution;
		normal_distribution<double> bgPixelMeanDistribution;
        normal_distribution<double> bgAreaDistribution;
        normal_distribution<double> fluxPhotonsInBlobDistribution;
        normal_distribution<double> bgPhotonsInBlobDistribution;
        /// ADD DISTRIBUTION IF NEEDED



        float bgFrequency;
        float fluxFrequency;

};

#endif // BAYESIANCLASSIFIERFORBLOBS_H
