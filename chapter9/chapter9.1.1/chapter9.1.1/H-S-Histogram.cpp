#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;

int main() {
	Mat srcImage, hsvImage;
	srcImage = imread("1.jpg");
	cvtColor(srcImage,hsvImage,COLOR_BGR2HSV);

	int hueBinNun = 30;					//ɫ����ֱ��ͼֱ������	
	int saturationBinNum = 30;			//���Ͷȵ�ֱ��ͼֱ������
	int histSize[] = { hueBinNun,saturationBinNum };

	float hueRanges[] = {0,180};					//����ɫ���ķ�ΧΪ0��179
	float saturationRanges[] = { 0,255 };               //����ɫ���ķ�ΧΪ0��255

	const float* ranges[] = { hueRanges,saturationRanges };

	MatND dstHist;								//MatND�����ڴ洢ֱ��ͼ��һ�����ݽṹ
	int channels[] = {0,1};

	calcHist(&hsvImage, 1, channels, Mat(), dstHist,2, histSize, ranges, true, false);

	double maxValue = 0;
	minMaxLoc(dstHist,0,&maxValue,0,0);
	int scale = 10;

	Mat histImage = Mat::zeros(saturationBinNum*scale,hueBinNun*10,CV_8UC3);

	for (int hue = 0; hue < hueBinNun; hue++) {
		for (int saturation = 0; saturation < saturationBinNum; saturation++) {
			float binValue = dstHist.at<float>(hue, saturation);
			int intensity = cvRound(binValue*255/maxValue);		//ǿ��
			rectangle(histImage,Point(hue*scale,saturation*scale),Point((hue+1)*scale-1,(saturation+1)*scale-1),Scalar::all(intensity),FILLED);
		}
	}
	imshow("�ز�ͼ",srcImage);
	imshow("H-Sֱ��ͼ",histImage);

	waitKey();
	return 0;

}