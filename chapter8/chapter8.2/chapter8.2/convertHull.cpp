#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "ԭͼ����"
#define WINDOW_NAME2 "Ч��ͼ����"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_maxThresh = 255;
RNG g_rng(12345);
Mat srcImage_copy = g_srcImage.clone();
Mat g_thresholdImage_output;
vector<vector<Point>>g_vContours;
vector<Vec4i>g_vHierarchy;

void on_ThreshChange(int,void*);

void on_ThreshChange(int,void*) {
	//�ȶ�ͼ����ж�ֵ����������ֵ
	threshold(g_grayImage,g_thresholdImage_output,g_nThresh,255,THRESH_BINARY);

	//Ѱ������
	findContours(g_thresholdImage_output,g_vContours,g_vHierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));
	
	//����ÿһ��������Ѱ����͹��
	vector<vector<Point>>hull(g_vContours.size());
	for (unsigned int i = 0; i < g_vContours.size(); i++) {
		convexHull(Mat(g_vContours[i]),hull[i],false);
	}

	//���Ƴ���������͹��
	Mat drawing = Mat::zeros(g_thresholdImage_output.size(),CV_8UC3);
	for (unsigned int i = 0; i < g_vContours.size(); i++) {
		Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));
		drawContours(drawing,g_vContours,i,color,1,8,vector<Vec4i>(),0,Point());
		drawContours(drawing, hull, i, color, 1, 8, vector<Vec4i>(), 0, Point());
	}
	imshow(WINDOW_NAME2,drawing);
}

int main() {
	g_srcImage = imread("1.jpg",1);
	if (!g_srcImage.data) {
		printf("��ȡͼƬ����\n");
		return false;
	}
	cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
	blur(g_grayImage,g_grayImage,Size(3,3));

	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1,g_srcImage);

	createTrackbar("��ֵ��",WINDOW_NAME1,&g_nThresh,g_maxThresh,on_ThreshChange);
	on_ThreshChange(0,0);

	waitKey(0);
	return 0;
}

