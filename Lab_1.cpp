// Lab_1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "ColorTransformer.h"

int main(int argc,char** argv)
{

	ColorTransformer CV;
	/*Mat src = imread("E:\\Deadline\\jennie.jpg", CV_LOAD_IMAGE_COLOR);*/
	/*Mat src = imread("E:\\Deadline\\lena.jpg", CV_LOAD_IMAGE_GRAYSCALE);*/
	Mat src = imread("E:\\Deadline\\lena.png", CV_LOAD_IMAGE_COLOR);

	Mat dst;
	Mat histogram;
	Mat hisImage;
	
	//CV.ChangeBrighness(src,dst,-70);
	CV.CalcHistogram(src, histogram);
	CV.DrawHistogram(histogram,hisImage);
	/*namedWindow("Show Image");
	imshow("Show Image", dst);
	waitKey(0);*/
	return 0;
}

