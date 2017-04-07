#include "Thresholder.h"
#include "Thresholder.h"


Thresholder::Thresholder()
{
}


Mat Thresholder::makeThresholding(Mat inputImage, double t) {
	Mat destinationImage;
	double maxValue = 255;
	threshold(inputImage, destinationImage, t, maxValue, THRESH_TOZERO);
	return destinationImage;
}

int Thresholder::getThresholdFromPercentileMethod(Mat image, float percentile){
    int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat histogram;
	calcHist(&image, 1, 0, Mat(), histogram, 1, &histSize, &histRange, uniform, accumulate);


    float numberOfPixels = image.rows*image.cols;
    float percentilePixels = percentile*numberOfPixels/100;
    cout << "percentilePixels: " << percentilePixels << endl;
    float count = 0;
    int threshold = 0;
    while (count < percentilePixels){
        count += histogram.at<float>(threshold);
        threshold++;
    }
    return threshold;
}
int Thresholder::getThresholdFromPeaksMethod(Mat image){

	int histSize = 256;
	float range[] = { 0, 255 };
	const float* histRange = { range };

	bool uniform = true; bool accumulate = false;

	Mat histogram;
	calcHist(&image, 1, 0, Mat(), histogram, 1, &histSize, &histRange, uniform, accumulate);

	bool find2Peaks = false;
	vector<float> peaks;


    histogram.at<float>(0) = 0;
	int i = 1;
	while (!find2Peaks){

		float p = histogram.at<float>(i);
		float p1 = histogram.at<float>(i - 1);
		float p2 = histogram.at<float>(i + 1);

		if (p > p1 && p > p2 )
		{
            cout << "livello: " << p << " > p1: "<<p1 << " e > p2:"<<p2<<endl;
			peaks.push_back(i);
		}

		if (peaks.size() == 2)
			find2Peaks = true;

		if (i == histSize - 1)
			break;

		i++;
	}


	if (peaks.size() == 2){
		int threshold = peaks[0];
		int min=999;
		for(int i=peaks[0];i<peaks[1];i++) {
            if(min>histogram.at<float>(i)){
                min=histogram.at<float>(i);
                threshold = i;
                cout << threshold << endl;
                }
        }


		cout << "threshold: " << threshold << endl;
		return threshold;
	}
	else{
		return 0;
	}

}
