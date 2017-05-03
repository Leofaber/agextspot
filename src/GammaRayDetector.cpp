#include "GammaRayDetector.h"


GammaRayDetector::GammaRayDetector(bool _validationMode, string _workPath,bool _showImagesMode){
    workPath = _workPath;
 	showImagesMode = _showImagesMode;
 	reverendBayes = new BayesianClassifierForBlobs(false);
 	validationMode = _validationMode;
 	if(_validationMode){
 	    errorEstimator = new ErrorEstimator(100,100);
 	}
 }



void GammaRayDetector::trainBayesianClassifier(string trainingSetPath){
    reverendBayes->learnFromTrainingSet(trainingSetPath);
}





void GammaRayDetector::startAnalysis(){

    vector<string> fileNames = FolderManager::getFileNamesFromFolder(workPath);

    int count = 1;
    for(vector<string>::iterator it=fileNames.begin() ; it < fileNames.end(); it++) {

        if(showImagesMode)
        cout<<"\n\nAnalysis of: " << *it << " ["<< count << "/"<< fileNames.size()<< "]"<< endl;

        Blob* b = detect(*it);

        if(validationMode)
            errorEstimator->updateErrorList(b,*it);

        count++;
    }
    if(validationMode)
        errorEstimator->showResults();

    getchar();

}

Blob* GammaRayDetector::detect(string fitsFileName)
{
    string fitsFilePath = workPath + "/" +fitsFileName;

    FileWriter::write2FileHeader(fitsFilePath);

    /// 1 - CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(fitsFilePath);


    /// 2 - FINDING BLOBS -> stretching,gaussian filtering, percentile threshold
    vector<Blob*> blobs = BlobsFinder::findBlobs(tempImage,showImagesMode);

    if(blobs.size()>0 && showImagesMode){
        ImagePrinter::printImageBlobs(tempImage.rows,tempImage.cols, blobs, "Found blobs");
    }

    /// 3 - SELECT MOST PROBABLE BLOB TO BE A FLUX
    Blob* fluxBlob = getMostProbableFluxBlob(blobs);


    if(fluxBlob != nullptr && showImagesMode){
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

            string information2Print = "Blob in: [" + to_string(b->getCentroid().x) +"," +to_string(b->getCentroid().y)   +"] background con probabilità: " + to_string(bgProbability*100) +"%" + " flusso con probabilità: " + to_string(fluxProbability*100) +"%";
            FileWriter::write2FileBody(information2Print);

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
        FileWriter::write2FileBody("No flux has been found!");
        return nullptr;
    }
 }
