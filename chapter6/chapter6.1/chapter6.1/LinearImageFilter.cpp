#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterValue = 3;			//�����˲�����ֵ
int g_nMeanBlurValue = 3;			//��ֵ�˲�����ֵ
int g_nGaussianBlurValue = 3;		//��˹�˲�����ֵ

//�켣���ص�����
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

static void on_BoxFilter(int, void*) {
	//�����˲�����
	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
	imshow("�����˲�",g_dstImage1);
}
static void on_MeanBlur(int, void *) {
	//��ֵ�˲�����
	blur(g_srcImage,g_dstImage2,Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1),Point(-1,-1));
	imshow("��ֵ�˲�", g_dstImage2);
}
static void on_GaussianBlur(int, void*) {
	//��˹�˲�����
	GaussianBlur(g_srcImage,g_dstImage3,Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),0,0);
	imshow("��˹�˲�",g_dstImage3);
}
int main() {
	system("color 5E");
	g_srcImage = imread("1.jpg",1);
	if (!g_srcImage.data) {
		printf("��ȡͼƬ����\n");
		return false;
	}

	//����ԭͼ������Mat������
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	namedWindow("ԭͼ",1);
	imshow("ԭͼ", g_srcImage);

	//�����˲�
	namedWindow("�����˲�",1);
	createTrackbar("�ں�ֵ:","�����˲�",&g_nBoxFilterValue,40,on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue,0);
	imshow("�����˲�", g_dstImage1);

	//��ֵ�˲�
	namedWindow("��ֵ�˲�",1);
	createTrackbar("�ں�ֵ;","��ֵ�˲�",&g_nMeanBlurValue,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue,0);
	imshow("��ֵ�˲�",g_dstImage2);

	//��˹�˲�
	namedWindow("��˹�˲�",1);
	createTrackbar("�ں�ֵ:","��˹�˲�",&g_nGaussianBlurValue,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue,0);
	imshow("��˹�˲�",g_dstImage3);

	while(char(waitKey(1))!='q'){}
	return 0;
}