#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;

#define WINDOW_NAME1 "ԭʼ����"
#define WINDOW_NAME2 "Ч������"

Mat g_srcImage, g_grayImage;
int g_nThresh = 50;
int g_nMaxThresh = 255;
RNG g_rng(12345);

void on_ContoursChange(int,void*);

void on_ContoursChange(int, void*) {
	Mat threshold_output;
	vector<vector<Point>>contours;
	vector<Vec4i>hierarchy;

	//ʹ��Threshold����Ե
	threshold(g_grayImage,threshold_output,g_nThresh,255,THRESH_BINARY);

	//�ҳ�����
	findContours(threshold_output,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point(0,0));

	//����αƽ�����+��ȡ���κ�Բ�α߽��
	vector<vector<Point>>contours_poly(contours.size());
	vector<Rect>boundRect(contours.size());
	vector<Point2f>center(contours.size());
	vector<float>radius(contours.size());

	//һ��ѭ�����������в��֣����б���������ĵĲ���
	for (unsigned int i = 0; i < contours.size(); i++) {
		approxPolyDP(Mat(contours[i]), contours_poly[i], 3, true);		//��ָ�����ȱƽ����������
		boundRect[i] = boundingRect(Mat(contours_poly[i]));			//����㼯������ľ��α߽�
		minEnclosingCircle(contours_poly[i], center[i], radius[i]);	//�Ը�����2D�㼯��Ѱ����С����İ�ΧԲ��
	}
		//���ƶ��������+��Χ�ľ��ο�+Բ�ο�
		Mat drawing = Mat::zeros(threshold_output.size(), CV_8UC3);
		for (unsigned int i = 0; i < contours.size(); i++) {
			Scalar color = Scalar(g_rng.uniform(0,255),g_rng.uniform(0,255),g_rng.uniform(0,255));			//���ѡ����ɫ
			drawContours(drawing,contours_poly,i,color,1,8,vector<Vec4i>(),0,Point());
			rectangle(drawing,boundRect[i].tl(),boundRect[i].br(),color,2,8,0);
			circle(drawing,center[i],(int)radius[i],color,2,8,0);	

			namedWindow(WINDOW_NAME2, WINDOW_AUTOSIZE);
			imshow(WINDOW_NAME2,drawing);

		}

	}


int main() {
	system("color 1A");

	g_srcImage = imread("1.jpg",1);
	if (!g_srcImage.data) {
		printf("��ȡͼƬ����\n");
		return false;
	}
	cvtColor(g_srcImage,g_grayImage,COLOR_BGR2GRAY);
	blur(g_grayImage,g_grayImage,Size(3,3));

	namedWindow(WINDOW_NAME1,WINDOW_AUTOSIZE);
	imshow(WINDOW_NAME1,g_srcImage);

	createTrackbar("��ֵ��",WINDOW_NAME1,&g_nThresh,g_nMaxThresh,on_ContoursChange);
	on_ContoursChange(0, 0);

	waitKey(0);
	return 0;

}