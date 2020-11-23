#include "ColorTransformer.h"

ColorTransformer::ColorTransformer()
{
}


ColorTransformer::~ColorTransformer()
{
}

int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b) {
	if (sourceImage.data == NULL)
		return 0;
	int width = sourceImage.cols, height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	if (srcChannels == 1) {
		destinationImage = cv::Mat(height, width, CV_8UC1);
	}
	else {
		destinationImage = cv::Mat(height, width, CV_8UC3);
	}

	int dstChannels = destinationImage.channels();
	std::cout << "So kenh mau: " << dstChannels << "\n";
	int srcWidthStep = sourceImage.step[0];
	int dstWidthStep = destinationImage.step[0];

	std::cout << srcWidthStep<<"\n";

	std::cout << dstWidthStep;

	uchar* pSrcData = sourceImage.data;
	uchar* pDstData = destinationImage.data;

	for (int y = 0; y < height; y++, pSrcData += srcWidthStep, pDstData += dstWidthStep) {
		uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;
		for (int x = 0; x < width; x++, pSrcRow += srcChannels, pDstRow += dstChannels) {
			for (int i = 0; i < srcChannels; i++) {
				// saturate_cast<uchar> lam tron pixel ve [0..255] dung nhat vd 257->1 (sai) 
				// => 257->255 (dung) 
				pDstRow[i] = saturate_cast<uchar>(pSrcRow[i] + b);
			}
		}
	}

	return 1;
}

int ColorTransformer::CalcHistogram(const Mat& sourceImage, Mat& histMatrix) {
	if (sourceImage.data == NULL)
		return 0;

	int width = sourceImage.cols, height = sourceImage.rows;
	int srcChannels = sourceImage.channels();

	//Ma tran 256 x nchannel
	histMatrix = Mat::zeros(256, srcChannels, CV_32S);

	int srcWidthStep = sourceImage.step[0];
	uchar* pSrcData = sourceImage.data;

	for (int y = 0; y < height; y++, pSrcData += srcWidthStep) {
		uchar* pSrcRow = pSrcData;
		for (int x = 0; x < width; x++, pSrcRow += srcChannels) {
			
			for (int i = 0; i < srcChannels; i++) {
				int binIdx = (int)pSrcRow[i];
				histMatrix.at<int>(binIdx, i)++;
			}
		}
	}

	for (int i = 0; i < histMatrix.rows; i++) {
		for (int j = 0; j < histMatrix.cols; j++) {
			std::cout << "\t\t"<<"("<<i<<" , " <<j <<"): "<< histMatrix.at<int>(i, j) << "\t\t";
		}
		std::cout << "\n";
	}
	
	return 1;
}

int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage) {
	if (histMatrix.data == NULL)
		return 0;

	int histSize = 256;
	int hist_w = 1024,hist_h = 768;
	Scalar scalar[] = { Scalar(255, 0, 0) ,Scalar(0, 255, 0),Scalar(0, 0, 255) };
	int bin_w = cvRound((double)hist_w / histSize);
	if (histMatrix.cols == 1) {
		histImage = cv::Mat(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));
	}
	else {
		histImage = cv::Mat(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));
	}

	int histImagechannel = histImage.channels();

	normalize(histMatrix, histMatrix, 0, histImage.cols, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++)
	{
		for (int j = 0; j < histImagechannel; j++) {
			line(histImage, Point(bin_w*(i - 1), hist_h - cvRound(histMatrix.at<int>((i - 1), j))),
				Point(bin_w*(i), hist_h - cvRound(histMatrix.at<int>((i - 1), j))),
				scalar[j], 2, 8, 0);
		}
	
	}
	imshow("calcHist Demo", histImage);
	waitKey();
	return EXIT_SUCCESS;
}
