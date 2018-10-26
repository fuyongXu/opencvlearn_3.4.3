#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace cv;
using namespace std;

static void on_ContrastAndBright(int, void*);

int g_nContrastValue;
int g_nBrightValue;
Mat g_srcImage, g_dstImage;

static void on_ContrastAndBright(int, void*) {
	namedWindow("ԭͼ����", 1);
	for (int y = 0; y < g_srcImage.rows; y++) {
		for (int x = 0; x < g_srcImage.cols; x++) {
			for (int c = 0; c < 3; c++) {
				//������Ϊ���������ܻᳬ������ȡֵ��Χ(���)���������Ƿ����������ʹ��saturate_cast�Խ������ת������ȷ����Ϊ��Чֵ
				//saturate_cast��������:
				/*
				if(data<0)
					data = 0;
				else if(data >255)
					data = 255;
				*/
				//Ϊ�˹۲�Ч����a��ȡֵΪ0.0��3.0�ĸ���ֵ�����ǹ켣��һ��ȡֵΪ����,��˽�nContrastValue������Ϊ0-300��������0.01
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

			}
		}
	}
	imshow("ԭʼ����", g_srcImage);
	imshow("Ч��ͼ����", g_dstImage);
}
int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("��ȡͼƬ1����\n");
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;

	namedWindow("Ч��ͼ����", 1);
	createTrackbar("�Աȶ�:", "Ч��ͼ����", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("����:", "Ч��ͼ����", &g_nBrightValue, 300, on_ContrastAndBright);

	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);
	while (char(waitKey(1)) != 'q') {}
	return 0;
}