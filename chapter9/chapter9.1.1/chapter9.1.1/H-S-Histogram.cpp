#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat srcImage, hsvImage;
	srcImage = imread("1.jpg");
	cvtColor(srcImage,hsvImage,COLOR_BGR2HSV);

	int hueBinNun = 30;					//色调的直方图直条数量	
	int saturationBinNum = 30;			//饱和度的直方图直条数量
	int histSize[] = { hueBinNun,saturationBinNum };

	float hueRanges[] = {0,180};					//定义色调的范围为0到179
	float saturationRanges[] = { 0,255 };               //定义色调的范围为0到255

	const float* ranges[] = { hueRanges,saturationRanges };

	MatND dstHist;								//MatND是用于存储直方图的一种数据结构
	int channels[] = {0,1};

	calcHist(&hsvImage, 1, channels, Mat(), dstHist,2, histSize, ranges, true, false);

	double maxValue = 0;
	minMaxLoc(dstHist,0,&maxValue,0,0);
	int scale = 10;

	Mat histImage = Mat::zeros(saturationBinNum*scale,hueBinNun*10,CV_8UC3);

	for (int hue = 0; hue < hueBinNun; hue++) {
		for (int saturation = 0; saturation < saturationBinNum; saturation++) {
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue*255/maxValue);		//强度
			rectangle(histImage,Point(hue*scale,saturation*scale),Point((hue+1)*scale-1,(saturation+1)*scale-1),Scalar::all(intensity),FILLED);
		}
	}
	imshow("素材图",srcImage);
	imshow("H-S直方图",histImage);

	waitKey();
	return 0;

}