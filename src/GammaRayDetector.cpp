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
       cout<< *it << endl;
       detect(*it);
    }

}

void GammaRayDetector::detect(string fitsFileName)
{

    string fitsFilePath = fitsFilesPath + "/" +fitsFileName;

    /// CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);


    /// FINDING BLOBS
    vector<Blob> blobs = BlobsFinder::findBlobs(tempImage,debugMode);

    if(blobs.size()==0){
        destroyAllWindows();
        return;
    }




    /// TODO THRESHOLDING -> Eliminate Background Blobs (mean < 5)

    if(blobs.size()==0){
        destroyAllWindows();
        return;
    }





    /// COMPARISON OF REMAINS BLOBS : who is backgound , who is flux?
    float max = blobs[0].getPixelsMean();
    Blob fluxBlob = blobs[0];
    cout << "Mean of blob " << blobs[0].getCentroid() << " = " << blobs[0].getPixelsMean() << endl;

    vector<Blob>::iterator i = blobs.begin();
    advance(i,1);
    for(; i != blobs.end(); i++){
        Blob b = *i;
        float mean = b.getPixelsMean();
        cout << "Mean of blob " << b.getCentroid() << " = " << mean << endl;
        if(mean > max){
            max = mean;
            fluxBlob = b;
        }else if(mean==max) {
            if(b.getNumberOfPixels() > fluxBlob.getNumberOfPixels()) {
                fluxBlob = b;
            }

        }
    }


    /// PRINTING IMAGE
    /*
    Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
    for(vector<Blob>::iterator i = blobs.begin(); i != blobs.end(); i++){
        ImagePrinter::printImageBlob(tempImageRgb, *i ,"window5");
    }
    */
    Mat tempImageRgb(tempImage.rows, tempImage.cols, CV_8UC3, Scalar(0,0,0)); //3-channel
    ImagePrinter::printImageBlob(tempImageRgb, fluxBlob,"window5");


    /// TODO

    // fix CRASH WHEN NO FLUX ARE PRESENT
    // KERNEL PIU GRANDE
    // COMPUTE REAL COORDINATES
}
