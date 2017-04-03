#include "ImagePrinter.h"

ImagePrinter::ImagePrinter()
{
    //ctor
}

void ImagePrinter::printImage(Mat image) {

    Mat outputImage;

    // Print on Console
    int rows = image.rows;
    int cols = image.cols;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j)
        {
            int pixelValue = (int)image.at<uchar>(i, j);
            cout << pixelValue << ",";
        }
        cout << "\n" ;
    }


    resize(image,outputImage,Size(0,0),3,3,INTER_LINEAR);
    // Print on output window
    namedWindow("test", CV_WINDOW_AUTOSIZE);
    imshow("test", outputImage);
    waitKey(0);

}
