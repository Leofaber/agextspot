#include "GammaRayDetector.h"




GammaRayDetector::GammaRayDetector(string _fitsFilesPath, BayesianClassifierForBlobs* _reverendBayes, ErrorEstimator* _ee, bool _debugMode)
{   fitsFilesPath = _fitsFilesPath;
 	debugMode = _debugMode;
    errorEstimator = _ee;
    reverendBayes = _reverendBayes;
}




void GammaRayDetector::startAnalysis(){

    vector<string> fileNames = FolderManager::getFileNamesFromFolder(fitsFilesPath);

    int count = 1;
    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {

        if(debugMode)
        cout<<"\n\nAnalysis of: " << *it << " ["<< count << "/"<< fileNames.size()<< "]"<< endl;

        Blob* b = detect(*it);

        errorEstimator->updateErrorList(b,*it);

        count++;
    }

    errorEstimator->showResults();

    getchar();

}

Blob* GammaRayDetector::detect(string fitsFileName)
{
    string fitsFilePath = fitsFilesPath + "/" +fitsFileName;


    /// 1 - CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);


    /// 2 - FINDING BLOBS -> stretching,gaussian filtering, percentile threshold
    vector<Blob*> blobs = BlobsFinder::findBlobs(tempImage,debugMode);

    if(blobs.size()>0 && debugMode){
        ImagePrinter::printImageBlobs(tempImage.rows,tempImage.cols, blobs, "Found blobs");
    }

    /// 3 - SELECT MOST PROBABLE BLOB TO BE A FLUX
    Blob* fluxBlob = getMostProbableFluxBlob(blobs);


    if(fluxBlob != nullptr && debugMode){
        Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
        ImagePrinter::printImageBlob(tempImageRgb, fluxBlob,"Last GRB found");
        waitKey(0);
    }
    return fluxBlob;
}



 Blob* GammaRayDetector::getMostProbableFluxBlob(vector<Blob*> blobs){

    if(blobs.size() > 0){

        Blob * mostProbableBlob = nullptr;
        float max = 0;
        for(vector<Blob*>::iterator i = blobs.begin(); i != blobs.end(); i++){

            Blob* b = *i;

            vector<pair<string,float> > predicted = reverendBayes->classify(b);

            float bgProbability = predicted[0].second;
            float fluxProbability = predicted[1].second;

            if(fluxProbability >= bgProbability && fluxProbability>max){
                max = fluxProbability;
                mostProbableBlob = b;
             }

        } // end for loop


        if(mostProbableBlob != nullptr){
            cout << "Flux found in "<< mostProbableBlob->getCentroid() <<" with probability: " << max*100 <<"%."<<endl;
        }else{
            cout << "No flux has been found." << endl;
        }
        return mostProbableBlob;

    }else{
        cout << "No flux has been found." << endl;
        return nullptr;
    }
 }




























    /*
    Blob* fluxBlob = nullptr;

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
                cout << "INIZIALIZZO FLUX "<<endl;
                fluxBlob = &b;
            }

        }

        //getchar();

    }

    if(fluxBlob == nullptr){
        cout << "No blob found." << endl;
        errorEstimator->addNoFluxCount();
        return;
    }else{

        cout << "Found flux in "<< fluxBlob->getCentroid() <<" with probability: " << max <<endl;
        Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
        ImagePrinter::printImageBlob(tempImageRgb, *fluxBlob,"Flux blob");

        /// 5 - ERROR ESTIMATION
        errorEstimator->updateErrorList(fluxBlob);
        errorEstimator->addFluxCount();

    }



*/












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







