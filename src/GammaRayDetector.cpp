#include "GammaRayDetector.h"


GammaRayDetector::GammaRayDetector(string _imagePath, string _outputLogName){
    imagePath = _imagePath;
    outputLogName = _outputLogName;
 	reverendBayes = new BayesianClassifierForBlobs(false);

 }



void GammaRayDetector::trainBayesianClassifier(string trainingSetPath){
    reverendBayes->learnFromTrainingSet(trainingSetPath);
}





void GammaRayDetector::startAnalysis(){

    FileWriter::write2FileHeader(imagePath, outputLogName);
    cout<<"\n\nAnalysis of: " << imagePath << endl;
    Blob* b = detect(imagePath);


}

Blob* GammaRayDetector::detect(string imagePath)
{


    /// 1 - CONVERTING FITS TO MAT
	Mat tempImage = FitsToCvMatConverter::convertFitsToCvMat(imagePath);


    /// 2 - FINDING BLOBS -> stretching,gaussian filtering, percentile threshold
    vector<Blob*> blobs = BlobsFinder::findBlobs(tempImage,false);


    /// 3 - SELECT MOST PROBABLE BLOB TO BE A FLUX
    Blob* fluxBlob = getMostProbableFluxBlob(blobs);

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
            FileWriter::write2FileBody(information2Print, outputLogName);

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
        FileWriter::write2FileBody("No flux has been found!", outputLogName);
        return nullptr;
    }
 }
