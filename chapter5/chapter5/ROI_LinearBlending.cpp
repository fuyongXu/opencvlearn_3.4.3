#include<opencv2/opencv.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

bool ROI_AddImage();
bool LinearBlending();
bool ROI_LinearBlending();

//ʵ��ROI�����Ի��
bool ROI_LinearBlending() {
	Mat srcImage1 = imread("dota_pa.jpg",1);
	Mat logoImage = imread("dota_logo.jpg");

	if (!srcImage1.data) {
		printf("��ȡdota_pa.jpg���� \n");
		return false;
	}
	if (!logoImage.data) {
		printf("��ȡdota_logo.jpg���� \n");
		return false;
	}

	Mat imageROI;
	imageROI = srcImage1(Rect(200, 250, logoImage.cols, logoImage.rows));
	//imageROI = srcImage1(Range(250,250+logoImage.rows),Range(200,200+logoImage.cols));
	addWeighted(imageROI, 0.5, logoImage, 0.3, 0., imageROI);
	namedWindow("ROI���Ի�ϴ���");
	imshow("�������Ի��ʾ������", srcImage1);
	return true;
}

//���ø���Ȥ����ROIʵ��ͼ�����

bool ROI_AddImage() {
	Mat srcImage2 = imread("dota_pa.jpg");
	Mat logoImage = imread("dota_logo.jpg");
	if (!srcImage2.data) {
		printf("��ȡsrcImage2����\n");
		return false;
	}
	if (!logoImage.data) {
		printf("��ȡlogoImage����\n");
		return false;
	}
	Mat imageROI = srcImage2(Rect(200,250,logoImage.cols,logoImage.rows));
	//������ģ(�����ǻҶ�ͼ)
	Mat mask = imread("dota_logo.jpg", 0);
	//����ģ���Ƶ�ROI
	logoImage.copyTo(imageROI, mask);
	namedWindow("����ROIʵ��ͼ����ӵĴ���");
	imshow("����ROIʵ��ͼ����ӵĴ���",srcImage2);
	return true;
}

//ʹ��cv::addWeighted()����ʵ��ͼ�����Ի��
bool LinearBlending() {
	double alphaValue = 0.5;
	double betaValue;
	Mat srcImage3, srcImage4, dstImage;
	srcImage3 = imread("mogu.jpg");
	srcImage4 = imread("rain.jpg");
	if (!srcImage3.data) {
		printf("��ȡsrcImage3���� \n");
		return false;
	}
	if (!srcImage4.data) {
		printf("��ȡsrcImage4���� \n");
		return false;
	}
	betaValue = (1.0 - alphaValue);
	addWeighted(srcImage3,alphaValue,srcImage4,betaValue,0.0,dstImage);

	namedWindow("ԭͼ",1);
	imshow("ԭͼ", srcImage3);

	namedWindow("Ч��ͼ", 1);
	imshow("Ч��ͼ",dstImage);
	return true;
}

int main() {
	system("color 5E");
	if (ROI_AddImage() && LinearBlending() && ROI_LinearBlending()) {
		cout << endl << "���гɹ�";
	}
	waitKey(0);
	return 0;
}