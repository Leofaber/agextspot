#include "GammaRayDetector.h"
#include "GammaRayDetector.h"




GammaRayDetector::GammaRayDetector(string _fitsFilesPath, normal_distribution<double> _fluxBlobMeansDistribution, normal_distribution<double> _bgBlobMeansDistribution, bool _debugMode)
{   fitsFilesPath = _fitsFilesPath;
	fluxBlobMeansDistribution = _fluxBlobMeansDistribution;
	bgBlobMeansDistribution = _bgBlobMeansDistribution;
	debugMode = _debugMode;

	fluxDistributionAtZeroMean = computeProbabilityFromDistribution(fluxBlobMeansDistribution.mean(),fluxBlobMeansDistribution);
    cout << "fluxDistributionAtZeroMean: " << fluxDistributionAtZeroMean << endl;


	bgDistributionAtZeroMean = computeProbabilityFromDistribution(bgBlobMeansDistribution.mean(),bgBlobMeansDistribution);
    cout << "bgDistributionAtZeroMean: " << bgDistributionAtZeroMean << endl;

    errorEstimator = new ErrorEstimator(100,100);
}


GammaRayDetector::~GammaRayDetector()
{
}

void GammaRayDetector::startAnalysis(){
    vector<string> fileNames;
    fileNames = FolderManager::getFilesFromFolder(fitsFilesPath);
    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {

       cout<<"\n\nAnalysis of: " << *it << endl;
       detect(*it);
    }

    float errorMean = errorEstimator->errorMean();
    cout << "Errore medio stimato: " << errorMean << endl;
    getchar();

}

void GammaRayDetector::detect(string fitsFileName)
{
    string fitsFilePath = fitsFilesPath + "/" +fitsFileName;



    /// 1 - CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);




    /// 2 - FINDING BLOBS -> stretching,gaussian filtering, percentile threshold
    vector<Blob> blobs = BlobsFinder::findBlobs(tempImage,debugMode);

    if(blobs.size()==0){
        //destroyAllWindows();
        cout << "[Stretching,filtering,percentile threshold] No flux found." << endl;
        getchar();
        return;
    }

    if(blobs.size()>0){

        Mat temp3ChannelImage(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0));
        ImagePrinter::printImageBlobs(temp3ChannelImage, blobs, "Found blobs");

    }

    /// 3 - Select most probable blob to be a flux

    Blob* fluxBlob;



    float max = 0;


    for(vector<Blob>::iterator i = blobs.begin(); i != blobs.end(); i++){

        Blob b = *i;
        float blobMean = b.getPixelsMean();

        float isFlux = computeProbabilityFromDistribution(blobMean, fluxBlobMeansDistribution);
        float isBg = computeProbabilityFromDistribution(blobMean, bgBlobMeansDistribution);

        float isFluxWithProbability = isFlux / fluxDistributionAtZeroMean;
        float isBgWithProbability = isBg / bgDistributionAtZeroMean;

        cout << "Il blob è: " <<endl;
        cout << "flux with probability " << isFluxWithProbability << endl;
        cout << "background with probability: " <<  isBgWithProbability << endl;

        if(isFluxWithProbability > isBgWithProbability){

            if(isFluxWithProbability>max){
                max = isFluxWithProbability;
                fluxBlob = &b;
            }

        }

        //getchar();

    }

    cout << "Found flux in "<< fluxBlob->getCentroid() <<" with probability: " << max <<endl;
    Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
    ImagePrinter::printImageBlob(tempImageRgb, *fluxBlob,"Flux blob");

    /// 5 - ERROR ESTIMATION
    errorEstimator->updateErrorList(fluxBlob);

    /*
    if(blobs.size()>1){

        Mat temp3ChannelImage(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0));
        ImagePrinter::printImageBlobs(temp3ChannelImage, blobs, "Blobs step 2");
        destroyWindow("Blobs step 2");

    }

    /// 3 - THRESHOLDING -> Eliminate Background Blobs (mean <= backgroundThresholdValue)
    vector<Blob> fluxBlob = Thresholder::makeThresholdingOnBlobPixelMean(blobs, bgBlobMeansDitribution.mean());

    if(fluxBlob.size()==0){
        //destroyAllWindows();
        cout << "[Thresholding on background blob mean] No flux found." << endl;
        getchar();
        return;
    }

    if(fluxBlob.size()>1){
        Mat temp3ChannelImage(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0));
        ImagePrinter::printImageBlobs(temp3ChannelImage, blobs, "Blobs step 3");

    }



    /// 4 - SELECT FLUX -> Eliminate False Positives (find biggest mean blob)
    Blob flux = fluxBlob[0];
    if(fluxBlob.size() > 1 ){
        cout << "False Positives Blobs are present. I take the one with biggest mean" << endl;
        vector<Blob>::iterator i = fluxBlob.begin();
        advance(i,1);
        float max = flux.getPixelsMean();
        for(; i!=fluxBlob.end(); i++){
            Blob b = *i;
            if(b.getPixelsMean() == max && b.getNumberOfPixels()>flux.getNumberOfPixels()){
                cout << "Two blobs with same mean. I take the biggest" << endl;
                flux = b;
                max = b.getPixelsMean();
            }else if(b.getPixelsMean() == max && b.getNumberOfPixels() == flux.getNumberOfPixels()){
                cout << "Two blobs with same mean and same size" << endl;

            }else if(b.getPixelsMean()>max){
                flux = b;
                max = b.getPixelsMean();
            }
        }

    }

    cout << "Found flux ! " <<endl;
    Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
    ImagePrinter::printImageBlob(tempImageRgb, flux,"Flux blob");


    */







    // COMPUTE REAL COORDINATES
}

float GammaRayDetector::computeProbabilityFromDistribution(float x,normal_distribution<double> distribution){
    float mean = distribution.mean();
    float stddev = distribution.stddev();


    float probability = 0;

    float multiplier = 1 / ( sqrt(2*M_PI*pow(stddev,2))   );

    float exponent = -1 *( (pow(x-mean,2)) / (2*pow(stddev,2)) );

    float exponential = exp(exponent);

    probability = multiplier * exponential;

    cout << "multiplier: " << multiplier << endl;
    cout << "exponent: " << exponent << endl;
    cout << "exponential: " << exponential << endl;





    return probability;
}

