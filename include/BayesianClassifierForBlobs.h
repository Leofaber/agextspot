#ifndef BAYESIANCLASSIFIERFORBLOBS_H
#define BAYESIANCLASSIFIERFORBLOBS_H

#include "BlobsDistributionEvaluator.h"

class BayesianClassifierForBlobs
{
    public:

        /**
            Calls learnFromTrainingSet to learn the distributions and shows them.
        */
        BayesianClassifierForBlobs(string simulatedBackgroundFitsFilesPath,string simulatedFluxFitsFilesPath, bool debugMode);

        /**
            Compute the probability for a Blob to be background and flux. Returns [ ("background", x%) , ("flux",1-x%) ]
        */
        vector<pair<string,float> > classify(Blob* b);

        /**
            Prints the mean and standard deviation of all the distributions
        */
        void showDistributionsValues();

    private:

        string simulatedBackgroundFitsFilesPath;
        string simulatedFluxFitsFilesPath;
        bool debugMode;

        /**
            Use the BlobsDistributionEvaluator class to compute the frequencies of the classes background/flux,
            and the distributions of the attributes.
        */
        void learnFromTrainingSet();


        /**
            Compute the probability of an attribute value, given a distribution, from the Gaussian Equation.
            This probability will be inserted in the Bayesian Theorem in the classify() method.
        */
        float computeProbabilityFromDistribution(float x,normal_distribution<double> distribution);

        normal_distribution<double> fluxPixelMeanDistribution;
        normal_distribution<double> bgPixelMeanDistribution;
        normal_distribution<double> fluxAreaDistribution;
        normal_distribution<double> bgAreaDistribution;
        normal_distribution<double> fluxPhotonsInBlobDistribution;
        normal_distribution<double> bgPhotonsInBlobDistribution;
        normal_distribution<double> fluxPhotonsClosenessDistribution;
        normal_distribution<double> bgPhotonsClosenessDistribution;
        /// ADD DISTRIBUTION IF NEEDED


        float countBgBlobs;
        float countFluxBlobs;
        float bgFrequency;
        float fluxFrequency;



};

#endif // BAYESIANCLASSIFIERFORBLOBS_H
