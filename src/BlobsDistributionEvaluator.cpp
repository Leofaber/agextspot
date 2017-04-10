#include "BlobsDistributionEvaluator.h"

BlobsDistributionEvaluator::BlobsDistributionEvaluator(string _pathFitsFiles, bool _debugMode)
{
    pathFitsFiles = _pathFitsFiles;
    debugMode = _debugMode;
}



GaussianDistribution BlobsDistributionEvaluator::getMeanAndDeviation(){

    GaussianDistribution gd;


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

    if(total == 0){
        cout << "No blobs found." << endl;
        getchar();
        gd.mean = 0;
        gd.deviation = 0;
        return gd;
    }
    else{
        ///Computing mean

        for(vector<float>::iterator it=blobsPixelsMeans.begin() ; it < blobsPixelsMeans.end(); it++) {
            cout << *it << endl;
            count += *it;
        }
        gd.mean = count/total;

        ///Computing deviation
        for(vector<float>::iterator it=blobsPixelsMeans.begin() ; it < blobsPixelsMeans.end(); it++) {
            cout << *it << endl;
            gd.deviation += pow(*it - gd.mean, 2);
        }
        gd.deviation = sqrt(gd.deviation/total);

    }





    destroyAllWindows();
    return gd;

}

vector<float> BlobsDistributionEvaluator::getBlobsPixelsMeanInFitsFile(string pathToFile){

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
