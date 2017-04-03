#include "HistogramStretching.h"

HistogramStretching::HistogramStretching()
{
    //ctor
}


Mat HistogramStretching::stretch(Mat inputImage){
    Mat image = inputImage.clone();
    int rows = image.rows;
    int cols = image.cols;
    int max = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
        {
            int pixelValue = (int)image.at<uchar>(i, j);
            if (pixelValue > max)
                max = pixelValue;
         }
     }
    //cout << "max: " << max;


    if(max == 0){
        cout << "[Stretching] Error: max = 0!" << endl;
    }
    // slope for linear stretching
    int slope = int(255 / max);


    // linear stretching
    for (int i = 0; i < rows; ++i)
    {
    for (int j = 0; j < cols; ++j)
        {
        int pixelValue = (int)image.at<uchar>(i, j);
        int newPixelValue;
        if(pixelValue <= 0)
            newPixelValue = 1;
        else
            newPixelValue = pixelValue*slope;


        image.at<uchar>(i, j) = (uchar)newPixelValue;

        }
    }
    return image;

}
