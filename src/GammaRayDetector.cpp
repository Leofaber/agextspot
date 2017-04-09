#include "GammaRayDetector.h"
#include "GammaRayDetector.h"




GammaRayDetector::GammaRayDetector(string _fitsFilesPath, float _backgroundThresholdValue, bool _debugMode)
{   fitsFilesPath = _fitsFilesPath;
	backgroundThresholdValue = _backgroundThresholdValue;
	debugMode = _debugMode;

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

    if(blobs.size()>1){

        Mat temp3ChannelImage(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0));
        ImagePrinter::printImageBlobs(temp3ChannelImage, blobs, "Blobs step 2");
        destroyWindow("Blobs step 2");

    }




    /// 3 - THRESHOLDING -> Eliminate Background Blobs (mean <= backgroundThresholdValue)
    vector<Blob> fluxBlob = Thresholder::makeThresholdingOnBlobPixelMean(blobs, backgroundThresholdValue);

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










    // COMPUTE REAL COORDINATES
}
