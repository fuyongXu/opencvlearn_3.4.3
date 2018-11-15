#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<iostream>
using namespace std;
using namespace cv;

#define WINDOW_NAME "���򴰿�"

int g_nThresholdValue = 100;
int g_nThresholdType = 3;
Mat g_srcImage, g_grayImage, g_dstImage;

void on_Threshold(int, void*);

void on_Threshold(int, void*) {
	threshold(g_srcImage, g_dstImage, g_nThresholdValue, 255, g_nThresholdType);
	imshow(WINDOW_NAME,g_dstImage);
}

int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("��ȡͼƬ����\n");
		return false;
	}
	cvtColor(g_srcImage, g_grayImage, COLOR_RGB2BGR);

	namedWindow(WINDOW_NAME, WINDOW_AUTOSIZE);
	createTrackbar("ģʽ",WINDOW_NAME,&g_nThresholdType,4,on_Threshold);
	createTrackbar("����ֵ",WINDOW_NAME,&g_nThresholdType,255,on_Threshold);

	on_Threshold(0, 0);
	while (1) {
		int key;
		key = waitKey(20);
		if (char(key) == 27) {
			break;
		}
	}
}