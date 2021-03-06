#include "BlobsDistributionEvaluator.h"

BlobsDistributionEvaluator::BlobsDistributionEvaluator()
{

}



normal_distribution<double> BlobsDistributionEvaluator::getMeanAndDeviation(string pathFitsFiles, AttributeType attribute, bool debugMode){

    vector<string> fileNames = FolderManager::getFileNamesFromFolder(pathFitsFiles);

    // il vettore di attributi per i quali si vuole calcolare la distribuzione
    vector<float> blobsAttribute;
    cout << "\nLearning from: " << pathFitsFiles << endl;
    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {
       cout<<"#";
       string fileName = (string) *it;
       // si cerca i valori dei quell'attributo nei blobs trovati in un file Fits
       vector<float> blobsAttributeInFitsFile = BlobsDistributionEvaluator::getAttributesInFitsFile(pathFitsFiles,*it, attribute, debugMode);
       blobsAttribute.insert( blobsAttribute.end(), blobsAttributeInFitsFile.begin(), blobsAttributeInFitsFile.end() );
    }
    cout << "\n" << endl;


    double mean = 0;
    double deviation = 0;

    double count = 0;
    double total = blobsAttribute.size();

    if(total == 0){
        cout << "No blobs found." << endl;
        getchar();
        mean = 0;
        deviation = 0;
        normal_distribution<double> gd(mean,deviation);
        return gd;
    }
    else{
        ///Computing mean

        for(vector<float>::iterator it=blobsAttribute.begin() ; it < blobsAttribute.end(); it++) {
            //cout << *it << endl;
            count += *it;
        }
        mean = count/total;
        //cout << "mean: " << mean << " total: " << total << endl;
        ///Computing deviation
        for(vector<float>::iterator it=blobsAttribute.begin() ; it < blobsAttribute.end(); it++) {
            //cout << *it << endl;
            double term = pow(*it - mean, 2);
            //cout << "term "<< term << endl;
            deviation += term;
        }
        //cout << "[BDE getmeananddev()]deviation: " << deviation << " total: " << total << endl;
        deviation = sqrt(deviation/total);
        //cout << "deviation: " << deviation << endl;

    }


    normal_distribution<double> gd(mean,deviation);


    destroyAllWindows();
    return gd;

}

vector<float> BlobsDistributionEvaluator::getAttributesInFitsFile(string pathFitsFiles,string pathToFile, AttributeType attribute, bool debugMode){

    // GET BLOBS , COMPUTING MEANS
    string fitsFilePath = pathFitsFiles + "/" +pathToFile;
    /// CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);

    /// FINDING BLOBS
    vector<Blob*> blobs = BlobsFinder::findBlobs(tempImage,debugMode);
    vector<float> attributeValues;
    for(vector<Blob*>::iterator i = blobs.begin(); i!=blobs.end(); i++){

        Blob* b = *i;

        if(attribute == PIXELMEAN){
           // cout << "Mean: " << b->getPixelsMean() << endl;
            attributeValues.push_back(b->getPixelsMean());
        }else if(attribute == AREA){
           // cout << "Area: " << b->getNumberOfPixels() << endl;
            attributeValues.push_back(b->getNumberOfPixels());
        }else if(attribute == PHOTONS){
           // cout << "Photons: " << b->getPhotonsInBlob() << endl;
            attributeValues.push_back(b->getPhotonsInBlob());
        }else if(attribute == PHOTONSCLOSENESS){
           // cout << "Photons Closeness: " << b->getPhotonsCloseness() << endl;
            attributeValues.push_back(b->getPhotonsCloseness());
        }

    }


    return attributeValues;


}

float BlobsDistributionEvaluator::getFrequencyOfClass(string pathFitsFiles, bool debugMode){

    vector<string> fileNames = FolderManager::getFileNamesFromFolder(pathFitsFiles);

    float count = 0;

    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {

        string fileName = (string) *it;

        string fitsFilePath = pathFitsFiles + "/" +fileName;

        /// CONVERTING FITS TO MAT
        Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);

        /// FINDING BLOBS
        vector<Blob*> blobs = BlobsFinder::findBlobs(tempImage,debugMode);

        count += blobs.size();
    }

    return count;
}
