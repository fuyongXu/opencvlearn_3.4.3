#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
using namespace cv;
using namespace std;

Mat g_srcImage, g_dstImage1, g_dstImage2, g_dstImage3;
int g_nBoxFilterValue = 3;			//方框滤波参数值
int g_nMeanBlurValue = 3;			//均值滤波参数值
int g_nGaussianBlurValue = 3;		//高斯滤波参数值

//轨迹条回调函数
static void on_BoxFilter(int, void*);
static void on_MeanBlur(int, void*);
static void on_GaussianBlur(int, void*);

static void on_BoxFilter(int, void*) {
	//方框滤波操作
	boxFilter(g_srcImage,g_dstImage1,-1,Size(g_nBoxFilterValue+1,g_nBoxFilterValue+1));
	imshow("方框滤波",g_dstImage1);
}
static void on_MeanBlur(int, void *) {
	//均值滤波操作
	blur(g_srcImage,g_dstImage2,Size(g_nMeanBlurValue+1,g_nMeanBlurValue+1),Point(-1,-1));
	imshow("均值滤波", g_dstImage2);
}
static void on_GaussianBlur(int, void*) {
	//高斯滤波操作
	GaussianBlur(g_srcImage,g_dstImage3,Size(g_nGaussianBlurValue*2+1,g_nGaussianBlurValue*2+1),0,0);
	imshow("高斯滤波",g_dstImage3);
}
int main() {
	system("color 5E");
	g_srcImage = imread("1.jpg",1);
	if (!g_srcImage.data) {
		printf("读取图片错误！\n");
		return false;
	}

	//复制原图到三个Mat类型中
	g_dstImage1 = g_srcImage.clone();
	g_dstImage2 = g_srcImage.clone();
	g_dstImage3 = g_srcImage.clone();

	namedWindow("原图",1);
	imshow("原图", g_srcImage);

	//方框滤波
	namedWindow("方框滤波",1);
	createTrackbar("内核值:","方框滤波",&g_nBoxFilterValue,40,on_BoxFilter);
	on_BoxFilter(g_nBoxFilterValue,0);
	imshow("方框滤波", g_dstImage1);

	//均值滤波
	namedWindow("均值滤波",1);
	createTrackbar("内核值;","均值滤波",&g_nMeanBlurValue,40,on_MeanBlur);
	on_MeanBlur(g_nMeanBlurValue,0);
	imshow("均值滤波",g_dstImage2);

	//高斯滤波
	namedWindow("高斯滤波",1);
	createTrackbar("内核值:","高斯滤波",&g_nGaussianBlurValue,40,on_GaussianBlur);
	on_GaussianBlur(g_nGaussianBlurValue,0);
	imshow("高斯滤波",g_dstImage3);

	while(char(waitKey(1))!='q'){}
	return 0;
}