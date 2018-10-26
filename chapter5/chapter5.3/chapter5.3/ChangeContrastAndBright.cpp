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
	namedWindow("原图窗口", 1);
	for (int y = 0; y < g_srcImage.rows; y++) {
		for (int x = 0; x < g_srcImage.cols; x++) {
			for (int c = 0; c < 3; c++) {
				//由于因为运算结果可能会超出像素取值范围(溢出)，还可能是非整数，因此使用saturate_cast对结果进行转换，以确保它为有效值
				//saturate_cast大致如下:
				/*
				if(data<0)
					data = 0;
				else if(data >255)
					data = 255;
				*/
				//为了观察效果，a的取值为0.0到3.0的浮点值，但是轨迹条一般取值为整数,因此将nContrastValue参数设为0-300，最后乘以0.01
				g_dstImage.at<Vec3b>(y, x)[c] = saturate_cast<uchar>((g_nContrastValue*0.01)*(g_srcImage.at<Vec3b>(y, x)[c]) + g_nBrightValue);

			}
		}
	}
	imshow("原始窗口", g_srcImage);
	imshow("效果图窗口", g_dstImage);
}
int main() {
	g_srcImage = imread("1.jpg");
	if (!g_srcImage.data) {
		printf("读取图片1错误！\n");
		return false;
	}
	g_dstImage = Mat::zeros(g_srcImage.size(), g_srcImage.type());

	g_nContrastValue = 80;
	g_nBrightValue = 80;

	namedWindow("效果图窗口", 1);
	createTrackbar("对比度:", "效果图窗口", &g_nContrastValue, 300, on_ContrastAndBright);
	createTrackbar("亮度:", "效果图窗口", &g_nBrightValue, 300, on_ContrastAndBright);

	on_ContrastAndBright(g_nContrastValue, 0);
	on_ContrastAndBright(g_nBrightValue, 0);
	while (char(waitKey(1)) != 'q') {}
	return 0;
}