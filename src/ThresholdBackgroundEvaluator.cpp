#include "ThresholdBackgroundEvaluator.h"

ThresholdBackgroundEvaluator::ThresholdBackgroundEvaluator(string _pathFitsFiles, bool _debugMode)
{
    pathFitsFiles = _pathFitsFiles;
    debugMode = _debugMode;
}



float ThresholdBackgroundEvaluator::getBackgroundThresholdValue(){

    float thresholdValue = 0;

    vector<string> fileNames;
    fileNames = FolderManager::getFilesFromFolder(pathFitsFiles);
    vector<float> blobsPixelsMeans;
    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {
       cout<< *it << endl;
       string fileName = (string) *it;
       vector<float> blobsPixelsMeanInFitsFile = getBlobsPixelsMeanInFitsFile(*it);
       blobsPixelsMeans.insert( blobsPixelsMeans.end(), blobsPixelsMeanInFitsFile.begin(), blobsPixelsMeanInFitsFile.end() );
    }

    float count = 0;
    float total = blobsPixelsMeans.size();
    cout << "TOTAL: " << total << endl;
    for(vector<float>::iterator it=blobsPixelsMeans.begin() ; it < blobsPixelsMeans.end(); it++) {
        cout << *it << endl;
        count += *it;
    }
    if(total>0)
        thresholdValue = count/total;
    else
        thresholdValue = 0;

    cout << "Analysis Complete:" << endl;
    cout << "TOTAL MEAN: " << thresholdValue <<endl;

    destroyAllWindows();
    getchar();

    return thresholdValue;

}

vector<float> ThresholdBackgroundEvaluator::getBlobsPixelsMeanInFitsFile(string pathToFile){

    // GET BLOBS , COMPUTING MEANS
    string fitsFilePath = pathFitsFiles + "/" +pathToFile;
    /// CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);

    /// FINDING BLOBS
    vector<Blob> blobs = BlobsFinder::findBlobs(tempImage,debugMode);
    vector<float> means;
    for(vector<Blob>::iterator i = blobs.begin(); i!=blobs.end(); i++){

        Blob b = *i;
        cout << "Mean: " << b.getPixelsMean() << endl;
        means.push_back(b.getPixelsMean());
    }


    return means;


}
