#include "BayesianClassifierForBlobs.h"

BayesianClassifierForBlobs::BayesianClassifierForBlobs(string simulatedBackgroundFitsFilesPath,string simulatedFluxFitsFilesPath, bool debugMode)
{


    /// Frequency of classes
    countBgBlobs = BlobsDistributionEvaluator::getFrequencyOfClass(simulatedBackgroundFitsFilesPath, debugMode);
    countFluxBlobs = BlobsDistributionEvaluator::getFrequencyOfClass(simulatedFluxFitsFilesPath, debugMode);

    float total = countBgBlobs + countFluxBlobs;

    bgFrequency = countBgBlobs/total;
    fluxFrequency = countFluxBlobs/total;






    /**
        ADD DISTRIBUTION IF NEEDED
    */

    bgPixelMeanDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedBackgroundFitsFilesPath, PIXELMEAN ,debugMode);

    fluxPixelMeanDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedFluxFitsFilesPath, PIXELMEAN, debugMode);

    bgAreaDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedBackgroundFitsFilesPath, AREA ,debugMode);

    fluxAreaDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedFluxFitsFilesPath, AREA, debugMode);

    bgPhotonsInBlobDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedBackgroundFitsFilesPath, PHOTONS, debugMode);

    fluxPhotonsInBlobDistribution= BlobsDistributionEvaluator::getMeanAndDeviation(simulatedFluxFitsFilesPath, PHOTONS, debugMode);

    bgPhotonsClosenessDistribution = BlobsDistributionEvaluator::getMeanAndDeviation(simulatedBackgroundFitsFilesPath, PHOTONSCLOSENESS, debugMode);

    fluxPhotonsClosenessDistribution= BlobsDistributionEvaluator::getMeanAndDeviation(simulatedFluxFitsFilesPath, PHOTONSCLOSENESS, debugMode);



    /**
        Prints everythings
    */
    showDistributionsValues();



}


vector<pair<string,float> > BayesianClassifierForBlobs::classify(Blob* b){

    vector<pair<string,float> > prediction;

    float pixelMean = b->getPixelsMean();
    float area = b->getNumberOfPixels();
    float photons = b->getPhotonsInBlob();
    /// ADD ATTRIBUTE

    float bgPM = computeProbabilityFromDistribution(pixelMean,bgPixelMeanDistribution);
    float bgA = computeProbabilityFromDistribution(area, bgAreaDistribution);
    float bgP = computeProbabilityFromDistribution(photons, bgPhotonsInBlobDistribution);
    /// ADD DISTR VALUE


    float fluxPM = computeProbabilityFromDistribution(pixelMean,fluxPixelMeanDistribution);
    float fluxA = computeProbabilityFromDistribution(area, fluxAreaDistribution);
    float fluxP = computeProbabilityFromDistribution(photons, fluxPhotonsInBlobDistribution);
    /// ADD DISTR VALUE

    float likelyHoodOfBackground =  bgPM*bgA*bgP*bgFrequency;
    float likelyHoodOfFlux = fluxPM*fluxA*fluxP*fluxFrequency;

    float sum = likelyHoodOfBackground+likelyHoodOfFlux;

    float probabilityOfBg = likelyHoodOfBackground/sum;
    float probabilityOfFlux = likelyHoodOfFlux/sum;

    prediction.push_back(make_pair("Background",probabilityOfBg));
    prediction.push_back(make_pair("Flux",probabilityOfFlux));


    cout << "[Reverend Bayes] "<< "Point "<<b->getCentroid()<<" is background " << " with probability: " << probabilityOfBg*100<<"%"<<endl;
    cout << "[Reverend Bayes] "<< "Point "<<b->getCentroid()<<" is flux " << " with probability: " << probabilityOfFlux*100<<"%"<<endl;


    return prediction;
}


float BayesianClassifierForBlobs::computeProbabilityFromDistribution(float x,normal_distribution<double> distribution){
    float mean = distribution.mean();
    float stddev = distribution.stddev();


    float probability = 0;

    float multiplier = 1 / ( sqrt(2*M_PI*pow(stddev,2))   );

    float exponent = -1 *( (pow(x-mean,2)) / (2*pow(stddev,2)) );

    float exponential = exp(exponent);

    probability = multiplier * exponential;

   // cout << "multiplier: " << multiplier << endl;
   // cout << "exponent: " << exponent << endl;
  //  cout << "exponential: " << exponential << endl;

    return probability;
}


void BayesianClassifierForBlobs::showDistributionsValues(){

    cout << "\n *** Number and Frequency of classes:" << endl;
    cout << "Background Blobs: " << countBgBlobs <<" - " <<bgFrequency  <<endl;
    cout << "Flux Blobs: " << countFluxBlobs <<" - " << fluxFrequency  <<endl;

    cout << "\n *** Analysis of PIXEL MEAN Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgPixelMeanDistribution.mean() <<endl;
    cout << "Standard Deviation: " << bgPixelMeanDistribution.stddev() <<endl;


	cout << "\n *** Analysis of PIXEL MEAN Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxPixelMeanDistribution.mean() <<endl;
    cout << "Standard Deviation: " << fluxPixelMeanDistribution.stddev() << endl;


    cout << "\n *** Analysis of AREA Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgAreaDistribution.mean() <<endl;
    cout << "Standard Deviation: " << bgAreaDistribution.stddev() << endl;


	cout << "\n *** Analysis of AREA Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxAreaDistribution.mean() <<endl;
    cout << "Standard Deviation: " << fluxAreaDistribution.stddev() << endl;


	cout << "\n *** Analysis of PHOTONS Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgPhotonsInBlobDistribution.mean() <<endl;
    cout << "Standard Deviation: " << bgPhotonsInBlobDistribution.stddev() << endl;


	cout << "\n *** Analysis of PHOTONS Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxPhotonsInBlobDistribution.mean() <<endl;
    cout << "Standard Deviation: " << fluxPhotonsInBlobDistribution.stddev() << endl;


	cout << "\n *** Analysis of PHOTONS Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgPhotonsInBlobDistribution.mean() <<endl;
    cout << "Standard Deviation: " << bgPhotonsInBlobDistribution.stddev() << endl;


	cout << "\n *** Analysis of PHOTONS Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxPhotonsInBlobDistribution.mean() <<endl;
    cout << "Standard Deviation: " << fluxPhotonsInBlobDistribution.stddev() << endl;


    cout << "\n *** Analysis of PHOTONS CLOSENESS Background Blobs Distribution Complete:" << endl;
    cout << "Mean: " << bgPhotonsClosenessDistribution .mean() <<endl;
    cout << "Standard Deviation: " << bgPhotonsClosenessDistribution.stddev() << endl;


	cout << "\n *** Analysis of PHOTONS CLOSENESS Flux Blobs Distribution Complete:" << endl;
    cout << "Mean: " << fluxPhotonsClosenessDistribution.mean() <<endl;
    cout << "Standard Deviation: " << fluxPhotonsClosenessDistribution.stddev() << endl;

    getchar();
}
