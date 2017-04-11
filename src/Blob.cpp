#include "Blob.h"

Blob::Blob(vector<Point>& c, Mat image, Mat photonImage)
{
    contour = c;
    cout << "Creating a new Blob. Number of contours pixels: " << c.size() << endl;
    //cout << "Contour Pixels: " << contour << endl;
    computeCentroid();
    cout << "Centroid of Blob: " << centroid << endl;
    computeBlobPixelsBlob(c,image);
    numberOfPixels = blobPixels.size();
    cout << "Pixels of Blob: " << numberOfPixels << endl;
    computePhotonsBlob(photonImage);
    cout << "Photons in Blob: " << photonsInBlob << endl;
    pixelMean = computePixelMean();
    cout << "Pixels mean: " << pixelMean << endl;
   /*for (vector<Pixel>::iterator it = blobPixels.begin(); it != blobPixels.end(); ++it){
        Pixel p = *it;
        cout <<"Pixel: " << p.p << " ->  " <<  p.greyLevel <<  endl;
    }*/
}

Blob::~Blob()
{
    //dtor
}



/// GETTERS
vector<Point> Blob::getContour(){
    return contour;
}
Point Blob::getCentroid(){
    return centroid;
}
int Blob:: getNumberOfPixels() {
    return numberOfPixels;
}
float Blob::getPhotonsInBlob() {
    return photonsInBlob;
}
float Blob::getPixelsMean(){
    return pixelMean;
}


void Blob::computeCentroid(){
    int sumX =0;
    int sumY=0;
    for(vector<Point>::iterator l = contour.begin(); l < contour.end(); l++){
                Point p = *l;
                //cout << p << endl;
                sumX+=p.x;
                sumY+=p.y;
    }
    Point c(sumX/contour.size(),sumY/contour.size());
    centroid = c;
}

void Blob::computeBlobPixelsBlob(vector<Point>& c, Mat image){
     for(int i = 0; i < image.rows; i++){
        for(int j=0; j < image.cols; j++){
            Point p(j,i);
            double isInside = pointPolygonTest(c,p,false);
            if(isInside > 0 | isInside == 0){
             //   cout << "Point " << p << " belongs to blob with grey level "<< (int)image.at<uchar>(i,j)<< endl;
                Pixel pixel;
                pixel.greyLevel = (int)image.at<uchar>(i,j);
                pixel.p = p;
                blobPixels.push_back(pixel);
            }
        }
    }
 }
void Blob::computePhotonsBlob(Mat photonImage){

    for(vector<Pixel>::iterator i = blobPixels.begin(); i != blobPixels.end(); i++){
        Pixel p = *i;
        int grayLevel = (int) photonImage.at<uchar>(p.p);
        //cout << "Photons in " << p.p << " = " << grayLevel << endl;
        photonsInBlob += grayLevel;
    }
}



float Blob::computePixelMean(){
    float numberOfBlobPixels = blobPixels.size();
    float greyLevelCount = 0;

    for (vector<Pixel>::iterator it = blobPixels.begin(); it != blobPixels.end(); ++it){
        Pixel p = *it;
        greyLevelCount+=p.greyLevel;
    }

    return greyLevelCount/numberOfBlobPixels;
}
