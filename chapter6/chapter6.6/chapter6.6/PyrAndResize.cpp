#include<opencv2/opencv.hpp>
#include<iostream>
using namespace cv;
using namespace std;

#define WINDOW_NAME "【程序窗口】"
Mat g_srcImage, g_dstImage, g_tmpImage;

int main()
{
	g_srcImage = imread("1.jpg");
	namedWindow(WINDOW_NAME);
	imshow(WINDOW_NAME, g_srcImage);
	g_tmpImage = g_srcImage;
	g_dstImage = g_tmpImage;
	int key = 0;
	while (1) //轮询获取按键信息
	{
		key = waitKey(9); //读取键值到key变量中
		switch (key) {
		case 27:  //按键ESC
		case 'q':
			return 0;
			break;
		case '1':
			pyrUp(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			cout << "检测到按键【1】被按下，开始进行基于【pyrUp】函数的图片放大：图片尺寸*2" << endl;
			break;
		case '2':
			pyrDown(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			cout << "检测到按键【2】被按下，开始进行基于【pyrDown】函数的图片缩小：图片尺寸/2" << endl;
			break;
		case '3':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols * 2, g_tmpImage.rows * 2));
			cout << "检测到按键【3】被按下，开始进行基于【resize】函数的图片放大：图片尺寸*2" << endl;
			break;
		case '4':
			resize(g_tmpImage, g_dstImage, Size(g_tmpImage.cols / 2, g_tmpImage.rows / 2));
			cout << "检测到按键【4】被按下，开始进行基于【pyrUp】函数的图片缩小：图片尺寸/2" << endl;
			break;
		}
		imshow(WINDOW_NAME, g_dstImage);
		g_tmpImage = g_dstImage; //将dst赋值给tmp，方便下一次循环
	}

	return 0;
}